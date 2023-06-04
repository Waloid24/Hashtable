#include <stdio.h>
#include <stdlib.h>
#include "logs.hpp"

FILE * _$logOF (const char * nameFile)
{
    FILE * logfile = nullptr;

    if (nameFile == nullptr)
    {
        logfile = fopen ("logSt.txt", "a+");
    }
    else
    {
        logfile = fopen (nameFile, "a+");
    }
    MY_ASSERT (logfile == nullptr, "Unable to open the file");
    setbuf(logfile, nullptr);

    return logfile;
}