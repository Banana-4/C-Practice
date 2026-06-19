#pragma once
#include "string.h"
#include <stdio.h>

typedef enum ERROR_CODES
{
    END = EOF,
    OK = 0,
    NO_STREAM = 1,
    NO_STR = 2,
    MEM_ERROR = 3,
}ERROR;

int get_line(FILE *stream , String *str); //returns Error codes
