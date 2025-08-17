#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    char uname[50], pass[50], buffer[100], response[100];

    while (1) {
        printf("Enter username (or 'exit' to quit): ");
        scanf("%s", uname);

        if (strcmp(uname, "exit") == 0) {
            int fd1 = open("fifo1", O_WRONLY);
            write(fd1, uname, strlen(uname) + 1);
            close(fd1);
            break;
        }

        printf("Enter password: ");
        scanf("%s", pass);

        sprintf(buffer, "%s %s", uname, pass);

        int fd1 = open("fifo1", O_WRONLY);
        write(fd1, buffer, strlen(buffer) + 1);
        close(fd1);

        int fd2 = open("fifo2", O_RDONLY);
        read(fd2, response, sizeof(response));
        close(fd2);

        printf("Server: %s\n", response);
    }

    return 0;
}
