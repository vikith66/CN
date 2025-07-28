//Vikith B Kotian
//240970107

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    char filename[100];
    char content[100];

    printf("Enter the filename: ");
    scanf("%s", filename);

    printf("Enter the characters to write to file: ");
    scanf(" %[^\n]", content); 
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        sleep(1); 

        int fd = open(filename, O_RDONLY);
        if (fd < 0) {
            perror("Child: Cannot open file");
            exit(1);
        }
        printf("\nChild process reading from file '%s':\n", filename);
        char buffer[100];
        int bytesRead;
        while ((bytesRead = read(fd, buffer, sizeof(buffer)-1)) > 0) {
            buffer[bytesRead] = '\0';
            printf("%s", buffer);
        }
        close(fd);
        printf("\n");
    }
    else {
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            perror("Parent: Cannot open file");
            exit(1);
        }
        for (int i = 0; content[i] != '\0'; i++) {
            write(fd, &content[i], 1);
        }
        close(fd);
        printf("\nParent wrote to file '%s' and closed it.\n", filename);
        wait(NULL);
    }
    return 0;
}
