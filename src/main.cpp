#include "textProcessing.hpp"
#include "MY_ASSERT.h"

int main (int argc, char * argv[])
{
    MY_ASSERT (argc != 2, "You should enter 2 arguments: \n 1) the name of using programm; \n 2) the name of the file to be proccessed");

    getArrayWords (argv[1]);


    return 0;
}

