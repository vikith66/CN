// Compile: gcc udp_file_server.c -o udp_server
// Run:     ./udp_server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5555
#define BUFF 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[BUFF];
    socklen_t len = sizeof(cliaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    // Receive filename
    recvfrom(sockfd, buffer, BUFF, 0, (struct sockaddr*)&cliaddr, &len);
    buffer[strcspn(buffer, "\n")] = 0;

    FILE *fp = fopen(buffer, "r");
    if (!fp) {
        sendto(sockfd, "file-not-found", strlen("file-not-found")+1, 0,
               (struct sockaddr*)&cliaddr, len);
        close(sockfd);
        return 0;
    }

    char chunk[11];
    int n;
    while ((n = fread(chunk, 1, 10, fp)) > 0) {
        chunk[n] = '\0';
        sendto(sockfd, chunk, n+1, 0, (struct sockaddr*)&cliaddr, len);
        usleep(20000); // slow down a bit
    }

    sendto(sockfd, "EOF", 4, 0, (struct sockaddr*)&cliaddr, len);

    fclose(fp);
    close(sockfd);
    return 0;
}
