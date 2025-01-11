#include "hra.h"

void init_hra(struct Hra* hra, int riadky, int stlpce, int pocet_jedla, int typ_plochy) {
	//printf("Inicializuj hru.\n");
    pthread_mutex_init(&hra->game_mutex, NULL);
	//printf("Inicializuj plochu.\n");
	inicializuj_plochu(&hra->plocha, riadky, stlpce, pocet_jedla, typ_plochy);
    napln_plochu(&hra->plocha);
	hra->isPaused= 0;
}

void nastav_snake(struct Snake *snake, struct Hra *hra) {
    snake->dlzka = 1;
	for (int i = 0; i < MAX_DLZKA; i++) {
		snake->cast[0].x = 0;
		snake->cast[0].y = 0;
	}
    snake->cast[0].x = 1 + rand() % (hra->plocha.stlpce - 2);
    snake->cast[0].y = 1 + rand() % (hra->plocha.riadky - 2);
	snake->pohybX = 0;
	snake->pohybY = 0;
}

void pravidla_hry(struct Snake *snake, struct Hra* hra, int *jeGameOver) {
	char narazilNa = hra->plocha.policko[snake->cast[0].y * hra->plocha.stlpce + snake->cast[0].x];
	if (snake->pohybX != 0 || snake->pohybY !=0) {
		if (narazilNa == '+') {
			for (int i = 0; i < MAX_JEDLO; i++) {
				if (!hra->plocha.jedlo[i].zjedene &&
					hra->plocha.jedlo[i].x == snake->cast[0].x &&
					hra->plocha.jedlo[i].y == snake->cast[0].y) {
						zjedz_jedlo(&hra->plocha, snake, i);
					}
			}
		}
		
		if (narazilNa == '#' || narazilNa == 'O' || narazilNa == '@') {
			*jeGameOver = 1;
			for (int i = 0; i < snake->dlzka; i++) {
				nove_jedlo(&hra->plocha, snake->cast[i].x, snake->cast[i].y);
			}
		}
	}
}

void zjedz_jedlo(struct Plocha* plocha,struct Snake* snake, int index_jedla) {
	plocha->jedlo[index_jedla].zjedene = 1;
	plocha->pocet_aktualneho_jedla--;
	snake->cast[snake->dlzka].x = snake->cast[snake->dlzka-1].x;
	snake->cast[snake->dlzka].y = snake->cast[snake->dlzka-1].y;
	snake->dlzka++;
	random_nove_jedlo(plocha);
	//printf("Zjedol jedlo.\n");
}


void vykonaj_pohyb(char input, struct Snake *snake){
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