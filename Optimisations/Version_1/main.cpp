#define NDEBUG
#include "./text/textProcessing.hpp"
#include "./hash/hashtable.hpp"
#include "./hash/hashfuncs.hpp"

#include <time.h>

const size_t NUM_ITERS     = 100000000;
const size_t NUM_HASH_FUNC = 7;

int main (int argc, char * argv[])
{
    textInfo_t textInfo = getArrayWords ("./src/Text.txt");

    htMainElem ht = {}; 
    char buf[60] = {};
    ht = createHashTable (textInfo, hashBkdr, buf);
    double secs = 0;

    for (size_t j = 0; j < NUM_ITERS; j++)
    {
        clock_t start = clock();
        htFind (ht, "SomeWord", hashBkdr);
        
        clock_t end = clock();
        
        secs += (double)(end-start)/CLOCKS_PER_SEC;
    }
    printf ("The time: %.3f seconds\n", secs);
    
    htDestructor (&ht);

    free (textInfo.arrayWords);

    return 0;
}

