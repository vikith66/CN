// Compile: gcc tcp_ip_class_client.c -o client
// Run:     ./client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9999
#define BUFF 100

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char ip[BUFF], buffer[BUFF];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    printf("Enter server IP to connect (like 127.0.0.1): ");
    scanf("%s", ip);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect"); exit(1);
    }

    char ip_input[BUFF];
    printf("Enter IP address to check: ");
    scanf("%s", ip_input);

    send(sockfd, ip_input, strlen(ip_input), 0);

    int n = read(sockfd, buffer, BUFF);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Server Response: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
