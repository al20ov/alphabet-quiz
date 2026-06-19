#include "common.h"
#include <stdint.h>
#include <stdio.h>

void print_gauge(struct letter_pair pair) {
    putchar(' ');
    for (char i = MIN_CHAR; i <= MAX_CHAR; i += 1) {
        if (i == pair.first) {
            putchar(pair.first);
        } else if (i == pair.second) {
            putchar(pair.second);
        } else {
            putchar(' ');
        }
    }
    putchar('\n');

    putchar(' ');
    for (char i = MIN_CHAR; i <= MAX_CHAR; i += 1) {
        if (i == pair.first || i == pair.second) {
            putchar('|');
        } else {
            putchar(' ');
        }
    }
    putchar('\n');

    puts(GAUGE_STRING);

    fflush(stdout);
}
