// 240970107: Vikith B Kotian
// C Program: Parent sends string to child using pipe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

        int charCount = 0, digitCount = 0, i = 0;

        while (buffer[i] != '\0') {
            if ((buffer[i] >= 'A' && buffer[i] <= 'Z') || 
                (buffer[i] >= 'a' && buffer[i] <= 'z')) {
                charCount++;
            } else if (buffer[i] >= '0' && buffer[i] <= '9') {
                digitCount++;
            }
            i++;
        }

        printf("\n[Child] Received string: %s\n", buffer);
        printf("[Child] Number of characters: %d\n", charCount);
        printf("[Child] Number of digits: %d\n", digitCount);

        close(pipefd[0]); 
    }

    else {
        close(pipefd[0]); 

        printf("Enter a string: ");
        scanf(" %[^\n]", str); 
        int i = 0;
        while (str[i] != '\0') {
            if (str[i] == '\n') {
                str[i] = '\0';
                break;
            }
            i++;
        }

        int len = 0;
        while (str[len] != '\0') {
            len++;
        }

        write(pipefd[1], str, len + 1); 
        close(pipefd[1]);              

        wait(NULL); 
    }

    return 0;
}
