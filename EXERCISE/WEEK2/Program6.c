#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int p1[2], p2[2]; 
    pid_t pid;

    if (pipe(p1) == -1 || pipe(p2) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid > 0) {
        close(p1[0]); 
        close(p2[1]); 

        char str[100];
        printf("Enter a string: ");
        scanf("%s", str);  

        write(p1[1], str, strlen(str) + 1);

        char result[20];
        read(p2[0], result, sizeof(result));

        printf("Child says: %s\n", result);

        close(p1[1]);
        close(p2[0]);
    } else {
        close(p1[1]); 
        close(p2[0]); 

        char str[100];
        read(p1[0], str, sizeof(str));

        int i = 0, j = strlen(str) - 1;
        int isPalindrome = 1;

        while (i < j) {
            if (str[i] != str[j]) {
                isPalindrome = 0;
                break;
            }
            i++;
            j--;
        }

        char *msg;
        if (isPalindrome)
            msg = "PALINDROME";
        else
            msg = "NOT PALINDROME";

        write(p2[1], msg, strlen(msg) + 1);

        close(p1[0]);
        close(p2[1]);
    }

    return 0;
}
