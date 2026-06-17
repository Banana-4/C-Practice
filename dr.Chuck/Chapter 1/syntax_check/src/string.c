#include "../include/string.h"

String *create_str(size_t size)
{
    String *str = (String*) malloc(sizeof(String));
    if (!str)
        return NULL;
    str->len = 0;
    str->size = size;
    str->str = malloc(str->size);
    if (!str->str)
    {
        free(str);
        return NULL;
    }
    else
        return str;
}

bool str_grow(const String *s)
{
    if (!s)
        return false;
    const size_t F = 2;
    char *str = malloc(F * s->size);
    if (!str)
        return false;
    s->size = s->size * F;
    memcpy(str,s->str, s->len + 1);
    return true;
}

void str_append(String *s, const char ch)
{
    if (!s)
        return;
    if(str->len + 1 == str->size - 1)
    {
        if(!str_grow(s))
            return;
    }
    s->str[str->len++] = ch;
    s->str[str->len] == '\0';
}

size_t str_len(const String *s)
{
    return (s ? s->len : 0);
}

const char *str(const String *s)
{
    return (s ? s->str : NULL);
}

void str_delete(String *s)
{
    if (!s)
        return;
    free(s->str);
    s->len = 0;
    s->size = 0;
    free(s);
}
