#include "common.h"
#include <stdio.h>

void print_gauge(struct letter_pair pair) {
    putchar(' ');
    for (char i = MIN_CHAR; i <= MAX_CHAR; i += 1) {
        putchar((i == pair.first || i == pair.second) ? i : ' ');
    }
    putchar('\n');

    putchar(' ');
    for (char i = MIN_CHAR; i <= MAX_CHAR; i += 1) {
        putchar((i == pair.first || i == pair.second) ? '|' : ' ');
    }
    putchar('\n');

    puts(GAUGE_STRING);

    fflush(stdout);
}
