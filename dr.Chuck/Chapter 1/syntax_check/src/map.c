#include "../include/map.h"

char get_right(char bracket)
{
    if (bracket == '(')
        return ')';
    if (bracket == '[')
        return ']';
    if (bracket == '{')
        return '}';
    if (bracket == '<')
        return '>';
    return '\0';
}
