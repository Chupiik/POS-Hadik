#ifndef HRA_H
#define HRA_H

#include "snake.h"
#include "plocha.h"

struct Jedlo {
    int x, y;
    int zjedene;
};

void nastav_snake(struct Snake *snake);
void nastav_jedlo(struct Jedlo jedlo[pocet_jedla]);
void vykresli_jedlo(struct Jedlo jedlo[pocet_jedla], struct Plocha* plocha);
void pravidla_hry(struct Snake *snake, struct Jedlo jedlo[pocet_jedla], struct Plocha* plocha, int *jeGameOver);
void vykonaj_pohyb(char input, struct Snake *snake);

#endif // HRA_H