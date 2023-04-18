#ifndef TEXTPROCESSING_H
#define TEXTPROCESSING_H

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include "MY_ASSERT.h"

struct textInfo {
    size_t numWords;
    char ** arrayWords;
};
typedef struct textInfo textInfo_t;

textInfo_t getArrayWords (const char * fileName);

#endif