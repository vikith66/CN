#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char data[100];

    fd = creat("a.txt", 0644);

    if (fd == -1) {
        perror("Error creating file");
        exit(1);
    }

    printf("Enter data to write into the file:\n");
    fgets(data, sizeof(data), stdin);

    int bytes_written = write(fd, data, sizeof(data));

    if (bytes_written == -1) {
        perror("Error writing to file");
        exit(1);
    }

    if (close(fd) == -1) {
        perror("Error closing file");
        exit(1);
    }

    printf("Data written to file successfully!\n");

    return 0;
}
