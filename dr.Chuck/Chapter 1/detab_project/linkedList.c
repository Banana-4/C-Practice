#include "linkedList.h"
#include <stdlib.h>

LinkedList *constructList() {
  LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
  if (!list) {
    return NULL;
  }
  list->len = 0;
  list->head = NULL;
  list->tail = NULL;
  return list;
}


bool append(LinkedList *list, char *data) {
  if (!list) {
    return false;
  }
  Node *node = (Node *)malloc(sizeof(Node));
  if (!node) {
    return false;
  }
  node->next = NULL;
  node->value = data;

  if (list->len > 0) {
    list->tail->next = node;
    list->tail = node;
  } else {
    list->head = list->tail = node;
  }

  ++list->len;

  return true;
}


void clear(LinkedList *list) {
  if (!list || list->len == 0) {
    return;
  }
  Node *left = list->head;
  Node *right = list->head;
  while (right) {
    left = right;
    right = right->next;
    free(left->value);
    free(left);
  }
  list->len = 0;
}

void destroy(LinkedList *list) {
  if (!list) {
    return;
  }
  clear(list);
  free(list);
}
