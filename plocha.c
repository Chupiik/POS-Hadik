#include <stdio.h>
#include <stdlib.h>
#include "plocha.h"

void inicializuj_plochu(struct Plocha* plocha, int riadky, int stlpce, int pocet_jedla) {
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
	nastav_jedlo(plocha);
}

void napln_plochu(struct Plocha* plocha) {
    for (int y = 0; y < plocha->riadky; y++) {
        for (int x = 0; x < plocha->stlpce; x++) {
            plocha->policko[y * plocha->stlpce + x] =
                (x == 0 || y == 0 || x == plocha->stlpce - 1 || y == plocha->riadky - 1) ? '#' : ' ';
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
