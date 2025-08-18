#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<wait.h>


#define MAX_CLIENTS 3

int main() {
    int server_fd, new_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    int child_sockets[MAX_CLIENTS];
    int i;
    char buffer[1024];
    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
       
	// Set up server address information
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8082);
	   
	 if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }
	   listen(server_fd, 5);
	   printf("Server is listening on port 8080...\n");
     for (i = 0; i < MAX_CLIENTS; i++) {
	  new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
	
	// Using fork() create a child server process to handle each client
        if ((child_sockets[i] = fork()) == 0) {
            // Child process
           close(server_fd);
            manage_client(new_socket);
			 
            exit(0);
        }
     }
        close(new_socket);
		// Wait for all child processes to complete
    for (i = 0; i < MAX_CLIENTS; i++) {
        wait(NULL);
    }

    return 0;
}

void manage_client(int client_socket) {
    char buffer[1024];
    ssize_t bytes_received;
	while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
	printf(" CLIENT : %s\n",buffer);
	printf(" SERVER : ");gets(buffer);
	send(client_socket, buffer, 1024, 0);
    }
	close(client_socket);
}