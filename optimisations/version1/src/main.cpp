#define NDEBUG
#include "./text/textProcessing.hpp"
#include "./hash/hashtable.hpp"
#include "../logs/logs.hpp"
#include "./hash/hashfuncs.hpp"

const size_t NUM_ITERS     = 1000;

int main (int argc, char * argv[])
{
    textInfo_t textInfo = getArrayWords ("./src/Text_avx.txt");
    htMainElem ht = {};

    for (size_t numFuncs = 0; numFuncs < 1; numFuncs++)
    {
        ht = createHashTable (textInfo, hashBkdr, "none.csv");
        printf ("textInfo.numWords = %d\n", textInfo.numWords);
        for (size_t numIters = 0; numIters < NUM_ITERS; numIters++)
        {
            for (size_t i = 0; i < textInfo.numWords; i++)
            {
                htFind (ht, textInfo.arrayWords[i]);
            }
        }
        htDestructor (&ht);
    }

    textDestructor (textInfo);
    
    return 0;
}
