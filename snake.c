#include "snake.h"
#include "plocha.h"

void vykresli_snake(struct Snake* snake, struct Plocha* plocha) {
    for (int i = snake->dlzka - 1; i > 0; i--) {
        plocha->policko[snake->cast[i].y * plocha->stlpce + snake->cast[i].x] = 'O';
    }
    plocha->policko[snake->cast[0].y * plocha->stlpce + snake->cast[0].x] = '@';
}

void pohni_snake(struct Snake *snake) {
    for (int i = snake->dlzka - 1; i > 0; i--) {
        snake->cast[i] = snake->cast[i - 1];
    }

    snake->cast[0].x += snake->pohybX;
    snake->cast[0].y += snake->pohybY;
}