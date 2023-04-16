#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <math.h>
#include "MY_ASSERT.h"
#include "listPtr.h"
#include "textProcessing.hpp"

struct hashtableMainElem
{
    size_t size;
    size_t capacity;
    listPtr_t * htElem;
};
typedef struct hashtableMainElem htMainElem;

size_t hashFunc1 (char * word);
size_t hashFunc2 (char * word);
size_t hashFunc3 (char * word);
size_t hashFunc4 (char * word);
size_t hashFunc5 (char * word);

const size_t STANDART_SIZE_TABLE = 8000;
const double MULTIPIER = (sqrt(5)-1)/2;

htMainElem createHashTable (textInfo_t textInfo, size_t (hashFuncts) (char * word), char * nameCsvFile);

#endif