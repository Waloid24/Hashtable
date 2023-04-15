#include "textProcessing.hpp"

char ** getArrayWords (const char * fileName)
{
    MY_ASSERT (fileName == nullptr, "There is no access to file name");
	char ** text = (char **) calloc (1, sizeof (char **));
    size_t numSymbols = getText (fileName, text);
    return textParsing (*text, numSymbols);    
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
    return nElem;
}

static char ** textParsing (char * text, size_t numSymbols)
{
    MY_ASSERT (text == nullptr, "Unable to access the text");
    char ** arrayWords = (char **) calloc (STANDART_NUM_WORDS, sizeof (char *));
    char * sep = "\n \t ,.:()[]!?;'";
    char * word = strtok (text, sep);

    for (int i = 0; word != nullptr; i++)
    {
        if (i == STANDART_NUM_WORDS)
        {
            arrayWords = (char **) realloc (arrayWords, STANDART_NUM_WORDS*sizeof(char *));
            MY_ASSERT (arrayWords == nullptr, "Not enough memory for next processing");
        }

        arrayWords[i] = word;
        word = strtok (nullptr, sep);
    }
}