#include "../include/stack.h"
#include <stdlib.h>

Stack *create_stack()
{
    const size_t CAP = 8;
    Stack *s = (Stack*) malloc(sizeof(Stack));
    if (!s)
        return NULL;
    s->items = malloc(CAP);
    if (!s->items)
    {
        free(s);
        return NULL;
    }
    s->len = 0;
    s->size = CAP;
    return s;
}

bool stack_grow(Stack *s)
{
    if(!s)
        return false;
    const size_t F = 2;
    char* items = malloc(F * s->size);
   if(!items)
       return false;
   memcpy(items,s->items, s->len);
   free(s->items);
   s->items = items;
   return true;
}

bool push(Stack *s, char ch)
{
    if(!s)
        return false;
    if( s->len + 1 == s->size)
        if(!stack_grow(s))
            return false;
    s->items[s->len++] = ch;
    return true;
}
int peek(const Stack *s)
{
    return (s ? s->items[s->len - 1] : EOF);
}
void pop(Stack *s)
{
    if(!s || s->len == 0)
        return;
    --(s->len);
}

void stack_delete(Stack *s)
{
    if(!s)
        return;
    free(s->items);
    s->len = 0;
    s->size = 0;
    free(s);
}
