#ifndef COMMON_H
#define COMMON_H

#define MIN_CHAR 'A'
#define MAX_CHAR 'Z'

#define CORRECT_STRING "Correct!"
#define INCORRECT_STRING "Wrong..."

#define USAGE_STRING                                                           \
    "When you're done playing, press CTRL+C, CTRL+D or type \"quit\".\n"

#define INVALID_ANSWER_STRING                                                  \
    "Please answer with either of the letters above.\n"

#define GAUGE_STRING "[--------------------------]\n"

struct letter_pair {
    char first;
    char second;
};

enum ANSWER_VALIDITY { ANSWER_INVALID, ANSWER_INCORRECT, ANSWER_CORRECT };

#endif
