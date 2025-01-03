#ifndef PLOCHA_H
#define PLOCHA_H

#define riadky 30
#define stlpce 30
#define pocet_jedla 30

extern char plocha[stlpce * riadky];

void napln_plochu(void);
void reset_cursor(void);
void print_plocha(void);

#endif // PLOCHA_H
