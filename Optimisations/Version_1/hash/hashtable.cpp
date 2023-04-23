#define NDEBUG
#include "hashtable.hpp"

static void         htInsert        (listPtr_t * elem, char * word);
static htMainElem   htInit          (void);

const size_t STANDART_SIZE_TABLE = 6000;

htMainElem createHashTable (textInfo_t textInfo, size_t (hashFuncs) (char * word), char * nameCsvFile)
{
    htMainElem ht = htInit ();
    size_t index = 0;
    char * word = nullptr;
    for (size_t i = 0; i < textInfo.numWords; i++)
    {
        word = textInfo.arrayWords[i];
        index = hashFuncs (word) % ht.capacity;
        htInsert (&(ht.htElem[index]), word);
    }

    return ht;
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


    for (size_t i = 0; i < lengthList; i++)
    {  
        char * data = listElem->data;
        int resultCmp = memcmp (data, word, strlen(data)+1);
        
        if (resultCmp == 0)
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
    for (size_t i = 0; i < lengthList; i++, listElem = listElem->next)
    {
        if (strcmp(listElem->data, word) == 0)
        {
            return; 
        }
    }
    listPushFront(elem, word);
}

void htDestructor (htMainElem * ht)
{
    MY_ASSERT (ht == nullptr, "Unable to get access to the table");
    size_t capacity = ht->capacity;
    for (size_t i = 0; i < capacity; i++)
    {
        listDestructor (&(ht->htElem[i]));
    }
    free (ht->htElem);
}

size_t hashBkdr (char * word)
{
    MY_ASSERT (word == nullptr, "There is no access to the word");

    unsigned int seed = 131;
    unsigned int hash = 0;

    while (*word){
        hash = hash * seed + (*word++);
    }

    return (hash & 0x7FFFFFFF);
}