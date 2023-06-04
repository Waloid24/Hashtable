#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <math.h>
#include "MY_ASSERT.h"
#include "../list/listPtr.h"
#include "../text/textProcessing.hpp"

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
size_t hashFunc6 (char * word);
size_t hashFunc7 (char * word);
size_t hashFunc8 (char * word);

struct listElement_t * htFind   (htMainElem hashtable, char * word, size_t (hashFuncs) (char * word));
htMainElem createHashTable      (textInfo_t textInfo, size_t (hashFuncts) (char * word), char * nameCsvFile);
void htDestructor               (htMainElem * ht);

const size_t STANDART_SIZE_TABLE = 6000;
const double MULTIPIER = (sqrt(5)-1)/2;

#endif