#include "server.h"

void pause_game(struct Hra* game) {
    pthread_mutex_lock(&game->game_mutex);
	game->isPaused = 1;
    //printf("Game paused.\n");
}

void unpause_game(struct Hra* game) {
    //printf("Game unpaused.\n");
	game->isPaused = 0;
    pthread_mutex_unlock(&game->game_mutex);
}

void pause_game_for_seconds(int seconds, struct Hra* game) {
    pause_game(game);
    sleep(seconds);
    unpause_game(game);
}

void send_info_to_player(struct ClientData* client, char score_message[50]) {
	//printf("Before lock\n");
	pthread_mutex_lock(&client->server->game->game_mutex);
	//printf("After lock\n");
	napln_plochu(&client->server->game->plocha);
	//printf("After napln plochu\n");
	vykresli_jedlo(&client->server->game->plocha);
	//printf("After vykresli jedlo\n");
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (client->server->clients[i].fd > 0 && !client->server->clients[i].jeGameOver) {
			vykresli_snake(&client->server->clients[i].snake, &client->server->game->plocha);
		}
	}
	//printf("After Vsetko vykreslene\n");
	if (send(client->fd, client->server->game->plocha.policko, sizeof(char) * MAX_STLPCE * MAX_RIADKY, 0) < 0) {
		perror("Error sending board to client");
		close(client->fd);
		client->fd = -1;
		pthread_mutex_unlock(&client->server->game->game_mutex);
		return;
	}

	if (send(client->fd, score_message, strlen(score_message), 0) < 0) {
		perror("Error sending score to client");
		close(client->fd);
		client->fd = -1;
		pthread_mutex_unlock(&client->server->game->game_mutex);
		return;
	}

	pthread_mutex_unlock(&client->server->game->game_mutex);
}

void send_info_to_all_players(struct Server* server, char score_message[50]) {
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (server->clients[i].fd != -1) {
			send_info_to_player(&server->clients[i], score_message);
		}
	}
}

void exit_check(struct Server* server) {
	*server->pocetKlientov = 0;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if(server->clients[i].fd != -1) {
			*server->pocetKlientov++;
		}
	}
	if (*server->pocetKlientov == 0) {
		close(server->server_fd);
	}
}

void* client_thread(void* arg) {
    struct ClientData* client = (struct ClientData*)arg;
    char input;
	while (1) {
		input = 0;
		recv(client->fd, &input, 1, 0);
		if (input == 'x' || input == 'X') {
			char exit_info[50];
			snprintf(exit_info, sizeof(exit_info), "EXIT");
			send_info_to_player(client, exit_info);
			close(client->fd);
			client->fd = FD_ASSIGNED;
			(*client->server->pocetKlientov)--;
			return NULL;
		}
		if (input == 'r' || input == 'R') {
			nastav_snake(&client->snake, client->server->game);
            client->jeGameOver = 0;
			char restart_info[50];
			snprintf(restart_info, sizeof(restart_info), "GAME PAUSED - Server port: %d", client->server->server_port);
			send_info_to_all_players(client->server, restart_info);
			pause_game_for_seconds(3, client->server->game);
		}
		
		if (!client->jeGameOver) {
			pthread_mutex_lock(&client->server->game->game_mutex);

			vykonaj_pohyb(input, &client->snake);
			pohni_snake(&client->snake, &client->server->game->plocha);
			pravidla_hry(&client->snake, client->server->game, &client->jeGameOver);
			pthread_mutex_unlock(&client->server->game->game_mutex);
		}
		
		if (client->jeGameOver) {
			char score_message[50];
			snprintf(score_message, sizeof(score_message), "GAME OVER - Score: %d - Server port: %d", client->snake.dlzka, client->server->server_port);
			send_info_to_player(client, score_message);
		} else {
			char score_message[50];
			snprintf(score_message, sizeof(score_message), "Score: %d - Server port: %d", client->snake.dlzka, client->server->server_port);
			send_info_to_player(client, score_message);
		}
		usleep(300000);
	}
}

int main_server(int riadky, int stlpce, int pocet_jedla, int typ_plochy, int port) {
    struct Hra game;
    init_hra(&game, riadky, stlpce, pocet_jedla, typ_plochy);

    int server_fd, new_client;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int flags = fcntl(server_fd, F_GETFL, 0);
    fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

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

    printf("Server listening on port %d\n", port);

    struct Server server;
	server.server_port = port;
    server.game = &game;
    server.server_fd = server_fd;
    int pocetKlientov = 0;
    server.pocetKlientov = &pocetKlientov;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        server.clients[i].fd = -1;
    }

    int no_player_count = 0;
    while (1) {
		if (*server.pocetKlientov == 0) {
			printf("No players connected. Waiting for connections...%d\n", 10 - no_player_count);
		}

		new_client = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
	
		int assigned = 0;
		if (new_client >= 0) {
			int flags = fcntl(new_client, F_GETFL, 0);
			if (flags == -1 || fcntl(new_client, F_SETFL, flags | O_NONBLOCK) == -1) {
			perror("Failed to set client socket to non-blocking mode");
			close(new_client);
			continue;
			}
			for (int i = 0; i < MAX_CLIENTS; i++) {
				if (server.clients[i].fd < 0) {
					server.clients[i].fd = new_client;
					nastav_snake(&server.clients[i].snake, &game);
					server.clients[i].jeGameOver = 0;

					printf("Server - client %d connected\n", i);
					if (pthread_create(&server.clients[i].thread, NULL, client_thread, &server.clients[i]) != 0) {
						perror("Thread creation failed");
						close(new_client);
						server.clients[i].fd = -1;
					} else {
						int velkost_plochy[2];
						velkost_plochy[0] = game.plocha.riadky;
						velkost_plochy[1] = game.plocha.stlpce;
						if (send(server.clients[i].fd, velkost_plochy, sizeof(int) *2, 0) < 0) {
							perror("Error sending board size to client");
							close(server.clients[i].fd);
							server.clients[i].fd = -1;
							break;
						}
						//printf("Sent board sizes to client\n");
						server.clients[i].server = &server;
						assigned = 1;
						(*server.pocetKlientov)++;
						//printf("Assigned\n");
						char score_message[50];
						snprintf(score_message, sizeof(score_message), "GAME PAUSED - Server port: %d", server.server_port);
						send_info_to_all_players(&server, score_message);
						pause_game_for_seconds(3, &game);
					}
					break;
				}
			}
			if (!assigned) {
			printf("Max clients reached. Connection rejected.\n");
			close(new_client);
		}
		}

        usleep(1000000);

        if (*server.pocetKlientov == 0) {
            no_player_count++;

            if (no_player_count >= 10)
			{
                printf("No players joined within the timeout. Shutting down server \n");
                break;
            }
        } else {
            no_player_count = 0;
        }
    }

	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (server.clients[i].fd == FD_ASSIGNED || server.clients[i].fd > 0) {
			//close(server.clients[i].fd);
			pthread_join(server.clients[i].thread, NULL);
		}
	}
    close(server_fd);
    pthread_mutex_destroy(&game.game_mutex);
    return 0;
}
