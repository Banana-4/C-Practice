#pragma once
#include <stdlib.h>
#include "string.h"

typedef struct Node
{
    struct Node *next;
    String *line;
}Node;

typedef struct List
{
    Node* head;
    Node* tail;
}List;

List *create_list();
void list_append(List* l, String* s);
void list_destroy(List &l);
