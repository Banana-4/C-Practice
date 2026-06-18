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

bool str_grow(String *s)
{
    if (!s)
        return false;
    const size_t F = 2;
    char *str = malloc(F * s->size);
    if (!str)
        return false;
    s->size = s->size * F;
    memcpy(str,s->str, s->len + 1);
    free(s->str);
    s->str = str;
    return true;
}

bool str_append(String *s, const char ch)
{
    if (!s)
        return false;
    if(s->len + 1 == s->size)
    {
        if(!str_grow(s))
            return false;
    }
    s->str[s->len++] = ch;
    s->str[s->len] = '\0';
    return true;
}

size_t str_len(const String *s)
{
    return (s ? s->len : 0);
}

const char *get_text(const String *s)
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
