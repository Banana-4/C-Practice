#include "../include/list.h"
List *create_list()
{
    List *l = (List*) malloc(sizeof(List));
    if (!l)
        return NULL;
    l->head = NULL;
    l->tail = NULL;
    return l;
}

void list_append(List* l, String* s)
{
    if(!l)
        return;
    Node *n = (Node*) malloc(sizeof(Node));
    if (!n)
        return;
    n->next = NULL;
    n->line = s;

    if (l->tail)
    {
        l->tail->next = n;
        l->tail = n;
    }
    else
    {
        l->head = l->tail = n;
    }
}
void list_print(const List *l)
{
    Node *n = l->head;
    while(n)
    {
        printf("%s", get_text(n->line));
        n = n->next;
    }
}
void list_delete(List *l)
{
    if (!l)
        return;
    Node *n = l->head;
    while(n != NULL)
    {
        Node *done = n;
        n = n->next;
        str_delete(done->line);
        free(done);
    }
    free(l);
}
