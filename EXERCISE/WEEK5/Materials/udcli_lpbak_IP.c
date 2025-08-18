//UDP Client Program -using client & Server different loop back
//loop back IP address
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define CLIENT_PORT 9090  
#define CLIENT_IP "127.0.0.101"  
#define SERVER_PORT 8080  
#define SERVER_IP "127.0.0.100"  
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(server_addr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up client address
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(CLIENT_IP);
    client_addr.sin_port = htons(CLIENT_PORT);

    // Bind the socket to the client's address
    if (bind(sockfd, (const struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);//8080
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);//127.0.0.100

    // Get the integer to send from the user
    int number;
    printf("Enter an integer to send to the server: ");
    scanf("%d", &number);
  
    sendto(sockfd, &number, sizeof(number), 0, (struct sockaddr *)&server_addr, addr_len);
    printf("Sent number %d to server.\n", number);
    int doubl_num;
    // Receive the doubled number from the server
    int n = recvfrom(sockfd, &doubl_num, sizeof(doubl_num), 0, (struct sockaddr *)&server_addr, &addr_len);
    if (n < 0) {
        perror("Receive failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';

    // Print the doubled number
    printf("CLIENT:Received doubled number from server: %d\n", doubl_num);

    close(sockfd);
    return 0;
}
