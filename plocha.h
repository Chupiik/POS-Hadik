#ifndef PLOCHA_H
#define PLOCHA_H

#define riadky 30
#define stlpce 60
#define pocet_jedla 20

struct Plocha {
    char policko[stlpce * riadky];
};

void napln_plochu(struct Plocha*);
void reset_cursor(void);

#endif // PLOCHA_H