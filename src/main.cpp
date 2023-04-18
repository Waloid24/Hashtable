#include "textProcessing.hpp"
#include "hashtable.hpp"

const size_t NUM_HASH_FUNC = 7;

int main (int argc, char * argv[])
{
    MY_ASSERT (argc != 2, "You should enter 2 arguments: \n 1) the name of using programm; \n 2) the name of the file to be proccessed");

    textInfo_t textInfo = getArrayWords (argv[1]);
    // printf ("after getArrayWords func\n");

    size_t (*hashFuncs[])(char * word) =  {hashFunc1, hashFunc2, hashFunc3, hashFunc4, hashFunc5, hashFunc6, hashFunc7};
    
    char buf[60] = {};
    for (int i = 0; i < NUM_HASH_FUNC; i++)
    {
        // printf ("num of hashfunc = %d\n", 3);
        sprintf (buf, "./build/table%d.csv", i+1);
        htMainElem ht = createHashTable (textInfo, hashFuncs[i], buf);
        // printf ("end of create table\n");
        // listElement_t * elem = htFind (ht, "prince", hashFunc7);
        // if (elem != nullptr)
        // {
        //     printf ("result: %s\n", elem->data);
        // }
    }

    return 0;
}

