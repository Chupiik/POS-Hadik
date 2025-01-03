#ifndef SNAKE_H
#define SNAKE_H

#define MAX_DLZKA 256
struct SnakeCast {
    int x, y;
};
struct Snake {
    int dlzka;
	int pohybX, pohybY;
    struct SnakeCast cast[MAX_DLZKA];
};

extern struct Snake snake;

void vykresli_snake(void);
void pohni_snake(void);

#endif // SNAKE_H
