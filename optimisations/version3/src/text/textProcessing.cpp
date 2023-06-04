#define NDEBUG
#include "textProcessing.hpp"
static size_t STANDART_NUM_WORDS = 10000;

static size_t     getText     (const char * fileName, char ** text);
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
    printf ("in getText: nElem = %zu\n", nElem);
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

    textInfo.text = text;

    printf ("numSymbols = %zu\n", numSymbols);

    size_t numWords = numSymbols >> 5;

    char ** arrayWords = (char **) calloc (numWords, sizeof (char *));

    for (size_t i = 0; i < numWords; i++)
    {
        arrayWords[i] = (char *) aligned_alloc (32, sizeof(char)*32);
        memmove (arrayWords[i], text, 32*sizeof(char));
        text += 32;
    }

    textInfo.numWords = numWords;
    textInfo.arrayWords = arrayWords;

    return textInfo;
}

void textDestructor (textInfo_t textInfo)
{
    free (textInfo.arrayWords);
}