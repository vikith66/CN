//Vikith B Kotian
//240970107

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>  

int main() {
    int num;

    printf("Enter an integer: ");
    scanf("%d", &num);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        printf("\nChild Process: Multiplication Table for %d\n", num);
        for (int i = 1; i <= 10; i++) {
            printf("%d x %d = %d\n", num, i, num * i);
        }
        printf("Child finished.\n");
    }
    else {
        wait(NULL); 
        printf("\nParent Process.\n");
    }

    return 0;
}
