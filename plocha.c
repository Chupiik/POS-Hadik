#include <stdio.h>
#include <stdlib.h>
#include "plocha.h"

void inicializuj_plochu(struct Plocha* plocha, int riadky, int stlpce, int pocet_jedla, int typ) {
    if (riadky > MAX_RIADKY || stlpce > MAX_STLPCE) {
        fprintf(stderr, "Error: Board size exceeds maximum allowed dimensions (%dx%d).\n", MAX_RIADKY, MAX_STLPCE);
        return;
    }
    plocha->riadky = riadky;
    plocha->stlpce = stlpce;
	if (pocet_jedla > MAX_JEDLO) {
		fprintf(stderr, "Error: The number of food exceeds maximum allowed (%d).\n", MAX_JEDLO);
        return;
	}
    plocha->pocet_jedla = pocet_jedla;
	
	nastav_level(plocha, typ);
	
	nastav_jedlo(plocha);
}

void nastav_level(struct Plocha* plocha ,int typ) {
	if (typ == 1) {
		level_ziadne_steny(plocha);
	} else if (typ == 2) {
		level_ziadne_steny(plocha);
		level_random_walls(plocha);
	}
}

void level_ziadne_steny(struct Plocha* plocha) {
	for (int y = 0; y < plocha->riadky; y++) {
		for (int x = 0; x < plocha->stlpce; x++) {
			if (x == 0 || x == plocha->stlpce - 1) {
				plocha->level[y * plocha->stlpce + x] = '|';
			} else if (y == 0 || y == plocha->riadky -1) {
				plocha->level[y * plocha->stlpce + x] = '-';
			} else {
				plocha->level[y * plocha->stlpce + x] = ' ';
			}
		}
	}
}

void napln_plochu(struct Plocha* plocha) {
    for (int y = 0; y < plocha->riadky; y++) {
        for (int x = 0; x < plocha->stlpce; x++) {
			plocha->policko[y * plocha->stlpce + x] = plocha->level[y * plocha->stlpce + x];
        }
    }
}

void nastav_jedlo(struct Plocha* plocha) {
    for (int i = 0; i < plocha->pocet_jedla; i++) {
			plocha->jedlo[i].x = 1 + rand() % (plocha->stlpce - 2);
			plocha->jedlo[i].y = 1 + rand() % (plocha->riadky - 2);
			plocha->jedlo[i].zjedene = 0;
    }
}

void vykresli_jedlo(struct Plocha* plocha) {
    for (int i = 0; i < plocha->pocet_jedla; i++) {
        if (!plocha->jedlo[i].zjedene) {
            plocha->policko[plocha->jedlo[i].y * plocha->stlpce + plocha->jedlo[i].x] = '+';
        }
    }
}

bool is_valid(int x, int y, int riadky, int stlpce, bool* navstivene, char* level) {
    return x >= 0 && x < stlpce && y >= 0 && y < riadky &&
           level[y * stlpce + x] == ' ' && !navstivene[y * stlpce + x];
}

int flood_fill(int x, int y, int riadky, int stlpce, bool* navstivene, char* level) {
    if (!is_valid(x, y, riadky, stlpce, navstivene, level)) {
		return 0;
	}
	
    navstivene[y * stlpce + x] = true;
    int count = 1;

    count += flood_fill(x + 1, y, riadky, stlpce, navstivene, level);
    count += flood_fill(x - 1, y, riadky, stlpce, navstivene, level);
    count += flood_fill(x, y + 1, riadky, stlpce, navstivene, level);
    count += flood_fill(x, y - 1, riadky, stlpce, navstivene, level);

    return count;
}

void level_random_walls(struct Plocha* plocha) {
	printf("Started generating \n");
    int riadky = plocha->riadky;
    int stlpce = plocha->stlpce;
    char* level = plocha->level;
    int pocet_policok = riadky * stlpce;
    int max_steny = pocet_policok / 20;

    for (int y = 0; y < riadky; y++) {
        for (int x = 0; x < stlpce; x++) {
            level[y * stlpce + x] = ' ';
        }
    }

    for (int i = 0; i < max_steny; i++) {
		int x;
		int y;
        do {
            x = 1 + rand() % (stlpce - 2);
            y = 1 + rand() % (riadky - 2);
        } while (level[y * stlpce + x] == '#');
        if (level[y * stlpce + x] == ' ' && !(x == 0 || y == 0 || x == stlpce - 1 || y == riadky - 1)) {
            level[y * stlpce + x] = '#';
        }
    }

    bool* navstivene = calloc(pocet_policok, sizeof(bool));
    int dostupne_policka = flood_fill(1, 1, riadky, stlpce, navstivene, level);
    free(navstivene);
	printf("Generated map \n");
    if (dostupne_policka != pocet_policok - max_steny) {
        level_random_walls(plocha);
    }
	for (int y = 0; y < plocha->riadky; y++) {
		for (int x = 0; x < plocha->stlpce; x++) {
			if (x == 0 || x == plocha->stlpce - 1) {
				plocha->level[y * plocha->stlpce + x] = '|';
			} else if (y == 0 || y == plocha->riadky -1) {
				plocha->level[y * plocha->stlpce + x] = '-';
			}
		}
	}
}