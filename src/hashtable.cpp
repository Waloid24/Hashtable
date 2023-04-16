#include "hashtable.hpp"

static void       htInsert      (listPtr_t * elem, char * word);
static htMainElem htInit        (void);
static void dropStat (htMainElem hashtable, char * nameCsvFile);

htMainElem createHashTable (textInfo_t textInfo, size_t (hashFuncts) (char * word), char * nameCsvFile)
{
    htMainElem ht = htInit ();
    size_t index = 0;
    for (size_t i = 0; i < textInfo.numWords; i++)
    {
        index = hashFuncts (textInfo.arrayWords[i]) % ht.capacity;
        
        htInsert (&(ht.htElem[index]), textInfo.arrayWords[i]);
    }
    dropStat (ht, nameCsvFile);

    return ht;
}

static void dropStat (htMainElem hashtable, char * nameCsvFile)
{    
    FILE * table = fopen (nameCsvFile, "w");
    MY_ASSERT (table == nullptr, "Unable to create the file");

    for (int i = 0; i < hashtable.capacity; i++)
    {
        fprintf (table, "%lu\n", hashtable.htElem[i].size);
    }
}

static htMainElem htInit (void)
{
    htMainElem hashtable = {};
    hashtable.size      = 0;
    hashtable.capacity  = STANDART_SIZE_TABLE;
    hashtable.htElem     = (listPtr_t *) calloc (hashtable.capacity, sizeof(listPtr_t));
    MY_ASSERT (hashtable.htElem == nullptr, "Unable to create a hashtable");
    
    for (int i = 0; i < hashtable.capacity; i++)
    {
        listConstruct (&(hashtable.htElem[i]));
    }
    return hashtable;
}

static void htInsert (listPtr_t * elem, char * word)
{
    listPushFront(elem, word);
}

size_t hashFunc1 (char * word)
{
    MY_ASSERT (word == nullptr, "There is no access to the word");

    return 1;
}

size_t hashFunc2 (char * word)
{
    MY_ASSERT (word == nullptr, "There is no access to the word");
    printf ("\033[3;41m hashFunc2: word = %s \033[0m\n", word);
    return word[0];
}

size_t hashFunc3 (char * word)
{
    MY_ASSERT (word == nullptr, "There is no access to the word");

    return strlen(word);
}

size_t hashFunc4 (char * word)
{
    MY_ASSERT (word == nullptr, "There is no access to the word");
    size_t lengthWord = strlen (word);
    size_t sum = 0;
    for (int i = 0; i < lengthWord; i++)
    {
        sum += word[i];
    }

    return sum;
}

size_t hashFunc5 (char * word)
{
    MY_ASSERT (word == nullptr, "There is no access to the word");

    size_t index = (size_t) round(MULTIPIER*word[0]);
    printf ("In func hashFunc5: index = %lu, (%f) \n", index, MULTIPIER*word[0]);

    return index;
}