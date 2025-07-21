#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main() {
	char buffer[100];
	ssize_t bytesRead;

	const char *pathname = "a.txt";
	int flags = O_RDONLY; // Open the file for reading
	int fd = open(pathname, flags);
	if (fd == -1) {
	perror("Error opening file");
	return 1;
	}
	bytesRead = read(fd, buffer, sizeof(buffer) - 1);
	if (bytesRead == -1) {
	perror("Error reading from stdin");
	return 1;
	}

	buffer[bytesRead] = '\0';
	printf("Read from stdin: %s\n", buffer);
	return 0;
}
