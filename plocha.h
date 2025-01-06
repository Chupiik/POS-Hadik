#ifndef PLOCHA_H
#define PLOCHA_H

#define MAX_RIADKY 100
#define MAX_STLPCE 100
#define MAX_JEDLO 100

struct Jedlo {
    int x, y;
    int zjedene;
};

struct Plocha {
    int riadky;
    int stlpce;
    int pocet_jedla;
    char policko[MAX_RIADKY * MAX_STLPCE];
	struct Jedlo jedlo[MAX_JEDLO];
};

void inicializuj_plochu(struct Plocha* plocha, int riadky, int stlpce, int pocet_jedla);
void nastav_jedlo(struct Plocha* plocha);
void vykresli_jedlo(struct Plocha* plocha);
void napln_plochu(struct Plocha* plocha);

#endif 
