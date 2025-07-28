//Vikith B Kotian
//240970107

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <num1> <num2> <operator>\n", argv[0]);
        return 1;
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    char op = argv[3][0];

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        int result;
        switch (op) {
            case '+':
                result = num1 + num2;
                printf("Child: %d + %d = %d\n", num1, num2, result);
                break;
            case '-':
                result = num1 - num2;
                printf("Child: %d - %d = %d\n", num1, num2, result);
                break;
            case '*':
                result = num1 * num2;
                printf("Child: %d * %d = %d\n", num1, num2, result);
                break;
            case '/':
                if (num2 == 0) {
                    printf("Child: Division by zero error.\n");
                } else {
                    float div = (float)num1 / num2;
                    printf("Child: %d / %d = %.2f\n", num1, num2, div);
                }
                break;
            default:
                printf("Invalid operator. \n");
        }
    }
    else {
        wait(NULL);
    }

    return 0;
}
