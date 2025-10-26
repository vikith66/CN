// Compile: gcc tcp_client.c -o client
// Run:     ./client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFF 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[BUFF];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect failed"); exit(1);
    }

    printf("Connected to server. Type messages or 'exit' to quit.\n");

    while (1) {
        printf("You: ");
        fgets(buffer, BUFF, stdin);
        send(sockfd, buffer, strlen(buffer), 0);

        if (strncmp(buffer, "exit", 4) == 0) break;

        memset(buffer, 0, BUFF);
        int n = read(sockfd, buffer, BUFF);
        if (n <= 0) {
            printf("Server disconnected\n");
            break;
        }
        buffer[n] = '\0';
        printf("Server: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
