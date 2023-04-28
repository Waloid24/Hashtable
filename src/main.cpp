#define NDEBUG
#include "./text/textProcessing.hpp"
#include "./hash/hashtable.hpp"
#include "../logs/logs.hpp"
#include "./hash/hashfuncs.hpp"
#include <time.h>

const size_t NUM_ITERS     = 1000;
const size_t NUM_HASH_FUNC = 7;

int main (int argc, char * argv[])
{
    textInfo_t textInfo = getArrayWords ("./src/Text.txt");
    htMainElem ht = {};

    // struct listElement_t * (*htFind[]) (htMainElem hashtable, char * word) = {htFind_0, htFind_3, htFind_1, htFind_2};
// printf ("lol0\n");
    struct listElement_t * (*htFind[]) (htMainElem hashtable, __m256i * word) = {htFind_4, htFind_5};

    // const char * phrases[] = {"hashBkdr_0 | memcmp",
    //                           "hashBkdr_0 | memcmpAsm",
    //                           "hashBkdr_1 | memcmp",
    //                           "hashBkdr_1 | memcmpAsm"};
    const char * phrases[] = {"hashBkdr_1 | memcmpAvx | AVX",
                              "hashBkdr_1 | memcmp | AVX"};

    for (size_t numFuncs = 0; numFuncs < 2; numFuncs++)
    {
        ht = createHashTable (textInfo, hashBkdr_1, "none.csv");
        double secs = 0;
        __m256i * testWord =  textInfo.ar256Words[8];
        for (size_t numIt = 0; numIt < 100000000; numIt++)
        {
                clock_t start = clock();
                htFind[numFuncs] (ht, testWord);
                clock_t end = clock();
                secs += (double)(end-start)/CLOCKS_PER_SEC;
        }
        
        _$log ("==============find 1 word=================\n");
        _$log ("%s\n \t time: %.3f seconds\n", phrases[numFuncs], secs);

        htDestructor (&ht);
    }

    textDestructor (textInfo);
    

    return 0;
}
