#include "server.h"

void pause_game(struct Hra* game) {
    pthread_mutex_lock(game->game_mutex);
	game->isPaused = 1;
    printf("Game paused.\n");
}

void unpause_game(struct Hra* game) {
    printf("Game unpaused.\n");
	game->isPaused = 0;
    pthread_mutex_unlock(game->game_mutex);
}

void pause_game_for_seconds(int seconds, struct Hra* game) {
    pause_game(game);
    sleep(seconds);
    unpause_game(game);
}

void send_info_to_player(struct ClientData* client, char score_message[50]) {
		pthread_mutex_lock(client->server->game->game_mutex);
		napln_plochu(&client->server->game->plocha);
		vykresli_jedlo(&client->server->game->plocha);
		for (int i = 0; i < MAX_CLIENTS; i++) {
			if (client->server->clients[i].fd > 0 && !client->server->clients[i].jeGameOver) {
				vykresli_snake(&client->server->clients[i].snake, &client->server->game->plocha);
			}
		}

		if (write(client->fd, client->server->game->plocha.policko, sizeof(char) * MAX_STLPCE * MAX_RIADKY) < 0) {
			perror("Error writing board to client");
			close(client->fd);
			client->fd = -1;
			pthread_mutex_unlock(client->server->game->game_mutex);
			return;
		}

		if (write(client->fd, score_message, strlen(score_message)) < 0) {
			perror("Error writing score to client");
			close(client->fd);
			client->fd = -1;
			pthread_mutex_unlock(client->server->game->game_mutex);
			return;
		}

		pthread_mutex_unlock(client->server->game->game_mutex);
}


void* client_thread(void* arg) {
    struct ClientData* client = (struct ClientData*)arg;
    char input;

    while (!client->jeGameOver) {
        read(client->fd, &input, 1);
        
		pthread_mutex_lock(client->server->game->game_mutex);

		vykonaj_pohyb(input, &client->snake);
		pohni_snake(&client->snake, &client->server->game->plocha);
		pravidla_hry(&client->snake, client->server->game, &client->jeGameOver);
		pthread_mutex_unlock(client->server->game->game_mutex);
		
		char score_message[50];
		snprintf(score_message, sizeof(score_message), "Score: %d", client->snake.dlzka);
		send_info_to_player(client, score_message);
	

        usleep(300000);
    }

    close(client->fd);
    client->fd = -1;
    return NULL;
}

int main_server(int riadky, int stlpce, int pocet_jedla, int typ_plochy) {
	struct Hra game;
	init_hra(&game, riadky, stlpce, pocet_jedla, typ_plochy);
	
	struct Server server;
	server.game = &game;
	
    int server_fd, new_client;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

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
        server.clients[i].fd = -1;
    }

    srand(time(0));

    while (1) {
        new_client = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (new_client < 0) {
            perror("Accept failed");
            continue;
        }

        int flags = fcntl(new_client, F_GETFL, 0);
        if (flags == -1 || fcntl(new_client, F_SETFL, flags | O_NONBLOCK) == -1) {
            perror("Failed to set client socket to non-blocking mode");
            close(new_client);
            continue;
        }

        int assigned = 0;
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (server.clients[i].fd == -1) {
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
					if (write(server.clients[i].fd, velkost_plochy, sizeof(int) *2) < 0) {
						perror("Error writing board size to client");
						close(server.clients[i].fd);
						server.clients[i].fd = -1;
						break;
					}
					printf("Sent board sizes to client\n");
					server.clients[i].server = &server;
                    assigned = 1;
					char score_message[50];
					snprintf(score_message, sizeof(score_message), "GAME PAUSED. Score: %d", server.clients[i].snake.dlzka);
					send_info_to_player(&server.clients[i], score_message);
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

    close(server_fd);
    pthread_mutex_destroy(game.game_mutex);
    return 0;
}
