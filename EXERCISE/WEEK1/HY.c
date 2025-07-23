#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int src_fd, dest_fd;
    char srcFileName[100], destFileName[100];
    char buffer[1024];  // buffer to read and write
    ssize_t bytesRead;  // number of bytes read

    // 1️⃣ User se source aur destination file name lena
    printf("Enter source file name: ");
    scanf("%s", srcFileName);

    printf("Enter destination file name: ");
    scanf("%s", destFileName);

    // 2️⃣ Source file ko read-only mode me open karna
    src_fd = open(srcFileName, O_RDONLY);
    if (src_fd < 0) {
        perror("Cannot open source file");
        return 1;
    }

    // 3️⃣ Destination file ko write mode me open karna
    dest_fd = open(destFileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Cannot open/create destination file");
        close(src_fd);
        return 1;
    }

    // 4️⃣ Read from source and write to destination
    while ((bytesRead = read(src_fd, buffer, sizeof(buffer))) > 0) {
        write(dest_fd, buffer, bytesRead);
    }

    printf("File copied successfully using system calls!\n");

    // 5️⃣ Files ko close karna
    close(src_fd);
    close(dest_fd);

    return 0;
}
