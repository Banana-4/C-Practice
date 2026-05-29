#pragma once
#include <stdbool.h>
#include <stddef.h>
// Data
struct Node {
  struct Node *next;
  char *value;
};

struct LinkedList {
  size_t len;
  struct Node *head;
  struct Node *tail;
};

typedef struct LinkedList LinkedList;
typedef struct Node Node;
// Interface

LinkedList *constructList();


bool append(LinkedList *list, char *data);

void clear(LinkedList *list);

void destroy(LinkedList *list);
