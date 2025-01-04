#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <errno.h>
#include "snake.h"
#include "plocha.h"
#include "hra.h"
#include <fcntl.h>

#define PORT 55000
#define MAX_CLIENTS 10

struct ClientData {
    int fd;
	struct Snake snake;
    int jeGameOver;
};

struct ClientData clients[MAX_CLIENTS];
struct Jedlo jedlo[pocet_jedla];

void broadcast_hry(struct ClientData clients[], struct Plocha* plocha) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].fd != -1) {
            if(clients[i].jeGameOver){
                char game_over_msg[4] = "GO\n";
                if (write(clients[i].fd, game_over_msg, strlen(game_over_msg)) < 0){
                     perror("Error writing to client");
                }
                close(clients[i].fd);
				clients[i].snake.dlzka = 0;
                clients[i].fd = -1;
            } else {
                if (write(clients[i].fd, plocha->policko, sizeof(char)*stlpce*riadky) < 0){
                    perror("Error writing to client");
                    close(clients[i].fd);
                    clients[i].fd = -1;
                }
            }
        }
    }
}


void handle_client_input(int client_fd, struct ClientData clients[MAX_CLIENTS]) {
     for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].fd == client_fd) {
            char input;
            ssize_t bytes_read = read(client_fd, &input, 1);
            if (bytes_read > 0) {
				 printf("Server - client %d, received input: %c\n", i, input);
				 printf("Server - client %d, before vykonaj_pohyb - dx: %d, dy: %d\n", i, clients[i].snake.pohybX, clients[i].snake.pohybY);
				 vykonaj_pohyb(input, &clients[i].snake);
				 printf("Server - client %d, after vykonaj_pohyb - dx: %d, dy: %d\n", i, clients[i].snake.pohybX, clients[i].snake.pohybY);
            } else if (bytes_read < 0 && errno != EAGAIN && errno != EWOULDBLOCK){
                 perror("Error reading from client");
				 close(clients[i].fd);
                 clients[i].fd = -1;
            }
             return;
        }
     }
}

int main() {
	//Inicializacia socketu
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

    for (int i = 0; i < MAX_CLIENTS; i++){
         clients[i].fd = -1;
    }
	
	// Inicializacia hry
    srand(time(0));
	struct Plocha plocha;
	nastav_jedlo(jedlo);
	

    fd_set sockety_na_citanie;
    int max_fd;
    while (1) {
        FD_ZERO(&sockety_na_citanie);
        FD_SET(server_fd, &sockety_na_citanie);
        max_fd = server_fd;
		int flags_server = fcntl(server_fd, F_GETFL, 0);
		fcntl(server_fd, F_SETFL, flags_server | O_NONBLOCK);
		for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i].fd > 0) {
                FD_SET(clients[i].fd, &sockety_na_citanie);
                if(clients[i].fd > max_fd){
                    max_fd = clients[i].fd;
                }
            }
        }
		printf("Server - Before select\n");
		printf("%d \n", max_fd);
        int activity = select(max_fd + 1, &sockety_na_citanie, NULL, NULL, NULL);
		printf("Server - After select\n");
        if (activity < 0 && errno != EINTR) {
            perror("Select error");
        }

        if (FD_ISSET(server_fd, &sockety_na_citanie)) {
            new_client = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
            if (new_client < 0) {
                perror("Accept failed");
                continue;
            }
			
			int flags = fcntl(new_client, F_GETFL, 0);
			if (flags < 0 || fcntl(new_client, F_SETFL, flags | O_NONBLOCK) < 0) {
				perror("Setting non-blocking failed");
				close(new_client);
				continue;
			}

            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i].fd == -1) {
                    clients[i].fd = new_client;
					nastav_snake(&clients[i].snake);
                    break;
                }
            }
        }
		
		for (int i = 0; i < MAX_CLIENTS; i++) {
           if (clients[i].fd > 0) {
                handle_client_input(clients[i].fd, clients);
            }
        }
		napln_plochu(&plocha);
		vykresli_jedlo(jedlo, &plocha);
		for (int i = 0; i < MAX_CLIENTS; i++) {
			if(clients[i].fd > 0 && !clients[i].jeGameOver){
				pohni_snake(&clients[i].snake);
				vykresli_snake(&clients[i].snake, &plocha);
			}
		}
		for (int i = 0; i < MAX_CLIENTS; i++) {
			if(clients[i].fd > 0 && !clients[i].jeGameOver){
				printf("Server - before pohni_snake - snake x:%d, y:%d\n",  clients[i].snake.cast[0].x, clients[i].snake.cast[0].y);
				printf("Server - after pohni_snake - snake x:%d, y:%d\n",  clients[i].snake.cast[0].x, clients[i].snake.cast[0].y);
				pravidla_hry(&clients[i].snake, jedlo, &plocha, &clients[i].jeGameOver);
				printf("Server - after pravidla_hry - jeGameOver:%d\n", clients[i].jeGameOver);
			}
		}

		printf("Server - Before broadcast\n");
        broadcast_hry(clients, &plocha);
		printf("Server - After broadcast\n");
        usleep(300000);
	
    }
	
	printf("Server - End\n");
    close(server_fd);
    return 0;
}