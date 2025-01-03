#include <stdio.h>
#include "plocha.h"

char plocha[stlpce * riadky];

void napln_plochu() {
    for (int y = 0; y < riadky; y++) {
        for (int x = 0; x < stlpce; x++) {
            plocha[y * stlpce + x] = (x == 0 || y == 0 || x == stlpce - 1 || y == riadky - 1) ? '#' : ' ';
        }
    }
}

void reset_cursor() {
    printf("\033[H");
}

void print_plocha() {
    for (int y = 0; y < riadky; y++) {
        for (int x = 0; x < stlpce; x++) {
            putchar(plocha[y * stlpce + x]);
        }
        putchar('\n');
    }
}
