#ifndef HASHFUNC_HPP
#define HASHFUNC_HPP

#include <stdio.h>
#include <string.h>
// #include "MY_ASSERT.h"
#include <stdlib.h>
#include <immintrin.h>
#include "../../logs/logs.hpp"

size_t            hashBkdr_0        (char * word);
extern "C" size_t hashBkdr_1        (__m256i * word);

#endif 