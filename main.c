#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define MIN 'A'
#define MAX 'Z'

#define CORRECT_STRING "Correct!"
#define INCORRECT_STRING "Wrong..."

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

    if (result.first == result.second) {
        result.second = ((result.second - MIN + 1) % 26) + MIN;
    }

    return result;
}

void print_question(struct letter_pair pair) {
    printf("Which letter comes first in the alphabet: %c or %c?\n", pair.first,
           pair.second);
}

void print_invalid_answer(void) {
    printf("Please answer with either of the letters above.\n");
}

enum ANSWER_VALIDITY { ANSWER_INVALID, ANSWER_INCORRECT, ANSWER_CORRECT };

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

void game_loop() {
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
    }
}

int main(void) {
    init_rand();
    game_loop();

    return 0;
}
