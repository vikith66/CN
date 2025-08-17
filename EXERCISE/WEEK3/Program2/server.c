#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

struct User {
    char username[50];
    char password[50];
};

int main() {
    // Pre-stored user data
    struct User users[3] = {
        {"alice", "1234"},
        {"bob", "abcd"},
        {"vikith", "mca2025"}
    };

    char buffer[100], uname[50], pass[50], response[100];

    // Create two FIFOs
    mkfifo("fifo1", 0666); // Client -> Server
    mkfifo("fifo2", 0666); // Server -> Client

    while (1) {
        int fd1 = open("fifo1", O_RDONLY);
        read(fd1, buffer, sizeof(buffer));
        close(fd1);

        if (strcmp(buffer, "exit") == 0) {
            printf("Server exiting...\n");
            break;
        }

        // Split username and password (format: "username password")
        sscanf(buffer, "%s %s", uname, pass);

        int authenticated = 0;
        for (int i = 0; i < 3; i++) {
            if (strcmp(uname, users[i].username) == 0 &&
                strcmp(pass, users[i].password) == 0) {
                authenticated = 1;
                break;
            }
        }

        if (authenticated)
            sprintf(response, "Welcome %s", uname);
        else
            sprintf(response, "Login Access Denied");

        int fd2 = open("fifo2", O_WRONLY);
        write(fd2, response, strlen(response) + 1);
        close(fd2);

        printf("Received: %s %s -> %s\n", uname, pass, response);
    }

    unlink("fifo1");
    unlink("fifo2");
    return 0;
}
