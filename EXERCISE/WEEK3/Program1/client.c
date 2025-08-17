#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    char str[100], result[10];

    while (1) {
        printf("Enter a string (or type 'exit' to quit): ");
        scanf("%s", str);

        int fd1 = open("fifo1", O_WRONLY);
        write(fd1, str, strlen(str) + 1);
        close(fd1);

        if (strcmp(str, "exit") == 0) {
            break;
        }

        int fd2 = open("fifo2", O_RDONLY);
        read(fd2, result, sizeof(result));
        close(fd2);

        printf("Server says: %s\n", result);
    }
    return 0;
}
