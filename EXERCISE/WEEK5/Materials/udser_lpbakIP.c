// UDP Server Program-using client & Server different 
//loopback IP address
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PORT 8080 // Server will listen on this port
#define SERVER_IP "127.0.0.100" // Replace with your server's IP address


int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
   
    socklen_t addr_len = sizeof(client_addr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    // Bind the socket to the server address
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on IP %s and port %d...\n", SERVER_IP, SERVER_PORT);
	 int rec_num;
    while (1) {
       int n;

        // Receive the integer from the client
        n = recvfrom(sockfd, &rec_num, sizeof(rec_num), 0, (struct sockaddr *)&client_addr, &addr_len);
        if (n < 0) {
            perror("Receive failed");
            continue;
        }
      
        printf("Received number: %d\n", rec_num);

        int doubled_num = rec_num * 2;
        printf("Doubled number: %d\n", doubled_num);

        // Send the doubled number back to the client
        printf("Doubled number to be sent to client  %d", doubled_num);
        sendto(sockfd, &doubled_num, sizeof(doubled_num), 0, (struct sockaddr *)&client_addr, addr_len);
        printf("Sent doubled number back to client.\n");
    }

    // Close the socket
    close(sockfd);
    return 0;
}
