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
#include "plocha.h"
#include "hra.h"

#define PORT 55000
#define MAX_CLIENTS 10

struct ClientData {
    int fd;
    struct Snake snake;
    int jeGameOver;
    pthread_t thread;
};

struct ClientData clients[MAX_CLIENTS];
struct Jedlo jedlo[pocet_jedla];
struct Plocha plocha;
pthread_mutex_t game_mutex;

void* client_thread(void* arg) {
    struct ClientData* client = (struct ClientData*)arg;
    char input;

    while (!client->jeGameOver) {
        read(client->fd, &input, 1);
		pthread_mutex_lock(&game_mutex);
		printf("Server - client %d, received input: %c\n", (int)(client - clients), input);
		printf("Server - client %d, before vykonaj_pohyb - dx: %d, dy: %d\n", (int)(client - clients), client->snake.pohybX, client->snake.pohybY);
		vykonaj_pohyb(input, &client->snake);
		printf("Server - client %d, after vykonaj_pohyb - dx: %d, dy: %d\n", (int)(client - clients), client->snake.pohybX, client->snake.pohybY);
		pohni_snake(&client->snake);
		printf("Server - client %d, after pohni_snake - snake x: %d, y: %d\n", (int)(client - clients), client->snake.cast[0].x, client->snake.cast[0].y);
		pravidla_hry(&client->snake, jedlo, &plocha, &client->jeGameOver);
		printf("Server - client %d, after pravidla_hry - jeGameOver: %d\n", (int)(client - clients), client->jeGameOver);
		pthread_mutex_unlock(&game_mutex);
        

        pthread_mutex_lock(&game_mutex);
        napln_plochu(&plocha);
        vykresli_jedlo(jedlo, &plocha);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i].fd > 0 && !clients[i].jeGameOver) {
                vykresli_snake(&clients[i].snake, &plocha);
            }
        }

        printf("Server - client %d, broadcasting plocha\n", (int)(client - clients));
        if (write(client->fd, plocha.policko, sizeof(char) * stlpce * riadky) < 0) {
            perror("Error writing to client");
            close(client->fd);
            client->fd = -1;
            pthread_mutex_unlock(&game_mutex);
            break;
        }
        pthread_mutex_unlock(&game_mutex);

        usleep(300000);
    }

    close(client->fd);
    client->fd = -1;
    return NULL;
}

int main() {
    int server_fd, new_client;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    pthread_mutex_init(&game_mutex, NULL);

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
    nastav_jedlo(jedlo);

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

        int vytvoreny = 0;
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i].fd == -1) {
                clients[i].fd = new_client;
                nastav_snake(&clients[i].snake);
                clients[i].jeGameOver = 0;

                printf("Server - client %d connected\n", i);
                if (pthread_create(&clients[i].thread, NULL, client_thread, &clients[i]) != 0) {
                    perror("Thread creation failed");
                    close(new_client);
                    clients[i].fd = -1;
                } else {
                    vytvoreny = 1;
                }
                break;
            }
        }

        if (!vytvoreny) {
            printf("Max clients reached. Connection rejected.\n");
            close(new_client);
        }
    }

    close(server_fd);
    pthread_mutex_destroy(&game_mutex);
    return 0;
}
