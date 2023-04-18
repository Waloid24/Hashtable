#include "hashtable.hpp"

static void         htInsert        (listPtr_t * elem, char * word);
static htMainElem   htInit          (void);
static void         dropStat        (htMainElem hashtable, char * nameCsvFile);
static size_t       rol             (size_t num);
static size_t       ror             (size_t num);

htMainElem createHashTable (textInfo_t textInfo, size_t (hashFuncs) (char * word), char * nameCsvFile)
{
    htMainElem ht = htInit ();
    size_t index = 0;
    for (size_t i = 0; i < textInfo.numWords; i++)
    {
        index = hashFuncs (textInfo.arrayWords[i]) % ht.capacity;
        htInsert (&(ht.htElem[index]), textInfo.arrayWords[i]);
    }
    dropStat (ht, nameCsvFile);

    return ht;
}

static void dropStat (htMainElem hashtable, char * nameCsvFile)
{    
    FILE * table = fopen (nameCsvFile, "w");
    MY_ASSERT (table == nullptr, "Unable to create the file");

    fprintf (table, "size_of_lists\n");
    for (size_t i = 0; i < hashtable.capacity; i++)
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
    
    for (size_t i = 0; i < hashtable.capacity; i++)
    {
        listConstruct (&(hashtable.htElem[i]));
    }
    return hashtable;
}

struct listElement_t * htFind (htMainElem hashtable, char * word, size_t (hashFuncs) (char * word))
{
    MY_ASSERT (word == nullptr, "There is no access to this word");

    size_t index = hashFuncs(word) % hashtable.capacity;
    size_t lengthList = hashtable.htElem[index].size;
    listElement_t * listElem = hashtable.htElem[index].ptrToList->next; 
    // printf ("index = %lu, word = %s, lengthList = %zu\n", index, word, lengthList);
    for (size_t i = 0; i < lengthList; i++)
    {
        FILE * HTMLgraphDump = listCreateHTMLfileForGraphviz ("HTMLBuf.html");
        fprintf (stderr, "i = %lu\n", i);
        listGraphviz ((&hashtable.htElem[index]), 0, "GraphForPtrList.dot", HTMLgraphDump);
        char * data = listElem->data;
        // printf ("data = %p, %s\n", data, data);
        if (strcmp (data, word) == 0)
        {
            return listElem;
        }
        else
        {
            listElem = listElem->next;
        }
    }

    return nullptr;
}

static void htInsert (listPtr_t * elem, char * word)
{
    size_t lengthList = elem->size;
    listElement_t * listElem = elem->ptrToList->next;
    for (int i = 0; i < lengthList; i++, listElem = listElem->next)
    {
        if (strcmp(listElem->data, word) == 0)
        {
            return; 
        }
    }
    // printf ("insert word = %s\n", word);
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
    // printf ("\033[3;41m hashFunc2: word = %s \033[0m\n", word);
    return word[0];
}

size_t hashFunc3 (char * word)
{
    MY_ASSERT (word == nullptr, "There is no access to the word");
    // printf ("hashFunc3: word = %s\n", word);
    return strlen(word);
}

size_t hashFunc4 (char * word)
{
    MY_ASSERT (word == nullptr, "There is no access to the word");
    size_t lengthWord = strlen (word);
    size_t sum = 0;
    for (size_t i = 0; i < lengthWord; i++)
    {
        sum += word[i];
    }

    return sum;
}

size_t hashFunc5 (char * word)
{
    MY_ASSERT (word == nullptr, "There is no access to the word");

    size_t h = 0;
    size_t length = strlen(word);
    for (size_t i = 0; i < length; i++)
    {
        h = rol(h)^word[i];
    }
    return h;
}

size_t hashFunc6 (char * word)
{
    MY_ASSERT (word == nullptr, "There is no access to the word");

    size_t h = 0;
    size_t length = strlen(word);
    for (size_t i = 0; i < length; i++)
    {
        h = ror(h)^word[i];
    }
    return h;
}

size_t hashFunc7 (char * word)
{
    MY_ASSERT (word == nullptr, "There is no access to the word");

    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*word){
        hash = hash * seed + (*word++);
    }

    return (hash & 0x7FFFFFFF);
}

static size_t rol (size_t num)
{
    return (num << 1) | (num >> (sizeof(num)*8 - 1));
}

static size_t ror (size_t num)
{
    return (num >> 1) | (num << (sizeof(num)*8 - 1));
}