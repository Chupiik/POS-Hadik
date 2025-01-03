#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "snake.h"
#include "plocha.h"
#include "input.h"
#include "hra.h"

int main(int argc, char **argv)
{
    srand(time(0));
	
	printf("\033[2J");
	
    nastav_snake();
    nastav_jedlo();

    while (!jeGameOver) {
        napln_plochu();
        vykresli_jedlo();
        vykresli_snake();
        pravidla_hry();
        reset_cursor();
        printf("Score: %d\n", snake.dlzka);
        print_plocha();
        if (!jeGameOver) {
            vykonaj();
            pohni_snake();
        }
        usleep(200000); 
    }

    printf("Game Over, Final score: %d\n", snake.dlzka);

    return 0;
}
