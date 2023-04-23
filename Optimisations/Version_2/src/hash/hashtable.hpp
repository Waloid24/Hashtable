#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <math.h>
#include "MY_ASSERT.h"
#include "../list/listPtr.h"
#include "../text/textProcessing.hpp"
#include <immintrin.h>

struct hashtableMainElem
{
    size_t capacity;
    listPtr_t * htElem;
};
typedef struct hashtableMainElem htMainElem;

struct listElement_t *  htFind              (htMainElem hashtable, char * word, size_t (hashFuncs) (char * word));
htMainElem              createHashTable     (textInfo_t textInfo, size_t (hashFuncts) (char * word), char * nameCsvFile);
void                    htDestructor        (htMainElem * ht);

#endif