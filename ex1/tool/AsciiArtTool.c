#include "stdio.h"
#include "stdbool.h"
#include "AsciiArtTool.h"
#define buffer_size 256

void minimize_and_add_to_RLEList(RLEList list, char* str)
{
        RLEListAppend(list, *str++);
}

RLEList asciiArtRead(FILE* in_stream)
{
    RLEList list = RLEListCreate();

    if(!list){
        return list;
    }
    char helper = fgetc(in_stream);
    while (helper > 0) {
        if (RLEListAppend(list, helper) != RLE_LIST_SUCCESS) {
            RLEListDestroy(list);
            return NULL;
        }
        helper = fgetc(in_stream);
    }

    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if(!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    int len = RLEListSize(list);
    char value;
    int i;
    for (i = 0; i < len; i++)
    {
        value = RLEListGet(list, i, NULL);
        if (value <= 0) {
            return RLE_LIST_ERROR;
        }
        fputc(value, out_stream);
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    char *encoded = RLEListExportToString(list, NULL);
    fputs(encoded, out_stream);
    return RLE_LIST_SUCCESS;
}

