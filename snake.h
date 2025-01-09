#ifndef SNAKE_H
#define SNAKE_H

#include "plocha.h"

#define MAX_DLZKA 256
struct SnakeCast {
    int x, y;
};
struct Snake {
    int dlzka;
	int pohybX, pohybY;
    struct SnakeCast cast[MAX_DLZKA];
};

void vykresli_snake(struct Snake *snake, struct Plocha* plocha);
void pohni_snake(struct Snake *snake, struct Plocha* plocha);

#endif // SNAKE_H