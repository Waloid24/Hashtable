#include "./text/textProcessing.hpp"
#include "./hash/hashtable.hpp"

const size_t NUM_HASH_FUNC = 8;

int main (int argc, char * argv[])
{
    MY_ASSERT (argc != 2, "You should enter 2 arguments: \n 1) the name of using programm; \n 2) the name of the file to be proccessed");

    textInfo_t textInfo = getArrayWords (argv[1]);

    size_t (*hashFuncs[])(char * word) =  {hashFunc1, hashFunc2, hashFunc3, hashFunc4, hashFunc5, hashFunc6, hashFunc7, hashFunc8};
    htMainElem ht = {};

    char buf[60] = {};
    for (size_t i = 0; i < NUM_HASH_FUNC; i++)
    {
        sprintf (buf, "./tables/table%lu.csv", i+1);
        ht = createHashTable (textInfo, hashFuncs[i], buf);
        htDestructor (&ht);
    }

    free (textInfo.arrayWords);

    return 0;
}

