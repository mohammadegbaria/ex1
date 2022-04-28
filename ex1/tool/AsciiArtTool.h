//
// Created by JokerTOoL on 20/04/2022.
//

#ifndef ACSII_ART_TOOL
#define ACSII_ART_TOOL

#include "stdio.h"
#include "stdbool.h"
//#include "RLEList.h"
#include </home/mtm/public/2122b/ex1/RLEList.h>

RLEList asciiArtRead(FILE* in_stream);

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif