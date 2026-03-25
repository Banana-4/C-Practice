#ifndef STDLIB_H
#define STDLIB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#endif
typedef struct Iter_dict Iter_dict;
typedef struct dnode  {
    char *__key;
    char *__value;
    struct dnode *__left;
    struct dnode *__right;
} dnode;

typedef struct PYDICT {
    size_t __size;
    dnode *__root;

  /*Interface*/
  void (*insert)(struct PYDICT*, char*, char*);
  char* (*get)(struct PYDICT*, char*);
  bool (*remove)(struct PYDICT *, char *);
  size_t (*len)(struct PYDICT *);
  Iter_dict *(*iter)(struct PYDICT*);
  void (*print)(struct PYDICT*);
  void (*del)(struct PYDICT*);

}PYDICT;

static void __free_dnode(dnode* dn) {
  free(dn->__key);
  free(dn->__value);
  free(dn);
}

static void __del_dnode(PYDICT *d, dnode *dn) {
  if (!dn)
        return;
    __del_dnode(d, dn->__left);
    __del_dnode(d, dn->__right);
    __free_dnode(dn);
    d->__size--;
}

static void __del_PYDICT(PYDICT *d) {
  if (!d)
    return;
  __del_dnode(d, d->__root);
  free(d);
}

static dnode *__insert_dnode(PYDICT *d, dnode *dn, char *key, char *val) {
  if (!dn) {
      dn = malloc(sizeof(dnode));
      if (!dn)
        return NULL;
      dn->__key = strdup(key);
      if (!dn->__key) {
          free(dn);
          return NULL;
      }
      dn->__value = strdup(val);
      if (!dn->__value) {
          free(dn->__key);
          free(dn);
          return NULL;
      }
      d->__size++;
      return dn;
  }

  int cmp = strcmp(key, dn->__key);
  if (cmp == 0) {
      char *tmp = strdup(val);
      if (tmp) {
          free(dn->__value);
          dn->__value = tmp;
      }
      return dn;

  } else if (cmp > 0) {
      dn->__right = __insert_dnode(d, dn->__right, key, val);
  } else {
      dn->__left = __insert_dnode(d, dn->__left, key, val);
  }
  return dn;
}

static void __insert_PYDICT(PYDICT *d, char *key, char *val) {
  d->__root = __insert_dnode(d, d->__root, key, val);
}


static dnode *__find_dnode(dnode *root, char *key) {
  if (!root)
    return NULL;
  int cmp = strcmp(key, root->__key);
  if (cmp == 0)
    return root;
  else if (cmp < 0)
    return __find_dnode(root->__left, key);
  else
    return __find_dnode(root->__right, key);
}

 void __remove_dnode(dnode *n, dnode *p) {



   if (!n->__left && !n->__right) {
     p->__left == n ? (p->__left = NULL) : (p->__right = NULL);
     __free_dnode(n);
   }

   if (n->__left && !n->__right) {
     p->__left == n ? (p->__left = n->__left) : (p->__right = n->__left);
     __free_dnode(n);
   }

   if (!n->__left && n->__right) {
     p->__left == n ? (p->__left = n->__right) : (p->__right = n->__right);
     __free_dnode(n);
   }

   dnode *par = n;
   dnode *c = n->__right;

   while (c->__left) {
     par = c;
     c = c->__left;
   }
   free(n->__key);
   free(n->__value);
   n->__key = c->__key;
   n->__value = c->__value;

   if (!c->__right) {
     par->__left == c ? (par->__left = NULL) : (par->__right = NULL);
     free(c);
   } else {
     par->__left = c ? (par->__left = c->__right) : (par->__right = c->__right);
     free(c);
   }

}

static bool __remove_PYDICT(PYDICT *d, char *key) {
  if (!d)
    return false;
  dnode *n = d->__root;
  dnode *p = n;
  int cmp;
  while (n && ((cmp = strcmp(key, n->__key)) != 0)) {
    p = n;
    if (cmp < 0)
      n = n->__left;
    else
      n = n->__right;
  }
  if (!n)
    return false;

  if (!n->__left && !n->__right) {
    if (n == d->__root) {
      d->__root = NULL;
      d->__size = 0;
      return true;
    } else {
      p->__left == n ? (p->__left = NULL) : (p->__right = NULL);
      __free_dnode(n);
    }
    return true;
   }

  if (n->__left && !n->__right) {
    if (n == d->__root) {
      d->__root = d->__root->__left;
      d->__size--;
    } else {
      p->__left == n ? (p->__left = n->__left) : (p->__right = n->__left);
      __free_dnode(n);
    }
    return true;
   }

  if (!n->__left && n->__right) {
    if (n == d->__root) {
      d->__root = d->__root->__right;
      d->__size--;
    } else {
     p->__left == n ? (p->__left = n->__right) : (p->__right = n->__right);
     __free_dnode(n);
    }
    return true;
   }

  dnode *par = n;
  dnode *c = n->__right;

  while (c->__left) {
    par = c;
    c = c->__left;
  }
  free(n->__key);
  free(n->__value);
  n->__key = c->__key;
  n->__value = c->__value;

  if (!c->__right)
    par->__left == c ? (par->__left = NULL) : (par->__right = NULL);
  else
    par->__left = c ? (par->__left = c->__right) : (par->__right = c->__right);
  free(c);
  d->__size--;
  return true;
}


static char *__get_PYDICT(PYDICT *d, char *key) {
  dnode *n = __find_dnode(d->__root, key);
  return n ? n->__value : NULL;
}

static void __print_dnode(dnode *dn) {
  if (!dn)
    return;

  __print_dnode(dn->__left);
  printf("'%s' : '%s' ", dn->__key, dn->__value);
  __print_dnode(dn->__right);
}

static void __print_PYDICT(PYDICT *d) {
  printf("[ ");
  __print_dnode(d->__root);
  printf("]\n");
}

static size_t __len_PYDICT(PYDICT *d) {
  return d->__size;
}



typedef struct list_node {
  dnode *val;
  struct list_node *next;
}list_node;

typedef struct list {
  struct list_node *head;
  struct list_node *tail;
  size_t size;
}list;

list *new_list() {
  list *l = (list*) malloc(sizeof(list));
  if(!l)
    return NULL;
  l->size = 0;
  l->head = NULL;
  l->tail = NULL;
  return l;
}

void append_list(list *l, dnode *val) {
  if(!l)
    return;
  list_node *node = (list_node*)malloc(sizeof(list_node));
  if (!node)
    return;

  if(l->size == 0) {
    node->val = val;
    node->next = NULL;
    l->head = l->tail = node;
  } else {
    l->tail->next = node;
    l->tail = node;
  }
  l->size++;
}

dnode *popf_list(list *l) {
  if(!l || l->size == 0)
    return NULL;
  dnode *val = l->head->val;
  list_node *last_head= l->head;
  l->head = l->head->next;
  l->size--;
  free(last_head);
  return val; 
}


struct Iter_dict {
  list *__stack;

  char *(*get_key)(struct Iter_dict*);
  char *(*get_val) (struct Iter_dict*);
  void (*next)(struct Iter_dict*);
  bool (*valid)(struct Iter_dict*);
  void (*del)(struct Iter_dict *);

};

static char *__get_key(Iter_dict *it) {
  if (!it)
    return NULL;
  if (it->__stack->size > 0) {
    return it->__stack->head->val->__key;
  } else 
  return NULL;
}

static char *__get_val(Iter_dict *it) {
  if (!it)
    return NULL;
  if (it->__stack->size > 0) {
    return it->__stack->head->val->__value;
  } else 
  return NULL;
}

static void __next_iter(Iter_dict *it) {
  if(!it)
    return;
  dnode *last = popf_list(it->__stack);
  if (last == NULL)
    return;
  if (last->__left)
    append_list(it->__stack, last->__left);
  if (last->__right)
    append_list(it->__stack, last->__right);
}

static bool __valid_iter(Iter_dict *it) {
  bool v = (it->__stack->size > 0);
  return v;
}

static void __del_iter(Iter_dict *it) {
  while (it->__stack->size > 0)
    popf_list(it->__stack);
  free(it);
  it = NULL;
}

Iter_dict *__new_iter(PYDICT *d) {
  if (!d)
    return NULL;
  Iter_dict *it = (Iter_dict *)malloc(sizeof(Iter_dict));
  if (!it)
    return NULL;
  it->__stack = new_list();
  if (d->__size == 0)
    return NULL;
  append_list(it->__stack, d->__root);
  it->del = &__del_iter;
  it->get_key = &__get_key;
  it->get_val = &__get_val;
  it->next = &__next_iter;
  it->valid = &__valid_iter;
  return it;
}

PYDICT *new_PYDICT() {
    PYDICT *d = (PYDICT *)malloc(sizeof(PYDICT));
    if (!d)
        return NULL;
    d->__root = NULL;
    d->__size = 0;
    d->insert = &__insert_PYDICT;
    d->get = &__get_PYDICT;
    d->remove = &__remove_PYDICT;
    d->len = &__len_PYDICT;
    d->print = &__print_PYDICT;
    d->del = &__del_PYDICT;
    d->iter = &__new_iter;
    return d;
}

int main() {
  PYDICT *pd = new_PYDICT();
  pd->insert(pd, "z", "Catch Phrase");
  
  pd->print(pd);
  pd->insert(pd, "z", "W");
  pd->print(pd);
  pd->insert(pd, "y", "B");
  pd->insert(pd, "c", "C");
  pd->insert(pd, "a", "D");
  pd->print(pd);
  printf("Length = %zu\n", pd->len(pd));

  printf("z=%s\n", pd->get(pd, "z"));
  printf("x=%s\n", pd->get(pd, "x"));
  Iter_dict *it = pd->iter(pd);
  if (it)
    while (it->valid(it)) {
      printf("Node: %s - %s\n", it->get_key(it), it->get_val(it));
      it->next(it);
    }
  it->del(it);
  pd->del(pd);
}
