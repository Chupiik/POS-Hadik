#include <stdlib.h>
#include "hra.h"

struct Jedlo jedlo[pocet_jedla];
int jeGameOver = 0;

void nastav_snake() {
    snake.dlzka = 1;
    snake.cast[0].x = 1 + rand() % (stlpce - 2);
    snake.cast[0].y = 1 + rand() % (riadky - 2);
}

void nastav_jedlo() {
    for (int i = 0; i < pocet_jedla; i++) {
        jedlo[i].x = 1 + rand() % (stlpce - 2);
        jedlo[i].y = 1 + rand() % (riadky - 2);
        jedlo[i].zjedene = 0;
    }
}

void vykresli_jedlo() {
    for (int i = 0; i < pocet_jedla; i++) {
        if (!jedlo[i].zjedene) {
            plocha[jedlo[i].y * stlpce + jedlo[i].x] = '+';
        }
    }
}

void pravidla_hry() {
    for (int i = 0; i < pocet_jedla; i++) {
        if (!jedlo[i].zjedene &&
            jedlo[i].x == snake.cast[0].x &&
            jedlo[i].y == snake.cast[0].y) {
            jedlo[i].zjedene = 1;
            snake.dlzka++;
        }
    }

    if (snake.cast[0].x == 0 || snake.cast[0].x == stlpce - 1 ||
        snake.cast[0].y == 0 || snake.cast[0].y == riadky - 1) {
        jeGameOver = 1;
    }

    for (int i = 1; i < snake.dlzka; i++) {
        if (snake.cast[0].x == snake.cast[i].x &&
            snake.cast[0].y == snake.cast[i].y) {
            jeGameOver = 1;
        }
    }
}
