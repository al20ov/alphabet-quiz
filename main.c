#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define MIN 'A'
#define MAX 'Z'

struct letter_pair {
    char first;
    char second;
};

void init_rand() {
    struct timeval tv;

    gettimeofday(&tv, NULL);
    srand(tv.tv_usec); // Init with microseconds, not seconds
}

char get_random_letter() {
    char result = (rand() % (MAX - MIN + 1)) + MIN;

    return result;
}

struct letter_pair get_letter_pair() {
    struct letter_pair result = {get_random_letter(), get_random_letter()};

    return result;
}

void print_instructions() { puts("\n"); }

void print_question(struct letter_pair pair) {
    printf("Which letter comes first in the alphabet: %c or %c\n? ", pair.first,
           pair.second);
}

void print_invalid_answer(void) {
    printf("Please answer with a single letter\n");
}

int get_result(struct letter_pair pair, char *answer) {
    size_t real_answer_len = strlen(answer);

    if (real_answer_len != 2) {
        print_invalid_answer();
        return -1;
    }

    return 0;
}

void game_loop() {
    struct letter_pair pair = {};
    char *answer = NULL;
    size_t answer_len = 0;
    ssize_t answer_read = 0;

    for (;;) {
        pair = get_letter_pair();
        print_question(pair);
        answer_read = getline(&answer, &answer_len, stdin);

        if (answer_read == -1 || strncmp(answer, "quit", 4) == 0) {
            free(answer);
            return;
        }

        get_result(pair, answer);
    }
}

int main(void) {
    init_rand();
    game_loop();

    return 0;
}
