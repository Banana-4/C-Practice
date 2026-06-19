#include "../include/get_line.h"

int get_line(FILE *stream , String *str)
{
    if (!stream)
        return NO_STREAM;
    if(!str)
        return NO_STR;

    int ch;
    while((ch = fgetc(stream)) != EOF)
    {
       if(!str_append(str, ch))
           return MEM_ERROR;
       if(ch == '\n')
           break;
    }

    return (ch == EOF ? END : OK);

}
