#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main() {
	int fd;
	off_t new_offset;
	// Open a file for reading and writing
	fd = open("a.txt", O_RDWR);
	if (fd == -1) {
		perror("Error opening file");
		return 1;
	}
	// Move the file offset to 5 bytes from the beginning
	new_offset = lseek(fd, 4, SEEK_SET);
	char ch[10];
	int no_of_byte_read=read(fd,ch,1);
	ch[no_of_byte_read]='\0';
	printf("One char read(5th) : %s\n",ch);
	if (new_offset == -1) {
		perror("Error seeking in file");
		close(fd);
		return 1;
	}
	printf("New file offset: %ld\n", new_offset);
	// Move the file offset 4 bytes forward from the current position
	new_offset = lseek(fd, 4, SEEK_CUR);
	if (new_offset == -1) {
		perror("Error seeking in file");
		close(fd);
		return 1;
	}
	printf("New file offset: %ld\n", new_offset);
	// Move the file offset to 2 bytes before the end of the file
	new_offset = lseek(fd, -2, SEEK_END);
	if (new_offset == -1) {
		perror("Error seeking in file");
		close(fd);
		return 1;
	}
	printf("New file offset: %ld\n", new_offset);
	// Close the file
	close(fd);
	return 0;
}
