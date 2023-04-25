#ifndef TEXTPROCESSING_H
#define TEXTPROCESSING_H

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdalign.h>
#include <stdlib.h>
#include <immintrin.h>
// #include "MY_ASSERT.h"
#include "../../logs/logs.hpp"

struct textInfo {
    size_t numWords;
    char * text;
    char ** arrayWords;
    __m256i ** ar256Words;
};
typedef struct textInfo textInfo_t;

textInfo_t getArrayWords    (const char * fileName);
void       textDestructor   (textInfo_t textInfo);

#endif