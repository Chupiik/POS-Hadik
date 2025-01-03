#ifndef HRA_H
#define HRA_H

#include "snake.h"
#include "plocha.h"

struct Jedlo {
    int x, y;
    int zjedene;
};
extern struct Jedlo jedlo[pocet_jedla];

extern int jeGameOver;

void nastav_snake(void);
void nastav_jedlo(void);
void vykresli_jedlo(void);
void pravidla_hry(void);

#endif // HRA_H
