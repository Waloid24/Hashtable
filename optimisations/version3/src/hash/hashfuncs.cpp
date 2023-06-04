#include "hashfuncs.hpp"

size_t hashBkdr (char * word)
{
    unsigned int seed = 131;
    unsigned int hash = 0;

    while (*word)
    {
        hash = hash * seed + (*word++);
    }

    return (hash & 0x7FFFFFFF);
}

size_t hashCrc32 (char * str)
{
    __m256i elem = _mm256_load_si256( (__m256i*) str);

    size_t hash = 0;
    hash = _mm_crc32_u64 ( hash, _mm256_extract_epi64 (elem, 3));
    hash = _mm_crc32_u64 ( hash, _mm256_extract_epi64 (elem, 2));
    hash = _mm_crc32_u64 ( hash, _mm256_extract_epi64 (elem, 1));
    hash = _mm_crc32_u64 ( hash, _mm256_extract_epi64 (elem, 0));
    
    return hash;
}
