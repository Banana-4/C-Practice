#include "../include/read_src.h"
#include "../include/syntax_check.h"

bool read_src(FILE *stream, List *list)
{
    if (!stream || !list)
        return false;
    const size_t CAP = 8;
    String *str;
    while(1)
        {
            str = create_str(CAP);
            ERROR code = get_line(stdin, str);
            if (code == END)
                return true;
            if(code == OK)
            {
                if(str->len > 1)
                    list_append(list, str);
            }
            else
                return false;
        }
}
