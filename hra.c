#include <stdlib.h>
#include "hra.h"
#include <string.h>

void nastav_snake(struct Snake *snake) {
    snake->dlzka = 1;
    snake->cast[0].x = 1 + rand() % (stlpce - 2);
    snake->cast[0].y = 1 + rand() % (riadky - 2);
	snake->pohybX = 0;
	snake->pohybY = 0;
}

void nastav_jedlo(struct Jedlo jedlo[pocet_jedla]) {
    for (int i = 0; i < pocet_jedla; i++) {
        jedlo[i].x = 1 + rand() % (stlpce - 2);
        jedlo[i].y = 1 + rand() % (riadky - 2);
        jedlo[i].zjedene = 0;
    }
}

void vykresli_jedlo(struct Jedlo jedlo[pocet_jedla], struct Plocha* plocha) {
    for (int i = 0; i < pocet_jedla; i++) {
        if (!jedlo[i].zjedene) {
            plocha->policko[jedlo[i].y * stlpce + jedlo[i].x] = '+';
        }
    }
}

void pravidla_hry(struct Snake *snake, struct Jedlo jedlo[pocet_jedla], struct Plocha* plocha, int *jeGameOver) {
    for (int i = 0; i < pocet_jedla; i++) {
        if (!jedlo[i].zjedene &&
            jedlo[i].x == snake->cast[0].x &&
            jedlo[i].y == snake->cast[0].y) {
            jedlo[i].zjedene = 1;
            snake->dlzka++;
        }
    }

    if (snake->cast[0].x == 0 || snake->cast[0].x == stlpce - 1 ||
        snake->cast[0].y == 0 || snake->cast[0].y == riadky - 1) {
        *jeGameOver = 1;
    }

    for (int i = 1; i < snake->dlzka; i++) {
        if (snake->cast[0].x == snake->cast[i].x &&
            snake->cast[0].y == snake->cast[i].y) {
            *jeGameOver = 1;
        }
    }
}


void vykonaj_pohyb(char input, struct Snake *snake){
    if (input != -1) {
        switch (input) {
            case 'w': snake->pohybX = 0; snake->pohybY = -1; break;
            case 's': snake->pohybX = 0; snake->pohybY = 1; break;
            case 'a': snake->pohybX = -1; snake->pohybY = 0; break;
            case 'd': snake->pohybX = 1; snake->pohybY = 0; break;
        }
    }
}