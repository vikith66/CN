// Compile: gcc tcp_quad_client.c -o c
// Run: ./c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7777
#define BUFF 256

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[BUFF];
    int a, b, c;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect"); exit(1);
    }

    printf("Enter coefficients a, b, c: ");
    scanf("%d %d %d", &a, &b, &c);

    sprintf(buffer, "%d %d %d", a, b, c);
    send(sockfd, buffer, strlen(buffer), 0);

    int n = read(sockfd, buffer, BUFF);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Server Response: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
