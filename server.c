#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include "snake.h"
#include "hra.h"
#include "server.h"


#define PORT 55000
#define MAX_CLIENTS 10

struct Hra game;

struct ClientData {
    int fd;
    struct Snake snake;
    int jeGameOver;
    pthread_t thread;
	pthread_mutex_t game_mutex;
};

struct ClientData clients[MAX_CLIENTS];

void* client_thread(void* arg) {
    struct ClientData* client = (struct ClientData*)arg;
    char input;

    while (!client->jeGameOver) {
        read(client->fd, &input, 1);
        
		pthread_mutex_lock(&client->game_mutex);

		vykonaj_pohyb(input, &client->snake);
		pohni_snake(&client->snake);
		pravidla_hry(&client->snake, &game, &client->jeGameOver);

		napln_plochu(&game.plocha);
		vykresli_jedlo(&game.plocha);
		for (int i = 0; i < MAX_CLIENTS; i++) {
			if (clients[i].fd > 0 && !clients[i].jeGameOver) {
				vykresli_snake(&clients[i].snake, &game.plocha);
			}
		}

		if (write(client->fd, game.plocha.policko, sizeof(char) * MAX_STLPCE * MAX_RIADKY) < 0) {
			perror("Error writing board to client");
			close(client->fd);
			client->fd = -1;
			pthread_mutex_unlock(&client->game_mutex);
			break;
		}

		char score_message[50];
		snprintf(score_message, sizeof(score_message), "Score: %d", client->snake.dlzka);
		if (write(client->fd, score_message, strlen(score_message)) < 0) {
			perror("Error writing score to client");
			close(client->fd);
			client->fd = -1;
			pthread_mutex_unlock(&client->game_mutex);
			break;
		}

		pthread_mutex_unlock(&client->game_mutex);
	

        usleep(300000);
    }

    close(client->fd);
    client->fd = -1;
    return NULL;
}

int main_server(int riadky, int stlpce, int pocet_jedla) {
	init_hra(&game, riadky, stlpce, pocet_jedla);
	
    int server_fd, new_client;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    pthread_mutex_init(&game.game_mutex, NULL);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i].fd = -1;
    }

    srand(time(0));

    while (1) {
        new_client = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (new_client < 0) {
            perror("Accept failed");
            continue;
        }

        // Set the new client socket to non-blocking mode
        int flags = fcntl(new_client, F_GETFL, 0);
        if (flags == -1 || fcntl(new_client, F_SETFL, flags | O_NONBLOCK) == -1) {
            perror("Failed to set client socket to non-blocking mode");
            close(new_client);
            continue;
        }

        int assigned = 0;
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i].fd == -1) {
                clients[i].fd = new_client;
                nastav_snake(&clients[i].snake, &game);
                clients[i].jeGameOver = 0;

                printf("Server - client %d connected\n", i);
                if (pthread_create(&clients[i].thread, NULL, client_thread, &clients[i]) != 0) {
                    perror("Thread creation failed");
                    close(new_client);
                    clients[i].fd = -1;
                } else {
					int velkost_plochy[2];
					velkost_plochy[0] = game.plocha.riadky;
					velkost_plochy[1] = game.plocha.stlpce;
					if (write(clients[i].fd, velkost_plochy, sizeof(int) *2) < 0) {
						perror("Error writing board size to client");
						close(clients[i].fd);
						clients[i].fd = -1;
						break;
					}
					printf("Sent board sizes to client\n");
					clients[i].game_mutex = game.game_mutex;
                    assigned = 1;
                }
                break;
            }
        }

        if (!assigned) {
            printf("Max clients reached. Connection rejected.\n");
            close(new_client);
        }
    }

    close(server_fd);
    pthread_mutex_destroy(&game.game_mutex);
    return 0;
}
