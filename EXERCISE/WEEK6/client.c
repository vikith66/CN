// Compile: gcc udp_file_client.c -o udp_client
// Run:     ./udp_client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5555
#define BUFF 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[BUFF];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send filename
    char filename[100];
    printf("Enter filename to fetch: ");
    scanf("%s", filename);

    sendto(sockfd, filename, strlen(filename)+1, 0,
           (struct sockaddr*)&servaddr, sizeof(servaddr));

    // Open new local file
    FILE *fp = fopen("client_copy.txt", "w");
    if (!fp) { perror("local file"); exit(1); }

    socklen_t len = sizeof(servaddr);
    while (1) {
        recvfrom(sockfd, buffer, BUFF, 0, (struct sockaddr*)&servaddr, &len);

        if (strcmp(buffer, "file-not-found") == 0) {
            printf("Server: file-not-found\n");
            break;
        }
        if (strcmp(buffer, "EOF") == 0) {
            printf("\nTransfer complete.\n");
            break;
        }
        printf("%s", buffer);
        fputs(buffer, fp);
    }

    fclose(fp);
    close(sockfd);
    return 0;
}
