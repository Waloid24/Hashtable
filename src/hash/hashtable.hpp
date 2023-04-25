#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <math.h>
#include <immintrin.h>
// #include "MY_ASSERT.h"
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

struct listElement_t * htFind_0 (htMainElem hashtable, char * word);
struct listElement_t * htFind_1 (htMainElem hashtable, char * word);
struct listElement_t * htFind_2 (htMainElem hashtable, char * word);
struct listElement_t * htFind_3 (htMainElem hashtable, char * word);
struct listElement_t * htFind_4 (htMainElem hashtable, __m256i * word);
struct listElement_t * htFind_5 (htMainElem hashtable, __m256i * word);
// htMainElem             createHashTable     (textInfo_t textInfo, size_t (hashFuncts) (char * word), char * nameCsvFile);
htMainElem                createHashTable     (textInfo_t textInfo, size_t (hashFuncs) (__m256i * word), char * nameCsvFile);
void                   htDestructor        (htMainElem * ht);

#endif