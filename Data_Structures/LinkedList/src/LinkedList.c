#include "../LinkedList.h"
#include <stdlib.h>
// data
typedef struct Node {
  struct Node *next;
  int value;
} Node;

struct LinkedList  {
  unsigned len;
  Node *head;
  Node* tail;
};

typedef struct ListIterator {
  Node *node;
} ListIterator;


Node *build_node(int n) {
  Node *node = (Node*)malloc(sizeof(Node));
  if (!node)
    return NULL;
  node->value = n;
  node->next = NULL;
  return node;
}

LinkedList *build_list() {
  LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
  if(!l) return NULL;
  l->len = 0;
  return l;
  }

LinkedList *build_list_array(Array *a) {
  LinkedList *list = build_list();
  ArrayIterator *iter = array_iterator(a);
  while (array_next(iter)) {
    if (!list_append(array_value(iter))) {
      destroy_list(list);
      return NULL;
    }
  }
  return list;
}

void destroy_list(LinkedList *l) {
  ListIterator *iter = list_iterator(l);
  while (list_next(iter)) {
    free(iter->node);
  }
  destroy_list_iterator(iter);
  free(l);
}


unsigned len_list(LinkedList *l) { return l->len; }


ListIterator *list_iterator(LinkedList *l) {
  if(!l || !l->len) return NULL;
  ListIterator *iter = (ListIterator*)malloc(sizeof(ListIterator));
  if (!iter) return NULL;
  iter->node = l->head;
  return iter;
}

bool list_next(ListIterator *i) {
  Node* next = i->node->next;
  if (next) {
    i->node = next;
    return true;
  }
  destroy_list_iterator(i);
  return false;
}

bool list_value(ListIterator *i, int *out) {
  if (!i)
    return false;
  *out = i->node->value;
  return true;
}

void destroy_list_iterator(ListIterator *i) {
  free(i);
}

bool append_list(LinkedList *l, int n) {
  if (!l) return false;

  Node *node = build_node(n);
  if(!node) return false;

  if (l->tail) {
    l->tail->next = node;
    l->tail = node;
  } else {
    l->tail = l->head = node;
  }
  l->len = l->len + 1;
  return true;
}

bool add_list(LinkedList *l, int n) {
  if (!l) return false;

  Node *node = build_node(n);
  if (!node) return false;

  if (l->head) {
    node->next = l->head;
    l->head = node;
  } else {
    l->tail = l->head = node;
  }
  l->len = l->len + 1;
  return true;
}

bool remove_list(LinkedList *l, unsigned int p, int *out) {
  if (!l || p >= l->len) return false;
  if (p == 0) {
    l->head = l->head->next;
  } else {
    Node *prev = NULL;
    ListIterator *iter = list_iterator(l);
    while (p--) {
      prev = iter->node;
      list_next(iter);
    }
    *out = list_value(iter);
    prev->next = iter->node->next;
    iter->node->next = NULL;
    free(iter->node);
    destroy_list_iterator(iter);
  }
  l->len = l->len - 1;
  return true;
}

bool insert_list(LinkedList *l, unsigned p, int n) {
  if (!l || p >= l->len)
    return false;
  if (p == 0) {
    return add_list(l, n);
  }
  if (p == l->len - 1) {
    return append_list(l, n);
  }
  ListIterator *iter = list_iterator(l);
  if (!iter) return false;

  Node *node = build_node(n);
  if (!node) return false;
  Node *prev = NULL;
  while (p--) {
    prev = iter->node;
    list_next(iter);
  }
  prev->next = node;
  node->next = iter->node;
  destroy_list_iterator(iter);
  l->len = l->len + 1;
  return true;
}


