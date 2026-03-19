#ifndef STDLIB_H
#define STDLIB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#endif

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
  size_t (*len)(struct PYDICT*);
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



static bool __remove_PYDICT(PYDICT *d, char *key) {
  if (!d)
    return false;

  dnode *n = d->__root;
  dnode *par = n;

  while (n) {
    int cmp = strcmp(key, n->__key);
    if (cmp == 0)
      break;
    par = n;
    if (cmp > 0)
      n = n->__right;
    else
      n = n->__left;
  }

  if (!n)
    return false;

  if (n == d->__root && d->__size == 1) {
    __free_dnode(n);
    d->__root = NULL;
    d->__size = 0;
  }


  if (!n->__right && n->__left)  {
    par->__left == n ? (par->__left = n->__left) : (par->__right = n->__left);
    d->__size--;
    __free_dnode(n);
    return true;
  }

  if (!n->__left && n->__right) {
    par->__left == n ? (par->__left = n->__right) : (par->__right = n->__right);
    d->__size--;
    __free_dnode(n);
    return true;
  }

  if (!n->__left && !n->__right) {
    par->__left == n ? (par->__left = NULL) : (par->__right = NULL);
    d->__size--;
    __free_dnode(n);
    return true;
  }


  dnode *r = n->__right;
  while (r->__left) {
    par = r;
    r = r->__left;
  }
  free(n->__key);
  free(n->__value);
  n->__key = r->__key;
  n->__value = r->__value;
  free(r);
  if (r != n->__right) {
    par->__left = NULL;
  }
  d->__size--;
  return true;
}

static char *__get_dnode(dnode *dn, char *key) {
  if (!dn)
    return NULL;
  int cmp = strcmp(key, dn->__key);
  if (cmp == 0)
    return dn->__value;
  else if (cmp > 0)
    return __get_dnode(dn->__right, key);
  else
    return __get_dnode(dn->__left, key);
}

static char *__get_PYDICT(PYDICT *d, char *key) {
  return __get_dnode(d->__root, key);
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
  pd->del(pd);
}
