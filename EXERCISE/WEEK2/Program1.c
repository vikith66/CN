// 240970107: Vikith B Kotian
// Program: Parent sends string to child using pipe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char str[100];

    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    else if (pid == 0) {
        close(pipefd[1]); 

        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer));

        int i, charCount = 0, digitCount = 0;
        for (i = 0; buffer[i] != '\0'; i++) {
            if (isalpha(buffer[i]))
                charCount++;
            else if (isdigit(buffer[i]))
                digitCount++;
        }

        printf("\n[Child] Received string: %s\n", buffer);
        printf("[Child] Number of characters: %d\n", charCount);
        printf("[Child] Number of digits: %d\n", digitCount);

        close(pipefd[0]); // Close read end
    }

    else {
        close(pipefd[0]);

        printf("Enter a string: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0'; 
        
        write(pipefd[1], str, strlen(str) + 1); 
        close(pipefd[1]); 
    }

    return 0;
}
