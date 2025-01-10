#ifndef PLOCHA_H
#define PLOCHA_H

#define MAX_RIADKY 100
#define MAX_STLPCE 100
#define MAX_JEDLO 100

#include <stdbool.h>

struct Jedlo {
    int x, y;
    int zjedene;
};

struct Plocha {
    int riadky;
    int stlpce;
    int pocet_jedla;
	int pocet_aktualneho_jedla;
    char policko[MAX_RIADKY * MAX_STLPCE];
	char level[MAX_RIADKY * MAX_STLPCE];
	struct Jedlo jedlo[MAX_JEDLO];
};

void inicializuj_plochu(struct Plocha* plocha, int riadky, int stlpce, int pocet_jedla, int typ);
void nastav_jedlo(struct Plocha* plocha);
void vykresli_jedlo(struct Plocha* plocha);
void nove_jedlo(struct Plocha* plocha, int x, int y);
void random_nove_jedlo(struct Plocha* plocha);
void napln_plochu(struct Plocha* plocha);
void nastav_level(struct Plocha* plocha ,int typ);
void level_ziadne_steny(struct Plocha* plocha);
void level_random_walls(struct Plocha* plocha);
int flood_fill(int x, int y, int riadky, int stlpce, bool* navstivene, char* level);
bool is_valid(int x, int y, int riadky, int stlpce, bool* navstivene, char* level);

#endif 
