#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "plocha.h"
#include "input.h"
#include "client.h"

#define SERVER_IP "127.0.0.1"
#define PORT 55000

int client_fd;
int game_over = 0;
int riadky;
int stlpce;

void* handle_input(void* arg) {
    while (!game_over) {
        char input = vrat_klavesu();
        if (input != -1) {
            if (write(client_fd, &input, 1) < 0) {
                perror("Error writing to server");
                close(client_fd);
                exit(EXIT_FAILURE);
            }
        }
        usleep(50000); 
    }
    return NULL;
}

void* handle_output(void* arg) {
    char board_buffer[MAX_RIADKY * MAX_STLPCE];
    char score_buffer[50];

    while (!game_over) {
        ssize_t bytes_read_board = read(client_fd, board_buffer, sizeof(board_buffer));
		if (board_buffer[0] == 'G' &&board_buffer[1] == 'O') {
			printf("Game Over");
            close(client_fd);
            exit(EXIT_FAILURE);
		}
        if (bytes_read_board <= 0) {
            perror("Error reading board from server");
            close(client_fd);
            exit(EXIT_FAILURE);
        }
		//board_buffer[bytes_read_board] = '\0';
        
        ssize_t bytes_read_score = read(client_fd, score_buffer, sizeof(score_buffer) - 1);
        if (bytes_read_score <= 0) {
            perror("Error reading score from server");
            close(client_fd);
            exit(EXIT_FAILURE);
        }
        score_buffer[bytes_read_score] = '\0';

        printf("\033[H\033[J"); 
        for (int y = 0; y < riadky; y++) {
            for (int x = 0; x < stlpce; x++) {
                putchar(board_buffer[y * stlpce + x]);
            }
            putchar('\n');
        }
        printf("%s\n", score_buffer);
		
		char game_over_message[50];
		snprintf(game_over_message, sizeof(game_over_message), "GAME OVER");
		if (strncmp(score_buffer, game_over_message, 9) == 0) {
			printf("PRESS R TO RESPAWN", score_buffer);
		}
    }
    return NULL;
}

int main_client() {
    struct sockaddr_in server_addr;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");
	int velkost_plochy[2];
	ssize_t bytes_read_size = read(client_fd, velkost_plochy, sizeof(int) * 2);
	if (bytes_read_size <= 0) {
		perror("Error reading score from server");
		close(client_fd);
		exit(EXIT_FAILURE);
	}
	riadky = velkost_plochy[0];
	stlpce = velkost_plochy[1];
	printf("Board size read. %d %d\n", riadky, stlpce);

    pthread_t input_thread, output_thread;
    pthread_create(&input_thread, NULL, handle_input, NULL);
    pthread_create(&output_thread, NULL, handle_output, NULL);

    pthread_join(input_thread, NULL);
    pthread_join(output_thread, NULL);

    printf("Game Over, closing connection.\n");
    close(client_fd);
    return 0;
}
