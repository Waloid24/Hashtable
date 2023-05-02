#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <math.h>
#include <immintrin.h>
#include <stdlib.h>
#include "../list/listPtr.h"
#include "../text/textProcessing.hpp"
#include "../../logs/logs.hpp"

struct hashtableMainElem
{
    size_t capacity;
    listPtr_t * htElem;
};
typedef struct hashtableMainElem htMainElem;

struct listElement_t * htFind              (htMainElem hashtable, char * word);
htMainElem             createHashTable     (textInfo_t textInfo, size_t (hashFuncts) (char * word), char * nameCsvFile);
void                   htDestructor        (htMainElem * ht);

#endif