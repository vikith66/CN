// 240970107: Vikith B Kotian
// Checks if it’s an Armstrong number.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int isArmstrong(int num) {
    int original = num, sum = 0, digits = 0, temp = num;
    while (temp > 0) {
        digits++;
        temp /= 10;
    }

    temp = num;
    while (temp > 0) {
        int rem = temp % 10;
        sum += pow(rem, digits);
        temp /= 10;
    }

    return (sum == original);
}

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

        int num;
        char buffer[10];

        printf("Enter an integer: ");
        scanf("%d", &num);

        write(p1[1], &num, sizeof(num));

        read(p2[0], buffer, sizeof(buffer));

        printf("Child says: %s\n", buffer);

        close(p1[1]);
        close(p2[0]);
    } else {
        close(p1[1]); 
        close(p2[0]); 

        int num;
        char msg[10];

        read(p1[0], &num, sizeof(num));

        if (isArmstrong(num)) {
            strcpy(msg, "YES");
        } else {
            strcpy(msg, "NO");
        }

        write(p2[1], msg, strlen(msg) + 1);

        close(p1[0]);
        close(p2[1]);
    }

    return 0;
}
