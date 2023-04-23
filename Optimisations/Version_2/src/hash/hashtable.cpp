#define NDEBUG
#include "hashtable.hpp"

const size_t STANDART_SIZE_TABLE = 6000;

static void         htInsert        (listPtr_t * elem, char * word);
static htMainElem   htInit          (void);

inline static int memcmpAsm (const void * str1, const void * str2, size_t length)
{
    int result = 0; 

    asm
    (
        ".intel_syntax noprefix\n\t"
        "cld\t\n"
        "repe cmpsb\t\n"
        "je .eq\t\n"
        ".noeq:\t\n"
        "dec %1\t\n"
        "dec %2\t\n"
        "mov %0, [%1]\t\n"
        "sub %0, [%2]\t\n"
        "jmp .end\t\n"
        ".eq:\t\n"
        "mov %0, 0\t\n"
        ".end:\t\n"
        ".att_syntax\t\n"
        : "=a" (result)
        : "S" (str1), "D" (str2), "c" (length)
    );

    return result;
}

static int memcmpAvx (const void * str1, const void * str2, size_t length)
{
    __m256i ar1 = _mm256_loadu_si256 ((__m256i *) str1);
    __m256i ar2 = _mm256_loadu_si256 ((__m256i *) str2);

    __m256i cmp = _mm256_cmpeq_epi8 (ar1, ar2);
    int mask = _mm256_movemask_epi8 (cmp);

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
        word = textInfo.arrayWords[i];
        index = hashFuncs (word) % ht.capacity;
        htInsert (&(ht.htElem[index]), word);
    }

    return ht;
}

static htMainElem htInit (void)
{
    htMainElem hashtable = {};
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
        int resultCmp = memcmp (data, word, 32);

        if (resultCmp == 0)
        {
            return listElem;
        }
        listElem = listElem->next;
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

