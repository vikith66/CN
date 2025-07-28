//Vikith B Kotian
//240970107


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    char src[100], dest[100];
    int fdsrc, fdest;
    ssize_t bytesRead, bytesWritten;
    char buffer[BUFFER_SIZE];

    printf("Enter source file name: ");
    scanf("%s", src);

    printf("Enter destination file name: ");
    scanf("%s", dest);

    fdsrc = open(src, O_RDONLY);
    if (fdsrc == -1) {
        perror("Error opening source file");
    }

    fdest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fdest == -1) {
        printf("Error Opening The File");
    }

    while ((bytesRead = read(fdsrc, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(fdest, buffer, bytesRead);
    }

    if (bytesRead == -1) {
        perror("Error reading from source file");
    }

    close(fdsrc);
    close(fdest);

    printf("File copied successfully.\n");
    return 0;
}
