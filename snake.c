#include "snake.h"
#include "plocha.h"

struct Snake snake;

void vykresli_snake() {
    for (int i = snake.dlzka - 1; i > 0; i--) {
        plocha[snake.cast[i].y * stlpce + snake.cast[i].x] = 'O';
    }
    plocha[snake.cast[0].y * stlpce + snake.cast[0].x] = '@';
}

void pohni_snake() {
    for (int i = snake.dlzka - 1; i > 0; i--) {
        snake.cast[i] = snake.cast[i - 1];
    }

    snake.cast[0].x += snake.pohybX;
    snake.cast[0].y += snake.pohybY;
}
