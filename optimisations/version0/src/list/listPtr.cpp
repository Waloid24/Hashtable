#define NDEBUG
#include "listPtr.h"

#define LONG_LINE "###################################################################\n"
#define dumpline(string, ...) fprintf (ptrGraph, string, ##__VA_ARGS__);
#define print_html(command, ...) fprintf(graphicBuf, command, ##__VA_ARGS__);

static char * POISON_LISTPTR = nullptr;

static void cmdLine (size_t num, const char * nameDOTfile)
{
    MY_ASSERT (nameDOTfile == nullptr, "Unexpected file reading error");

    char buf[100] = {};
    sprintf(buf, "dot -T png -o ./obj/graph%lu.png %s", num, nameDOTfile);
    system(buf);
}

static void createHTMLfile (size_t * num, FILE * graphicBuf)
{
    MY_ASSERT (graphicBuf == nullptr, "Unable to access to file");

    char buf[60] = {};
    sprintf (buf, "graph%lu.png", *num);

    print_html("<pre>\n");
    print_html("<img src=\"%s\" alt=\"dump №%lu\"/>\n", buf, *num);
    print_html("</pre>\n");

    (*num)++;

    fflush (graphicBuf);
    fclose (graphicBuf);
}

void listConstruct (listPtr_t * list)
{
    MY_ASSERT (list == nullptr, "There is no access to list");

    list->ptrToList = (struct listElement_t *) calloc (1, sizeof (listElement_t));

    MY_ASSERT(list->ptrToList == nullptr, "Unable to allocate memory for the list");

    list->ptrToList[0].data = POISON_LISTPTR;
    list->ptrToList[0].prev = list->ptrToList[0].next = &(list->ptrToList[0]);
}

void listDump (const listPtr_t * list, FILE * log)
{
    MY_ASSERT (list == nullptr, "There is no access to list file");
    MY_ASSERT(log == nullptr, "There is no access to log file");

    setbuf(log, NULL);

    fprintf (log, LONG_LINE);

    fprintf (log, "list.size = %zu\n", list->size);
    fprintf (log, "data in fucken element is %.s\n\n", list->ptrToList[0].data);

    fprintf (log, "data: ");

    struct listElement_t * currentElem = (list->ptrToList)[0].prev;
    for (size_t i = 0; i < list->size; i++)
    {
        fprintf (log, "%.s ", currentElem->data);
        currentElem = listPtrToNextElement(currentElem);
    }

    fprintf (log,"\nnext: ");

    currentElem = list->ptrToList[0].prev;
    for (size_t i = 0; i < list->size; i++)
    {
        fprintf (log, "%.s ", currentElem->next->data);
        currentElem = listPtrToNextElement(currentElem);
    }

    fprintf (log, "\nprev: ");

    currentElem = list->ptrToList[0].prev;
    for (size_t i = 0; i < list->size; i++)
    {
        fprintf (log, "%.s ", currentElem->prev->data);
        currentElem = listPtrToNextElement(currentElem);
    }

    fprintf (log, "\n");
    fprintf (log, LONG_LINE);
    fprintf (log, "\n\n");

    fflush (log);

}

struct listElement_t * listPushBack (listPtr_t * list, elem_t newElemValue)
{
    MY_ASSERT (list == nullptr, "There is no access to list");

    if (list->size == 0)
    {
        return listPushFirstElem (list, newElemValue);
    }

    struct listElement_t * newElem = (struct listElement_t *) calloc (1, sizeof(struct listElement_t));
    MY_ASSERT (newElem == nullptr, "Unable to allocate new memory");

    newElem->data = newElemValue;
    newElem->next = list->ptrToList[0].prev;
    newElem->prev = list->ptrToList[0].next;

    list->ptrToList[0].next->next = newElem;
    list->ptrToList[0].prev->prev = newElem;

    list->ptrToList[0].next = newElem;

    list->size++;

    return newElem;
}

listElement_t * listPushFront (listPtr_t * list, elem_t newElemValue)
{
    MY_ASSERT (list == nullptr, "There is no access to list");

    if (list->size == 0)
    {
        return listPushFirstElem (list, newElemValue);
    }

    struct listElement_t * newElem = (struct listElement_t *) calloc (1, sizeof(struct listElement_t));
    MY_ASSERT (newElem == nullptr, "Unable to allocate new memory");

    newElem->data = newElemValue;

    newElem->next = list->ptrToList[0].next;
    newElem->prev = list->ptrToList[0].prev;

    list->ptrToList[0].prev->next = newElem;
    list->ptrToList[0].next->prev = newElem;

    list->ptrToList[0].prev = newElem;

    list->size++;

    return newElem;
}

struct listElement_t * listPushFirstElem (listPtr_t * list, elem_t newElemValue)
{
    struct listElement_t * newElem = (struct listElement_t *) calloc (1, sizeof(struct listElement_t));
    MY_ASSERT (newElem == nullptr, "There is no access to list");
    list->ptrToList[0].next = newElem;
    list->ptrToList[0].prev = newElem;

    newElem->data = newElemValue;
    newElem->next = list->ptrToList[0].prev;
    newElem->prev = list->ptrToList[0].next;

    list->size++;

    return newElem;
}

struct listElement_t * listInsertBefore (listPtr_t * list, struct listElement_t * currentElem, elem_t newElemValue)
{
    MY_ASSERT (list == nullptr, "Unable to allocate new memory");
    struct listElement_t * newElem = (struct listElement_t *) calloc (1, sizeof(struct listElement_t));
    MY_ASSERT (newElem == nullptr, "Unable to allocate new memory");

    newElem->data = newElemValue;
    newElem->next = currentElem;
    newElem->prev = currentElem->prev;

    currentElem->prev->next = newElem;
    currentElem->prev = newElem;

    list->size++;

    return newElem;
}

struct listElement_t * listInsertAfter (listPtr_t * list, struct listElement_t * currentElem, elem_t newElemValue)
{
    MY_ASSERT (list == nullptr, "Unable to allocate new memory");
    struct listElement_t * newElem = (struct listElement_t *) calloc (1, sizeof(struct listElement_t));
    MY_ASSERT (newElem == nullptr, "Unable to allocate new memory");

    newElem->data = newElemValue;
    newElem->next = currentElem->next;
    newElem->prev = currentElem;

    currentElem->next->prev = newElem;
    currentElem->next = newElem;

    list->size++;

    return newElem;
}

void listDestructor (listPtr_t * list)
{
    MY_ASSERT(list == nullptr, "There is no access to list");
    struct listElement_t * current = list->ptrToList[0].next;
    while (current != list->ptrToList[0].prev)
    {
        current = current->next;
        free (current->prev);
    }
    if (list->size != 0)
    {
        free (list->ptrToList[0].prev);
        free (list->ptrToList); 
    }
    else
    {
        free (list->ptrToList); 
    }
}

void listDeleteElem (listPtr_t * list, struct listElement_t * currentElem)
{
    MY_ASSERT (list == nullptr, "There is no access to list");
    MY_ASSERT (currentElem == nullptr, "Unable to find this element");

    if (list->size == 1)
    {
        currentElem->data = POISON_LISTPTR;
        currentElem->next = nullptr;
        currentElem->prev = nullptr;

        list->ptrToList[0].prev = list->ptrToList[0].next = &(list->ptrToList[0]);
    }

    if (currentElem == list->ptrToList[0].prev)
    {
        list->ptrToList[0].prev = list->ptrToList[0].prev->next;
    }
    if (currentElem == list->ptrToList[0].next)
    {
        list->ptrToList[0].next = list->ptrToList[0].next->prev;
    }

    currentElem->prev->next = currentElem->next;
    currentElem->next->prev = currentElem->prev;

    currentElem->data = POISON_LISTPTR;
    currentElem->next = nullptr;
    currentElem->prev = nullptr;

    list->size--;
}

struct listElement_t * listAccessFirstElem (const listPtr_t * list)
{
    MY_ASSERT (list == nullptr, "There is no access to list");

    return list->ptrToList[0].prev;
}

struct listElement_t * listAccessLastElem (const listPtr_t * list)
{
    MY_ASSERT (list == nullptr, "There is no access to list");

    return list->ptrToList[0].next;
}

struct listElement_t * listFindElemByValue (const listPtr_t * list, elem_t value)
{
    MY_ASSERT (list == nullptr, "There is no access to list");

    struct listElement_t * current = list->ptrToList[0].prev;

    for (size_t i = 0; i < list->size && current->data != value; i++)
    {
        current = current->next;
    }
    return current;
}

struct listElement_t * listFindElemByNumber (const listPtr_t * list, size_t number)
{
    MY_ASSERT (list == nullptr, "There is no access to list");

    struct listElement_t * current = list->ptrToList[0].prev;

    for (size_t i = 0; i < number && i < list->size; i++)
    {
        current = current->next;
    }

    return current;
}

struct listElement_t * listValidator (const listPtr_t * list, FILE * const log)
{
    MY_ASSERT (list == nullptr, "There is no access to list");
    MY_ASSERT (log == nullptr, "There is no access to list");

    struct listElement_t * current = list->ptrToList[0].prev;

    for (size_t i = 0; i < list->size; i++)
    {
        if (current->next->prev->data == current->data && current->prev->next->data == current->data)
        {
            current = current->next;
        }
        else
        {
            fprintf (log, "The error occurred around an element with a value of \"%.s\"\n", current->data);
            printf ("A small error has occurred\n");
            listDump (list, log);
            return current;
        }
    }

    fflush (log);
    fclose (log);
    return nullptr;
}

void listGraphviz (const listPtr_t * list, const char * nameDOTfile, FILE * ptrHTMLfile)
{
    FILE * ptrGraph = fopen (nameDOTfile, "w");
    MY_ASSERT (ptrGraph == nullptr, "There is no access to dump file for graphviz");

    dumpline("digraph G {\n");
    dumpline("  graph [dpi = 100];\n\n");
    dumpline("  ranksep = 1.5;\n\n");
    dumpline("  splines = ortho;\n\n");

    // for (int i = 0; i < numLists; i++)
    // {
    //     printf ("num list = %d\n", i);
    //     dumpList (&(list[i]), ptrGraph);
    // }
    // printf ("end\n");
    

    dumpline("  {rank = min;\n");
    dumpline("          above_node[shape = rectangle, style = \"rounded, invis\", fixedsize = true, height = 1, width = 2, fontsize = 30, label = \"Hi!\", width = 3];");
    dumpline("  }\n");
    dumpline("  {rank = same;\n");

    dumpline("  node0[shape = record, style = \"rounded, filled\", color = \"#8c6bb1\", label=\"size = %zu|<h0>head = %s|<t0>tail = %s\"];\n",
             list->size, list->ptrToList[0].prev->data, list->ptrToList[0].next->data);

    dumpline("  edge[minlen = 3, penwidth = 3];\n");
    dumpline("  node[shape = rectangle, style = \"rounded, filled\",\n");
    dumpline("              fixedsize = true, height = 1, width = 2,\n");
    dumpline("              penwidth = 4, color =\"#fa9fb5\", fontsize = 30];\n\n");

    struct listElement_t * current = list->ptrToList[0].prev;
    for (size_t i = 1; i < list->size + 1; i++)
    {
        dumpline("  node%lu[fillcolor = \"#ffffcc\", label = \"%s\"];\n", i, current->data);
        current = current->next;
    }

    dumpline("  }\n");
    dumpline("  {rank = max;\n");
    dumpline("          below_node[style = invis, label = \"Bye!\", width = 3];\n");
    dumpline("  }\n\n");

    dumpline("  above_node -> node0 [style = invis];\n");
    dumpline("  below_node -> node0 [style = invis];\n");
    dumpline("  node0:h0 -> node1 [color = blue];\n");
    dumpline("  node0:t0 -> node%zu [color = blue];\n", list->size);

    for (size_t i = 1; i < list->size; i++)
    {
        dumpline("  node%lu -> node%lu [color = black];\n", i, i+1);
        dumpline("  node%lu -> node%lu [color = black];\n", i+1, i);
    }
    dumpline("  node1 -> node%zu [color = black];\n", list->size);
    dumpline("  node%zu -> node1 [color = black];\n", list->size);



    dumpline("}\n\n");

    fflush (ptrGraph);
    fclose (ptrGraph);

    cmdLine (NUMBER_OF_GRAPHIC_DUMPS, nameDOTfile);

    createHTMLfile (&NUMBER_OF_GRAPHIC_DUMPS, ptrHTMLfile);
}

struct listElement_t * listPtrToNextElement (struct listElement_t * currentElem)
{
    MY_ASSERT (currentElem == nullptr, "There is no access to current element");
    return currentElem->next;
}

struct listElement_t * listPtrToPrevElement (struct listElement_t * currentElem)
{
    MY_ASSERT (currentElem == nullptr, "There is no access to current element");
    return currentElem->prev;
}

size_t listSize (const listPtr_t * list)
{
    MY_ASSERT (list == nullptr, "There is no access to list");
    return list->size;
}

FILE * listSystemOfLogs (const char * nameLogForList)
{
    MY_ASSERT (nameLogForList == nullptr, "There is no access to name of logfile");
    FILE * log = fopen (nameLogForList, "a");

    return log;
}

FILE * listCreateHTMLfileForGraphviz (const char * nameFile)
{
    MY_ASSERT (nameFile == nullptr, "There is no access to name of logfile");
    FILE * HTMLforGraphviz = fopen (nameFile, "a");
    MY_ASSERT (HTMLforGraphviz == nullptr, "Unable to open the file");
    return HTMLforGraphviz;
}



