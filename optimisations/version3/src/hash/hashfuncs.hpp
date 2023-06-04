#ifndef HASHFUNC_HPP
#define HASHFUNC_HPP

#include <stdio.h>
#include <string.h>
#include <immintrin.h>
#include <stdlib.h>
#include "../../logs/logs.hpp"

size_t              hashBkdr        (char * word);
extern "C" size_t   hashBkdrAsm     (char * word);
size_t              hashCrc32       (char * word);
extern "C" size_t   hashCrc32Asm    (char * word);

#endif 