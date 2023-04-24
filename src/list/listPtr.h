#ifndef LISTPTR_H
#define LISTPTR_H

#include <stdio.h>
#include <math.h>
// #include "MY_ASSERT.h"
#include <stdlib.h>
#include "../../logs/logs.hpp"

//====================================variables used=====================================

typedef char * elem_t;
static size_t NUMBER_OF_GRAPHIC_DUMPS = 1;

//=======================================================================================

//=================================defining structures===================================

struct listElement_t
{
    struct listElement_t * prev;
    elem_t   data;
    struct listElement_t * next;
};

typedef struct
{
    struct listElement_t * ptrToList;
    size_t size;
} listPtr_t;

//================================main functions========================================

void                    listConstruct           (listPtr_t * list);
struct listElement_t *  listPushBack            (listPtr_t * list, elem_t newElemValue);
       listElement_t *  listPushFront           (listPtr_t * list, elem_t newElemValue);
struct listElement_t *  listPushFirstElem       (listPtr_t * list, elem_t newElemValue);
struct listElement_t *  listInsertBefore        (listPtr_t * list, struct listElement_t * currentElem, elem_t newElemValue);
struct listElement_t *  listInsertAfter         (listPtr_t * list, struct listElement_t * currentElem, elem_t newElemValue);
void                    listDestructor          (listPtr_t * list);
void                    listDeleteElem          (listPtr_t * list, struct listElement_t * currentElem);

struct listElement_t *  listValidator           (const listPtr_t * list, FILE * const log);
void listGraphviz (const listPtr_t * list, const char * nameDOTfile, FILE * ptrHTMLfile);

//===============================support function=======================================

struct listElement_t *  listPtrToNextElement    (struct listElement_t * currentElem);
struct listElement_t *  listPtrToPrevElement    (struct listElement_t * currentElem);
void                    listDump                (const listPtr_t    * list, FILE * log);
size_t                  listSize                (const listPtr_t * list);
struct listElement_t *  listAccessLastElem      (const listPtr_t    * list);
struct listElement_t *  listAccessFirstElem     (const listPtr_t    * list);
struct listElement_t *  listFindElemByValue     (const listPtr_t    * list, elem_t value);
struct listElement_t *  listFindElemByNumber    (const listPtr_t    * list, size_t number);
FILE *                  listCreateHTMLfileForGraphviz (const char * nameFile);
FILE *                  listSystemOfLogs        (const char * nameLogForList);

//======================================================================================

#endif
