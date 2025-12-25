#include "../include/LinkedList.h"

typedef struct Node {
  struct Node *next;
  int value;
} Node;

struct LinkedList  {
  unsigned len;
  Node *head;
  Node* tail;
};

typedef struct IteratorList {
  Node *node;
} ListIterator;


LinkedList *buildLinkedList(ERROR* signal) {
  LinkedList *list = malloc(sizeof(LinkedList));
  if (!list) {
    *signal = memory_fail;
    return NULL;
  }
  *signal = no_error;
  return list;
}

int* peekFront(LinkedList *l, ERROR *signal) {
  if (!l) {
    *signal = no_list;
    return NULL;
  }
  if (l->len == 0) {
    *signal = empty_list;
    return NULL;
  }
  *signal = no_error;
  return &l->head->value;
}

int* peekBack(LinkedList *l, ERROR *signal) {
  if (!l) {
    *signal = no_list;
    return NULL;
  }
  if (l->len == 0) {
    *signal = empty_list;
    return NULL;
  }
  *signal = no_error;
  return &l->tail->value;
}

int *atList(LinkedList *l, unsigned pos, ERROR *signal) {
  if (!l) {
    *signal = no_list;
    return NULL;
  }
  if (l->len == 0) {
    *signal = empty_list;
    return NULL;
  }

  if (pos > l->len) {
    *signal = index_out_of_range;
    return NULL;
  }
  Node *trav = l->head;
  while (pos--) {
    trav = trav->next;
  }
  *signal = no_error;
  return &trav->value;
}

void insertList(LinkedList *l, unsigned int pos, int n, ERROR *signal) {
  if (!l) {
    *signal = no_list;
    return;
  }
  if (pos > l->len) {
    *signal = index_out_of_range;
    return;
  }
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = n;
  Node *trav = l->head;
  Node* prev = l->head;
  while (pos--) {
    prev = trav;
    trav = trav->next;
  }
  if (prev == trav) {
    newNode->next = trav;
    l->head = newNode;
  } else if (trav == NULL && prev == NULL) {
    l->head = l->tail = newNode;
    newNode->next = NULL;
  } else if (trav == NULL) {
    prev->next = newNode;
    newNode->next = NULL;
    l->tail = newNode;
  } else {
    prev->next = newNode;
    newNode->next = trav;
  }
  *signal = no_error;
  ++l->len;
}

void removeList(LinkedList *l, unsigned int pos, ERROR *signal) {
  if (!l) {
    *signal = no_list;
    return;
  }
  if (l->len == 0) {
    *signal = empty_list;
    return;
  }

  if (pos > l->len) {
    *signal = index_out_of_range;
    return;
  }
  Node *trav = l->head;
  Node *prev = l->head;
  while (pos--) {
    prev = trav;
    trav = trav->next;
  }
  if (prev == trav) {
    free(l->head);
    l->head = l->tail = NULL;
  } else if (trav == NULL) {
    prev->next = NULL;
    free(l->tail);
  } else {
    prev->next = trav->next;
    trav->next = NULL;
    free(trav);
  }
  --l->len;
  *signal = no_error;
}

void pushList(LinkedList *l, int n, ERROR *signal) {
  insertList(l, 0, n, signal);
}

void appendList(LinkedList *l, int n, ERROR *signal) {
  insertList(l, l->len, n, signal);
}

int popList(LinkedList *l, ERROR *signal) {
  if (!l) {
    *signal = no_list;
    return 0;
  }
  if (l->len == 0) {
    *signal = empty_list;
    return 0;
  }
  int val = l->head->value;
  Node *old = l->head;
  l->head = l->head->next;
  free(old);
  --l->len;
  *signal = no_error;
  return val;
}

bool emptyList(LinkedList *l, ERROR* signal) {
  if (!l) {
    *signal = no_list;
  }
  *signal = no_error;
  return l->len == 0;
}

void destroyList(LinkedList *l, ERROR *signal) {
  if (!l) {
    *signal = no_list;
    return;
  }
  if (l->len == 0) {
    free(l);
    return;
  }
  Node *trav = l->head;
  Node* next;
  while (trav) {
    next = trav->next;
    free(trav);
    trav = next;
  }
  *signal = no_error;
}

IteratorList *iteratorList(LinkedList *l, ERROR* signal) {
  if (!l) {
    *signal = no_list;
    return NULL;
  }
  if (l->len == 0) {
    *signal = empty_list;
    return NULL;
  }
  IteratorList *iter = (IteratorList *)malloc(sizeof(IteratorList));
  if (!iter) {
    *signal = memory_fail;
    return NULL;
  }
  iter->node = l->head;
  *signal = no_error;
  return iter;
}

void nextNode(IteratorList *iter, ERROR *signal) {
  if (!iter) {
    *signal = null_iter;
    return;
  }
  if (!iter->node) {
    *signal = end_of_list;
    return;
  }
  iter->node = iter->node->next;
  *signal = no_error;
}

int* valueNode(IteratorList *iter, ERROR *signal) {
  if (!iter) {
    *signal = null_iter;
    return NULL;
  }
  if (iter->node == NULL) {
    *signal = end_of_list;
    return NULL;
  }
  *signal = no_error;
  return &iter->node->value;
}