// Compile: gcc tcp_multi_server.c -o server -pthread
// Run:     ./server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8888
#define MAX_CLIENTS 10
#define BUFF 1024

void *client_handler(void *arg);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    pthread_t tid;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) { perror("socket failed"); exit(EXIT_FAILURE); }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed"); exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0) { perror("listen"); exit(EXIT_FAILURE); }
    printf("Server listening on port %d...\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) { perror("accept"); continue; }

        printf("New client connected\n");
        pthread_create(&tid, NULL, client_handler, (void *)&new_socket);
    }

    close(server_fd);
    return 0;
}

void *client_handler(void *arg) {
    int sock = *(int*)arg;
    char buffer[BUFF];
    int n;

    while (1) {
        memset(buffer, 0, BUFF);
        n = read(sock, buffer, BUFF);
        if (n <= 0) {
            printf("Client disconnected\n");
            break;
        }
        buffer[n] = '\0';
        printf("Client: %s\n", buffer);

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Client ended chat session\n");
            break;
        }

        printf("Server: ");
        fgets(buffer, BUFF, stdin);
        send(sock, buffer, strlen(buffer), 0);
    }

    close(sock);
    pthread_exit(NULL);
}
