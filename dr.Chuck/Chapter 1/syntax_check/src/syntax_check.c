#include "../include/syntax_check.h"

static Set *left = NULL;
static Set *right = NULL;

bool init_syntax_check()
{
    left = create_set();
    if (!left)
        return false;
    right = create_set();
    if(!right)
    {
        set_delete(left);
        left = NULL;
        return false;
    }
    if (
        set_insert(left, '(') && set_insert(left, '{') &&
        set_insert(left, '[') && set_insert(left, '<') &&
        set_insert(right, ')') && set_insert(right, '}') &&
        set_insert(right, ']') &&set_insert(right, '>')
    )
        return true;
    else
     return false;
}

void syntax_check(List *text)
{
    Stack *stack = create_stack();
    bool in_q = false;
    char q;
    Node *n = text->head;
    while(n)
    {
        in_q = false;
        q = '\0';
        String *line = n->line;
        for(size_t i = 0; i < line->len; ++i)
        {
            if(!in_q && line->str[i] == '/')
            {
                if (line->str[i + 1] == '/')
                    break;
            }
            if (!in_q && (line->str[i] == '"' || line->str[i] == '\''))
            {
                in_q = true;
                q = line->str[i];
            }
            if (in_q)
            {
                if (line->str[i] == q)
                {
                    in_q = false;
                    q = '\0';
                }
                if(line->str[i] == '\n' || line->str[i] == EOF)
                {
                    printf("Unterminated %c\n", q);
                }
            }

            if (in_set(left, line->str[i]))
                push(stack, line->str[i]);
            if(in_set(right, line->str[i]))
            {
                if(stack->len == 0)
                {
                    printf("Unmatched %c\n", line->str[i]);
                }
                if(get_right(peek(stack))!= line->str[i])
                {
                    printf("%c does not match %c\n", peek(stack), line->str[i]);
                }
                pop(stack);
            }
        }
        n = n->next;
        printf("%s", line->str);
    }
    if (stack->len != 0)
    {
        printf("Multiple unmatched brackets detected.\n");
    }
}
