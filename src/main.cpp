#include "textProcessing.hpp"
#include "hashtable.hpp"

const size_t NUM_HASH_FUNC = 5;

int main (int argc, char * argv[])
{
    MY_ASSERT (argc != 2, "You should enter 2 arguments: \n 1) the name of using programm; \n 2) the name of the file to be proccessed");

    textInfo_t textInfo = getArrayWords (argv[1]);
    printf ("after getArrayWords func\n");

    size_t (*hashFuncts[])(char * word) =  {hashFunc1, hashFunc2, hashFunc3, hashFunc4, hashFunc5};
    
    char buf[60] = {};
    for (int i = 0; i < NUM_HASH_FUNC; i++)
    {
        printf ("num of hashfunc = %d\n", i);
        sprintf (buf, "./build/table%d.csv", i);
        createHashTable (textInfo, hashFuncts[i], buf);
    }

    return 0;
}

