#define NDEBUG
#include "hashtable.hpp"
#include "hashfuncs.hpp"

const size_t STANDART_SIZE_TABLE = 107;

static void         htInsert        (listPtr_t * elem, __m256i * word);
static htMainElem   htInit          (void);

inline static int memcmpAvx (const __m256i * ar1, const __m256i * ar2)
{
    __m256i cmp = _mm256_cmpeq_epi8 (*ar1, *ar2);
    unsigned int mask = (unsigned int) _mm256_movemask_epi8 (cmp);

    if (mask == 0xffffffff)
    {
        return 0;
    }
    return 1;
}

htMainElem createHashTable (textInfo_t textInfo, size_t (hashFuncs) (char * word), char * nameCsvFile)
{
    htMainElem ht = htInit ();
    size_t index = 0;
    char * word = nullptr;
    for (size_t i = 0; i < textInfo.numWords; i++)
    {
        word = (char *) textInfo.ar256Words[i];
        index = hashFuncs (word) % ht.capacity;
        htInsert (&(ht.htElem[index]), (__m256i *) word);
    }
    return ht;
}

static htMainElem htInit (void)
{
    htMainElem hashtable = {};
    hashtable.capacity   = STANDART_SIZE_TABLE;
    hashtable.htElem     = (listPtr_t *) calloc (hashtable.capacity, sizeof(listPtr_t));
    MY_ASSERT (hashtable.htElem == nullptr, "Unable to create a hashtable");
    
    for (size_t i = 0; i < hashtable.capacity; i++)
    {
        listConstruct (&(hashtable.htElem[i]));
    }
    return hashtable;
}

struct listElement_t * htFind (htMainElem hashtable, __m256i * word)
{
    MY_ASSERT (word == nullptr, "There is no access to this word");

    size_t index = hashBkdr ((char *)word) % hashtable.capacity;
    size_t lengthList = hashtable.htElem[index].size;
    listElement_t * listElem = hashtable.htElem[index].ptrToList->next; 

    __m256i * data = nullptr;

    for (size_t i = 0; i < lengthList; i++)
    {  
        data = listElem->data;

        if (memcmp (data, word, 32) == 0)
        {
            return listElem;
        }
        listElem = listElem->next;
    }

    return nullptr;
}

static void htInsert (listPtr_t * elem, __m256i * word)
{
    size_t lengthList = elem->size;
    listElement_t * listElem = elem->ptrToList->next;
    for (size_t i = 0; i < lengthList; i++, listElem = listElem->next)
    {
        if (memcmp(listElem->data, word, 32) == 0)
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

