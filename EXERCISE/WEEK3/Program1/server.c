#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    char str[100];
    char result[10];

    // Create two FIFOs
    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    while (1) {
        int fd1 = open("fifo1", O_RDONLY);
        read(fd1, str, sizeof(str));
        close(fd1);

        if (strcmp(str, "exit") == 0) {
            printf("Server exiting...\n");
            break;
        }

        // Check palindrome
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

        if (isPalindrome)
            strcpy(result, "YES");
        else
            strcpy(result, "NO");

        int fd2 = open("fifo2", O_WRONLY);
        write(fd2, result, strlen(result) + 1);
        close(fd2);

        printf("Processed string: %s -> %s\n", str, result);
    }

    unlink("fifo1");
    unlink("fifo2");
    return 0;
}
