#include <stdlib.h>
#include "hra.h"
#include <string.h>
#include <stdio.h>

void init_hra(struct Hra* hra, int riadky, int stlpce, int pocet_jedla) {
    pthread_mutex_init(&hra->game_mutex, NULL);
	inicializuj_plochu(&hra->plocha, riadky, stlpce, pocet_jedla);
    napln_plochu(&hra->plocha);
}

void nastav_snake(struct Snake *snake, struct Hra *hra) {
    snake->dlzka = 1;
    snake->cast[0].x = 1 + rand() % (hra->plocha.stlpce - 2);
    snake->cast[0].y = 1 + rand() % (hra->plocha.riadky - 2);
	snake->pohybX = 0;
	snake->pohybY = 0;
}

void pravidla_hry(struct Snake *snake, struct Hra* hra, int *jeGameOver) {
	char narazilNa = hra->plocha.policko[snake->cast[0].y * hra->plocha.stlpce + snake->cast[0].x];
	
	if (narazilNa == '+') {
		for (int i = 0; i < hra->plocha.pocet_jedla; i++) {
			if (!hra->plocha.jedlo[i].zjedene &&
				hra->plocha.jedlo[i].x == snake->cast[0].x &&
				hra->plocha.jedlo[i].y == snake->cast[0].y) {
				hra->plocha.jedlo[i].zjedene = 1;
				snake->dlzka++;
				hra->plocha.jedlo[i].x = 1 + rand() % (hra->plocha.stlpce - 2);
				hra->plocha.jedlo[i].y = 1 + rand() % (hra->plocha.riadky - 2);
				hra->plocha.jedlo[i].zjedene = 0;
			}
		}
	}
	
    //printf("NARAZIL: %c \n", plocha->policko[snake->cast[0].y * stlpce + snake->cast[0].x]);
	if (narazilNa == '#' || narazilNa == 'O' || narazilNa == '@') {
		*jeGameOver = 1;
	}
    
}


void vykonaj_pohyb(char input, struct Snake *snake){
    if (input != -1) {
        switch (input) {
            case 'w': 
				if (snake->pohybY != 1) {
					snake->pohybX = 0; 
					snake->pohybY = -1; 
				}
				break;
            case 's': 
				if (snake->pohybY != -1) {
					snake->pohybX = 0; 
					snake->pohybY = 1; 
				}
				break;
            case 'a': 
				if (snake->pohybX != 1) {
					snake->pohybX = -1; 
					snake->pohybY = 0; 
				}
				break;
            case 'd': 
				if (snake->pohybX != -1) {
					snake->pohybX = 1; 
					snake->pohybY = 0; 
				}
				break;
        }
    }
}