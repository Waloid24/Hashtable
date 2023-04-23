#define NDEBUG
#include "textProcessing.hpp"
static size_t STANDART_NUM_WORDS = 10000;

static size_t getText (const char * fileName, char ** text);
static textInfo_t textParsing (char * text, size_t numSymbols);

textInfo_t getArrayWords (const char * fileName)
{
    MY_ASSERT (fileName == nullptr, "There is no access to file name");
	char * text = nullptr;
    size_t numSymbols = getText (fileName, &text);
    return textParsing (text, numSymbols);  
}

static size_t getText (const char * fileName, char ** text)
{
    MY_ASSERT (fileName == nullptr, "Unable to access the file");
    struct stat fileInfo;
	FILE * fileInput = fopen (fileName, "rb");
    MY_ASSERT (fileInput == nullptr, "Unable to open the file");
    stat (fileName, &fileInfo);
	size_t nElem = fileInfo.st_size;

    *text = (char *) calloc (nElem + 1, sizeof(char));
	MY_ASSERT (*text == nullptr, "Error in allocating memory for saving");
	(*text)[nElem] = '\0';

	fread (*text, 1, nElem, fileInput);
    fclose (fileInput);
    return nElem;
}

static textInfo_t textParsing (char * text, size_t numSymbols)
{
    MY_ASSERT (text == nullptr, "Unable to access the text");
    textInfo_t textInfo = {};

    char ** arrayWords = (char **) calloc (STANDART_NUM_WORDS, sizeof (char *));
    const char * sep = "\n \t ,.:()[]!?;'";
    char * word = strtok (text, sep);

    size_t numWords = 0;
    for (; word != nullptr; numWords++)
    {
        alignas(32) char * word32 = (char *) calloc (1, 32*sizeof(char));
        word32 = (char *) memmove(word32, word, strlen(word));
        if (numWords == STANDART_NUM_WORDS)
        {
            arrayWords = (char **) realloc (arrayWords, 2*numWords*sizeof(char *));
            MY_ASSERT (arrayWords == nullptr, "Not enough memory for next processing");
            STANDART_NUM_WORDS *= 2;
        }

        arrayWords[numWords] = word32;
        word = strtok (nullptr, sep);
    }

    textInfo.numWords = numWords;
    textInfo.arrayWords = arrayWords;

    free (text);

    return textInfo;
}

void textDestructor (textInfo_t textInfo)
{
    printf ("STANDART_NUM_WORDS = %lu\n", STANDART_NUM_WORDS);
    for (int i = 0; i < STANDART_NUM_WORDS; i++)
    {
        if (textInfo.arrayWords[i] != nullptr)
        {
            free (textInfo.arrayWords[i]);
        }
    }

    free (textInfo.arrayWords);
}