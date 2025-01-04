#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "plocha.h"
#include "input.h"

#define SERVER_IP "127.0.0.1"
#define PORT 55000

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char server_buffer[stlpce * riadky + 1];
    char plocha_copy[stlpce * riadky];
    int game_over = 0;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    while (!game_over) {
        ssize_t bytes_read = read(sock_fd, server_buffer, sizeof(server_buffer) -1);
        if (bytes_read < 0) {
            perror("Error reading from server");
            close(sock_fd);
            exit(EXIT_FAILURE);
        } else if (bytes_read == 0){
            printf("Server closed connection\n");
            close(sock_fd);
            exit(EXIT_SUCCESS);
        }

        if (server_buffer[0] == 'G' && server_buffer[1] == 'O'){
            printf("Game Over from server.\n");
            game_over = 1;
            continue;
        }

        strncpy(plocha_copy, server_buffer, stlpce * riadky);
        plocha_copy[stlpce * riadky] = '\0';

        printf("\033[H\033[2J");
        for (int y = 0; y < riadky; y++) {
            for (int x = 0; x < stlpce; x++) {
                putchar(plocha_copy[y * stlpce + x]);
            }
            putchar('\n');
        }

        char input = vrat_klavesu();
            if (write(sock_fd, &input, 1) < 0){
                perror("Error writing to server");
                close(sock_fd);
                exit(EXIT_FAILURE);
            }
        usleep(50000);
    }
    printf("Game Over, closing connection.\n");
    close(sock_fd);
    return 0;
}