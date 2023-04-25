#define NDEBUG
#include "hashtable.hpp"
#include "hashfuncs.hpp"

const size_t STANDART_SIZE_TABLE = 1131;

// static void         htInsert        (listPtr_t * elem, char * word);
static void htInsert (listPtr_t * elem, __m256i * word);
static htMainElem   htInit          (void);

inline static int memcmpAsm (const void * str1, const void * str2, size_t length)
{
    int result = 0; 

    asm
    (
        ".intel_syntax noprefix\n\t"
        "cld\t\n"
        "repe cmpsb\t\n"
        "je 1f\t\n"
        "dec %1\t\n"
        "dec %2\t\n"
        "mov %0, [%1]\t\n"
        "sub %0, [%2]\t\n"
        "jmp 2f\t\n"
        "1:\t\n"
        "mov %0, 0\t\n"
        "2:\t\n"
        ".att_syntax\t\n"
        : "=a" (result)
        : "S" (str1), "D" (str2), "c" (length)
    );

    return result;
}

static int memcmpAvx (const __m256i * ar1, const __m256i * ar2)
{
    // __m256i ar1 = _mm256_loadu_si256 ((__m256i *) str1);
    // __m256i ar2 = _mm256_loadu_si256 ((__m256i *) str2);

    __m256i cmp = _mm256_cmpeq_epi8 (*ar1, *ar2);
    unsigned int mask = (unsigned int) _mm256_movemask_epi8 (cmp);

    if (mask == 0xffffffff)
    {
        return 0;
    }
    return 1;
}

htMainElem createHashTable (textInfo_t textInfo, size_t (hashFuncs) (__m256i * word), char * nameCsvFile)
{
    htMainElem ht = htInit ();
    size_t index = 0;
    __m256i * word = nullptr;
    for (size_t i = 0; i < textInfo.numWords; i++)
    {
        // printf ("in createHashTable\n");
        word = textInfo.ar256Words[i];
        // printf ("in createHashTable: before hashFunc, word = %s\n", word);
        index = hashFuncs (word) % ht.capacity;
        // printf ("in createHashTable: index = %lu\n", index);
        htInsert (&(ht.htElem[index]), word);
    }
    printf ("end\n");
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

// struct listElement_t * htFind_0 (htMainElem hashtable, char * word)
// {
//     MY_ASSERT (word == nullptr, "There is no access to this word");

//     size_t index = hashBkdr_0(word) % hashtable.capacity;
//     size_t lengthList = hashtable.htElem[index].size;
//     listElement_t * listElem = hashtable.htElem[index].ptrToList->next; 

//     size_t lengthWord = strlen (word);
//     char * data = nullptr;

//     for (size_t i = 0; i < lengthList; i++)
//     {  
//         data = listElem->data;
//         size_t lengthData = strlen (data);
//         if (lengthData != lengthWord)
//         {
//             listElem = listElem->next;
//             continue;
//         }
//         // int resultCmp = 

//         if (memcmp (data, word, lengthData) == 0)
//         {
//             return listElem;
//         }
//         listElem = listElem->next;
//     }

//     return nullptr;
// }

// struct listElement_t * htFind_1 (htMainElem hashtable, char * word)
// {
//     MY_ASSERT (word == nullptr, "There is no access to this word");

//     size_t index = hashBkdr_1(word) % hashtable.capacity;
//     size_t lengthList = hashtable.htElem[index].size;
//     listElement_t * listElem = hashtable.htElem[index].ptrToList->next; 

//     size_t lengthWord = strlen (word);
//     char * data = nullptr;

//     for (size_t i = 0; i < lengthList; i++)
//     {  
//         data = listElem->data;
//         size_t lengthData = strlen (data);
//         if (lengthData != lengthWord)
//         {
//             listElem = listElem->next;
//             continue;
//         }
//         // int resultCmp = 

//         if (memcmp (data, word, lengthData) == 0)
//         {
//             return listElem;
//         }
//         listElem = listElem->next;
//     }

//     return nullptr;
// }

// struct listElement_t * htFind_2 (htMainElem hashtable, char * word)
// {
//     MY_ASSERT (word == nullptr, "There is no access to this word");

//     size_t index = hashBkdr_1(word) % hashtable.capacity;
//     size_t lengthList = hashtable.htElem[index].size;
//     listElement_t * listElem = hashtable.htElem[index].ptrToList->next; 

//     size_t lengthWord = strlen (word);
//     char * data = nullptr;

//     for (size_t i = 0; i < lengthList; i++)
//     {  
//         data = listElem->data;
//         size_t lengthData = strlen (data);
//         if (lengthData != lengthWord)
//         {
//             listElem = listElem->next;
//             continue;
//         }
//         // int resultCmp = 

//         if (memcmpAsm (data, word, lengthData) == 0)
//         {
//             return listElem;
//         }
//         listElem = listElem->next;
//     }

//     return nullptr;
// }

// struct listElement_t * htFind_3 (htMainElem hashtable, char * word)
// {
//     MY_ASSERT (word == nullptr, "There is no access to this word");

//     size_t index = hashBkdr_0(word) % hashtable.capacity;
//     size_t lengthList = hashtable.htElem[index].size;
//     listElement_t * listElem = hashtable.htElem[index].ptrToList->next; 

//     size_t lengthWord = strlen (word);
//     char * data = nullptr;

//     for (size_t i = 0; i < lengthList; i++)
//     {  
//         data = listElem->data;
//         size_t lengthData = strlen (data);
//         if (lengthData != lengthWord)
//         {
//             listElem = listElem->next;
//             continue;
//         }
//         // int resultCmp = 

//         if (memcmpAsm (data, word, lengthData) == 0)
//         {
//             return listElem;
//         }
//         listElem = listElem->next;
//     }

//     return nullptr;
// }

struct listElement_t * htFind_4 (htMainElem hashtable, __m256i * word)
{
    MY_ASSERT (word == nullptr, "There is no access to this word");

    // printf ("before hashBkdr_1\n");
    size_t index = hashBkdr_1(word) % hashtable.capacity;
    // printf ("lengthList\n");
    size_t lengthList = hashtable.htElem[index].size;
    listElement_t * listElem = hashtable.htElem[index].ptrToList->next; 

    __m256i * data = nullptr;

    for (size_t i = 0; i < lengthList; i++)
    {  
        data = listElem->data;

        if (memcmpAvx (data, word) == 0)
        {
            // printf ("word = %s\n", word);
            return listElem;
        }
        listElem = listElem->next;
    }

    return nullptr;
}

struct listElement_t * htFind_5 (htMainElem hashtable, __m256i * word)
{
    MY_ASSERT (word == nullptr, "There is no access to this word");
    // printf ("before hashBkdr_1\n");
    size_t index = hashBkdr_1(word) % hashtable.capacity;
    size_t lengthList = hashtable.htElem[index].size;
    listElement_t * listElem = hashtable.htElem[index].ptrToList->next; 

    __m256i * data = nullptr;

    // printf ("before memcmp\n");
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

