// Compile: gcc tcp_ip_class_server.c -o server -pthread
// Run:     ./server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 9999
#define BUFF 100

void *client_handler(void *arg);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    pthread_t tid;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); exit(1); }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind"); exit(1);
    }

    if (listen(server_fd, 5) < 0) { perror("listen"); exit(1); }
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

    int n = read(sock, buffer, BUFF);
    if (n <= 0) {
        close(sock);
        pthread_exit(NULL);
    }
    buffer[n] = '\0';
    printf("Received IP: %s\n", buffer);

    int first_octet;
    sscanf(buffer, "%d", &first_octet);
    char result[BUFF];

    if (first_octet >= 1 && first_octet <= 126)
        sprintf(result, "Class A, Default Mask: 255.0.0.0");
    else if (first_octet >= 128 && first_octet <= 191)
        sprintf(result, "Class B, Default Mask: 255.255.0.0");
    else if (first_octet >= 192 && first_octet <= 223)
        sprintf(result, "Class C, Default Mask: 255.255.255.0");
    else if (first_octet >= 224 && first_octet <= 239)
        sprintf(result, "Class D, Default Mask: N/A (Multicast)");
    else if (first_octet >= 240 && first_octet <= 254)
        sprintf(result, "Class E, Default Mask: N/A (Reserved)");
    else
        sprintf(result, "Invalid IP");

    send(sock, result, strlen(result), 0);
    close(sock);
    pthread_exit(NULL);
}
