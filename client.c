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

void* handle_input(void* arg) {
	struct ClientInfo* clientInfo = (struct ClientInfo*) arg;
	printf("ClientInfo gameOver %d / %d", clientInfo->gameOver, *clientInfo->gameOver);
	while(*clientInfo->gameOver == 0) {
		char input = vrat_klavesu();
		if (input != -1) {
			if (send(clientInfo->fd, &input, 1, 0) < 0) {
				perror("Error sending to server");
				close(clientInfo->fd);
				exit(EXIT_FAILURE);
			}
		}
		usleep(50000); 
    }
    return NULL;
}

void* handle_output(void* arg) {
	struct ClientInfo* clientInfo = (struct ClientInfo*) arg;
    char board_buffer[MAX_RIADKY * MAX_STLPCE];
    char score_buffer[50];

	while(*clientInfo->gameOver == 0) {
        ssize_t bytes_read_board = recv(clientInfo->fd, board_buffer, sizeof(board_buffer), 0);
		if (board_buffer[0] == 'G' && board_buffer[1] == 'O') {
			printf("Game Over");
            close(clientInfo->fd);
            exit(EXIT_FAILURE);
		}
        if (bytes_read_board <= 0) {
            perror("Error reading board from server");
            close(clientInfo->fd);
            exit(EXIT_FAILURE);
        }

        ssize_t bytes_read_score = recv(clientInfo->fd, score_buffer, sizeof(score_buffer) - 1, 0);
        if (bytes_read_score <= 0) {
            perror("Error reading score from server");
            close(clientInfo->fd);
            exit(EXIT_FAILURE);
        }
        score_buffer[bytes_read_score] = '\0';

        printf("\033[H\033[J"); 
        for (int y = 0; y < clientInfo->riadky; y++) {
            for (int x = 0; x < clientInfo->stlpce; x++) {
                putchar(board_buffer[y * clientInfo->stlpce + x]);
            }
            putchar('\n');
        }
        printf("%s\n", score_buffer);

		char game_over_message[50];
		snprintf(game_over_message, sizeof(game_over_message), "GAME OVER");
		if (strncmp(score_buffer, game_over_message, 9) == 0) {
			printf("PRESS R TO RESPAWN", score_buffer);
		}
		char exit_game_message[50];
		snprintf(exit_game_message, sizeof(exit_game_message), "EXIT");
		if (strncmp(score_buffer, exit_game_message, 4) == 0) {
			*(clientInfo->gameOver) = 1; 
		}
    }
    return NULL;
}

int main_client() {
    struct sockaddr_in server_addr;

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
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
	ssize_t bytes_read_size = recv(client_fd, velkost_plochy, sizeof(int) * 2, 0);
	if (bytes_read_size <= 0) {
		perror("Error reading score from server");
		close(client_fd);
		exit(EXIT_FAILURE);
	}
	int riadky = velkost_plochy[0];
	int stlpce = velkost_plochy[1];
	printf("Board size read. %d %d\n", riadky, stlpce);

	struct ClientInfo clientInfo;
	int gameOver = 0;
	clientInfo.fd = client_fd;
	clientInfo.riadky = riadky;
	clientInfo.stlpce = stlpce;
	clientInfo.gameOver = &gameOver;

    pthread_t input_thread, output_thread;
    pthread_create(&input_thread, NULL, handle_input, &clientInfo);
    pthread_create(&output_thread, NULL, handle_output, &clientInfo);

    pthread_join(input_thread, NULL);
    pthread_join(output_thread, NULL);

    printf("Closing connection.\n");
    close(client_fd);
    return 0;
}