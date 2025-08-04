// 240970107: Vikith B Kotian
// Program: Parent & Child Process using fork()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>  

int main() {
    pid_t pid;
    char filename[100];

    printf("Enter the file name: ");
    scanf("%s", filename);

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    else if (pid == 0) {
        printf("\n[Child] Trying to open file: %s\n", filename);
        
        int fd = open(filename, O_RDONLY);
        if (fd < 0) {
            perror("[Child] Error opening file");
            exit(1);
        }

        char buffer[11]; 
        int bytesRead = read(fd, buffer, 10);
        if (bytesRead < 0) {
            perror("[Child] Error reading file");
            close(fd);
            exit(1);
        }

        buffer[bytesRead] = '\0';  // Null terminate
        printf("[Child] First 10 characters: %s\n", buffer);

        close(fd);
    }

    else {
        wait(NULL); // Wait for child to finish
        printf("[Parent] Child has completed reading.\n");
    }

    return 0;
}
