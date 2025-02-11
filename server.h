#ifndef SERVER_H
#define SERVER_H
#include "hra.h"
#include "input.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

#define FD_ASSIGNED -10
#define MAX_CLIENTS 10

struct ClientData {
    int fd;
    struct Snake snake;
    int jeGameOver;
    pthread_t thread;
	struct Server* server;
};

struct Server {
	struct Hra* game;
	struct ClientData clients[MAX_CLIENTS];
	int* pocetKlientov;
	int server_fd;
	int server_port;
};


int main_server(int riadky, int stlpce, int pocet_jedla, int typ_plochy, int port);
void* client_thread(void* arg);

#endif