#define NDEBUG
#include "textProcessing.hpp"
static size_t STANDART_NUM_WORDS = 10000;

static size_t     getText     (const char * fileName, char ** text);
static textInfo_t textParsing (char * text, size_t numSymbols);
static void set256Words (textInfo_t * text);

textInfo_t getArrayWords (const char * fileName)
{
    MY_ASSERT (fileName == nullptr, "There is no access to file name");
	char * text = nullptr;
    size_t numSymbols = getText (fileName, &text);
    textInfo_t textInf = textParsing (text, numSymbols);
    set256Words (&textInf);
    return textInf;
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

    textInfo.text = text;

    char ** arrayWords = (char **) calloc (STANDART_NUM_WORDS, sizeof (char *));
    const char * sep = "\n \t ,.:()[]!?;'";
    char * word = strtok (text, sep);

    size_t numWords = 0;
    for (; word != nullptr; numWords++)
    {
        if (numWords == STANDART_NUM_WORDS)
        {
            arrayWords = (char **) realloc (arrayWords, 2*numWords*sizeof(char *));
            MY_ASSERT (arrayWords == nullptr, "Not enough memory for next processing");
            STANDART_NUM_WORDS *= 2;
        }

        arrayWords[numWords] = word;
        word = strtok (nullptr, sep);
    }

    textInfo.numWords = numWords;
    textInfo.arrayWords = arrayWords;

    return textInfo;
}

static void set256Words (textInfo_t * text)
{
    MY_ASSERT (text == nullptr, "Unable to use \"text\" pointer");

    size_t wordsCounter = text->numWords;

    text->ar256Words = (__m256i **) calloc (wordsCounter, sizeof(__m256i *));
    MY_ASSERT (text->ar256Words == nullptr, "Unable to allocate new memory");

    for (size_t i = 0; i < wordsCounter; i++)
    {
        __m256i * _256word = (__m256i *) aligned_alloc (32, sizeof(__m256i));
        MY_ASSERT (_256word == nullptr, "Unable to allocate new memory");
        memset (_256word, 0, sizeof(__m256i));

        alignas (32) char tmp_word[32] = {0};
        strcpy (tmp_word, text->arrayWords[i]);

        *_256word = _mm256_load_si256 ((__m256i*) tmp_word);

        text->ar256Words[i] = _256word;
    }
    return;
}

void textDestructor (textInfo_t textInfo)
{
    for (size_t i = 0; i < textInfo.numWords; i++)
    {
        free (textInfo.ar256Words[i]);
    }
    free (textInfo.ar256Words);
    free (textInfo.arrayWords);


}