#ifndef TEXTPROCESSING_H
#define TEXTPROCESSING_H

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include "MY_ASSERT.h"

const size_t STANDART_NUM_WORDS = 500;

char ** getArrayWords (const char * fileName);
static size_t getText (const char * fileName, char ** text);
static char ** textParsing (char * text, size_t numSymbols);

#endif