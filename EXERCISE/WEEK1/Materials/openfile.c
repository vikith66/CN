#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main() {
const char *pathname = "a.txt";
int flags = O_RDONLY; // Open the file for reading
int fd = open(pathname, flags);
if (fd == -1) {
perror("Error opening file");
return 1;
}
// File operations go here
// Close the file
close(fd);
return 0;
}
