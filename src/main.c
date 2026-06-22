#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "common.h"
#include "gauge.h"

void init_rand(void) {
    struct timeval tv;

    gettimeofday(&tv, NULL);
    srand(tv.tv_usec); // Init with microseconds, not seconds
}

char get_random_letter(void) {
    char result = (rand() % (MAX_CHAR - MIN_CHAR + 1)) + MIN_CHAR;

    return result;
}

struct letter_pair get_letter_pair() {
    struct letter_pair result = {get_random_letter(), get_random_letter()};

    if (result.first == result.second) {
        result.second = ((result.second - MIN_CHAR + 1) % 26) + MIN_CHAR;
    }

    return result;
}

void print_usage(void) { puts(USAGE_STRING); }

void print_invalid_answer(void) { puts(INVALID_ANSWER_STRING); }

void print_question(struct letter_pair pair) {
    printf("Which letter comes first in the alphabet: \033[1;33m%c\033[0m or "
           "\033[1;33m%c\033[0m?\n",
           pair.first, pair.second);
}

enum ANSWER_VALIDITY get_result(struct letter_pair pair, char *answer) {
    if (strlen(answer) != 2) {
        print_invalid_answer();
        return ANSWER_INVALID;
    }

    int user_answer = toupper((unsigned char)answer[0]);

    if (user_answer != pair.first && user_answer != pair.second) {
        print_invalid_answer();
        return ANSWER_INVALID;
    }

    char correct = pair.first <= pair.second ? pair.first : pair.second;

    if (user_answer == correct) {
        puts(CORRECT_STRING);
        return ANSWER_CORRECT;
    }

    puts(INCORRECT_STRING);
    return ANSWER_INCORRECT;
}

void game_loop(void) {
    struct letter_pair pair = {0};
    char *answer = NULL;
    size_t answer_len = 0;
    ssize_t answer_read = 0;
    enum ANSWER_VALIDITY validity = ANSWER_INVALID;

    for (;;) {
        pair = get_letter_pair();
        print_question(pair);

        validity = ANSWER_INVALID;
        while (validity == ANSWER_INVALID) {
            answer_read = getline(&answer, &answer_len, stdin);
            if (answer_read == -1 || strncmp(answer, "quit", 4) == 0) {
                free(answer);
                return;
            }

            validity = get_result(pair, answer);
        }
        print_gauge(pair);
    }
}

int main(void) {
    init_rand();
    print_usage();
    game_loop();

    return 0;
}
