// Compile: gcc tcp_quad_server.c -o s -pthread
// Run: ./s

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <math.h>

#define PORT 7777
#define BUFF 256

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
    int a, b, c;

    int n = read(sock, buffer, BUFF);
    if (n <= 0) { close(sock); pthread_exit(NULL); }
    buffer[n] = '\0';

    sscanf(buffer, "%d %d %d", &a, &b, &c);
    char result[BUFF];

    if (a == 0) { // Linear or invalid
        if (b == 0) {
            sprintf(result, "Invalid equation (a=0, b=0)");
        } else {
            double root = -((double)c)/b;
            sprintf(result, "Linear equation root: %.2lf", root);
        }
    } else { // Quadratic
        double D = b*b - 4*a*c;
        if (D > 0) {
            double r1 = (-b + sqrt(D))/(2*a);
            double r2 = (-b - sqrt(D))/(2*a);
            sprintf(result, "Roots are real and distinct: %.2lf , %.2lf", r1, r2);
        } else if (D == 0) {
            double r = -b/(2.0*a);
            sprintf(result, "Roots are real and equal: %.2lf", r);
        } else {
            double real = -b/(2.0*a);
            double imag = sqrt(-D)/(2*a);
            sprintf(result, "Roots are complex: %.2lf + %.2lfi , %.2lf - %.2lfi", real, imag, real, imag);
        }
    }

    send(sock, result, strlen(result), 0);
    close(sock);
    pthread_exit(NULL);
}
