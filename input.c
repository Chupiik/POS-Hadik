#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "input.h"
#include "snake.h"

int vrat_klavesu(void) {
    struct termios oldt, newt;
    int ch, oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return (ch != EOF) ? ch : -1;
}

void vykonaj() {
    int ch = vrat_klavesu();

    if (ch != -1) {
        switch (ch) {
            case 'w': if (snake.pohybY != 1) { snake.pohybX = 0; snake.pohybY = -1; } break;
            case 's': if (snake.pohybY != -1) { snake.pohybX = 0; snake.pohybY = 1; } break;
            case 'a': if (snake.pohybX != 1) { snake.pohybX = -1; snake.pohybY = 0; } break;
            case 'd': if (snake.pohybX != -1) { snake.pohybX = 1; snake.pohybY = 0; } break;
        }
    }
}
