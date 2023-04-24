#include "hashfuncs.hpp"

size_t hashBkdr_0 (char * word)
{
    unsigned int seed = 131;
    unsigned int hash = 0;

    while (*word)
    {
        hash = hash * seed + (*word++);
    }

    return (hash & 0x7FFFFFFF);
}
