#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define MIN 'A'
#define MAX 'Z'

#define CORRECT_STRING "Correct!\n"
#define INCORRECT_STRING "Wrong...\n"

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

void print_question(struct letter_pair pair) {
    printf("Which letter comes first in the alphabet: %c or %c?\n", pair.first,
           pair.second);
}

void print_invalid_answer(void) {
    printf("Please answer with either of the letters above.\n");
}

enum MATCH_LEVEL { NONE, FIRST, SECOND };

enum MATCH_LEVEL get_match(struct letter_pair pair, char sanitized_answer) {
    if (sanitized_answer == pair.first) {
        return FIRST;
    } else if (sanitized_answer == pair.second) {
        return SECOND;
    } else {
        return NONE;
    }
}

enum ANSWER_VALIDITY { ANSWER_INVALID, ANSWER_INCORRECT, ANSWER_CORRECT };

enum ANSWER_VALIDITY get_result(struct letter_pair pair, char *answer) {
    size_t real_answer_len = strlen(answer);
    enum MATCH_LEVEL match = NONE;

    if (real_answer_len != 2) {
        print_invalid_answer();
        return ANSWER_INVALID;
    }
    match = get_match(pair, (char)toupper(answer[0]));

    if (match == NONE) {
        print_invalid_answer();
        return ANSWER_INVALID;
    }

    if (match == FIRST && pair.first <= pair.second) {
        puts(CORRECT_STRING);
        return ANSWER_CORRECT;
    }

    if (match == SECOND && pair.second <= pair.first) {
        puts(CORRECT_STRING);
        return ANSWER_CORRECT;
    }

    puts(INCORRECT_STRING);
    return ANSWER_INCORRECT;
}

void game_loop() {
    struct letter_pair pair = {};
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
    }
}

int main(void) {
    init_rand();
    game_loop();

    return 0;
}
