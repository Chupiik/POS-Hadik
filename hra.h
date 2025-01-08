#ifndef HRA_H
#define HRA_H
#include "server.h"
#include "plocha.h"
#include "snake.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Hra {
    struct Plocha plocha;
	int isPaused;
    pthread_mutex_t* game_mutex;
};

void init_hra(struct Hra* hra, int riadky, int stlpce, int pocet_jedla);

void nastav_snake(struct Snake *snake, struct Hra *hra);
void pravidla_hry(struct Snake *snake, struct Hra* hra, int *jeGameOver);
void vykonaj_pohyb(char input, struct Snake *snake);

#endif // HRA_H