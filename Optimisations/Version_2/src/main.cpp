#define NDEBUG
#include "./text/textProcessing.hpp"
#include "./hash/hashtable.hpp"
#include "./hash/hashfuncs.hpp"

#include <time.h>

const size_t NUM_ITERS     = 100000000;
const size_t NUM_HASH_FUNC = 7;

int main (int argc, char * argv[])
{
    textInfo_t textInfo = getArrayWords (argv[1]);
    htMainElem ht = {};
    ht = createHashTable (textInfo, hashBkdr, "none.csv");
    double secs = 0;

    alignas (32) char * testWord = (char *) calloc (1, 32*sizeof(char));
    char * testWord32 = (char *) memmove(testWord, "word", strlen(testWord));

    for (size_t j = 0; j < NUM_ITERS; j++)
    {
        clock_t start = clock();
        htFind (ht, testWord32, hashBkdr);
        
        clock_t end = clock();
        
        secs += (double)(end-start)/CLOCKS_PER_SEC;
    }
    printf ("The time: %.3f seconds\n", secs);

    textDestructor (textInfo);

    htDestructor (&ht);

    return 0;
}

