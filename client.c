#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "plocha.h"
#include "input.h"

#define SERVER_IP "127.0.0.1"
#define PORT 55000

int sock_fd;
int game_over = 0;

void* handle_input(void* arg) {
    while (!game_over) {
        char input = vrat_klavesu();
        if (input != -1) {
            if (write(sock_fd, &input, 1) < 0) {
                perror("Error writing to server");
                close(sock_fd);
                exit(EXIT_FAILURE);
            }
        }
        usleep(50000); // Prevent excessive CPU usage
    }
    return NULL;
}

void* handle_output(void* arg) {
    char board_buffer[stlpce * riadky];
    char score_buffer[50];

    while (!game_over) {
        // Read the board
        ssize_t bytes_read_board = read(sock_fd, board_buffer, sizeof(board_buffer));
        if (bytes_read_board <= 0) {
            perror("Error reading board from server");
            close(sock_fd);
            exit(EXIT_FAILURE);
        }

        // Read the score
        ssize_t bytes_read_score = read(sock_fd, score_buffer, sizeof(score_buffer) - 1);
        if (bytes_read_score <= 0) {
            perror("Error reading score from server");
            close(sock_fd);
            exit(EXIT_FAILURE);
        }
        score_buffer[bytes_read_score] = '\0';

        // Render the game board
        printf("\033[H\033[J"); // Clear the terminal
        for (int y = 0; y < riadky; y++) {
            for (int x = 0; x < stlpce; x++) {
                putchar(board_buffer[y * stlpce + x]);
            }
            putchar('\n');
        }

        // Display the score
        printf("%s\n", score_buffer);
    }
    return NULL;
}

int main() {
    struct sockaddr_in server_addr;

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

    pthread_t input_thread, output_thread;
    pthread_create(&input_thread, NULL, handle_input, NULL);
    pthread_create(&output_thread, NULL, handle_output, NULL);

    pthread_join(input_thread, NULL);
    pthread_join(output_thread, NULL);

    printf("Game Over, closing connection.\n");
    close(sock_fd);
    return 0;
}
