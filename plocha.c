#include <stdio.h>
#include "plocha.h"

void napln_plochu(struct Plocha* plocha) {
    for (int y = 0; y < riadky; y++) {
        for (int x = 0; x < stlpce; x++) {
            plocha->policko[y * stlpce + x] = (x == 0 || y == 0 || x == stlpce - 1 || y == riadky - 1) ? '#' : ' ';
        }
    }
}

void reset_cursor() {
    printf("\033[H");
}