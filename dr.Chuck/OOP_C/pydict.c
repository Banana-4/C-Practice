#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dnode  {
    char *__key;
    char *__value;
    struct dnode *__left;
    struct dnode *__right;
} dnode;

typedef struct PYDICT {
    size_t __size;
    dnode *__root;
}PYDICT;

PYDICT *new_PYDICT() {
    PYDICT *d = (PYDICT *)malloc(sizeof(PYDICT));
    if (!d)
        return NULL;
    d->__root = NULL;
    d->__size = 0;
    return d;
}

inline static void free_dnode(dnode* dn) {
  free(dn->__key);
  free(dn->__value);
  free(dn);
}
void del_dnode(PYDICT *d, dnode *dn) {
    if (!dn)
        return;
    del_dnode(d, dn->__left);
    del_dnode(d, dn->__right);
    free_dnode(dn);
    d->__size--;
}

void del_PYDICT(PYDICT *d) {
  del_dnode(d, d->__root);
}

dnode *insert_dnode(PYDICT *d, dnode *dn, char *key, char *val) {
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
      dn->__right = insert_dnode(d, dn->__right, key, val);
  } else {
      dn->__left = insert_dnode(d, dn->__left, key, val);
  }
  return dn;
}

void insert_PYDICT(PYDICT *d, char *key, char *val) {
  d->__root = insert_dnode(d, d->__root, key, val);
}



void remove_PYDICT(PYDICT *d, char *key) {
  if (!d)
    return;

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
    return;

  if (n == d->__root && d->__size == 1) {
    free_dnode(n);
    d->__root = NULL;
    d->__size = 0;
  }


  if (!n->__right && n->__left)  {
    par->__left == n ? (par->__left = n->__left) : (par->__right = n->__left);
    d->__size--;
    free_dnode(n);
    return;
  }

  if (!n->__left && n->__right) {
    par->__left == n ? (par->__left = n->__right) : (par->__right = n->__right);
    d->__size--;
    free_dnode(n);
    return;
  }

  if (!n->__left && !n->__right) {
    par->__left == n ? (par->__left = NULL) : (par->__right = NULL);
    d->__size--;
    free_dnode(n);
    return;
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
}

char *get_dnode(dnode *dn, char *key) {
  if (!dn)
    return NULL;
  int cmp = strcmp(key, dn->__key);
  if (cmp == 0)
    return dn->__value;
  else if (cmp > 0)
    return get_dnode(dn->__right, key);
  else
    return get_dnode(dn->__left, key);
}

char *get_PYDICT(PYDICT *d, char *key) {
  return get_dnode(d->__root, key);
}

void print_dnode(dnode *dn) {
  if (!dn)
    return;

  print_dnode(dn->__left);
  printf("'%s' : '%s' ", dn->__key, dn->__value);
  print_dnode(dn->__right);
}

void print_PYDICT(PYDICT *d) {
  printf("[ ");
  print_dnode(d->__root);
  printf("]\n");
}

size_t len_PYDICT(PYDICT *d) {
  return d->__size;
}

int main() {
  PYDICT *pd = new_PYDICT();
  insert_PYDICT(pd, "z", "Catch Phrase");
  print_PYDICT(pd);
  insert_PYDICT(pd, "z", "W");
  print_PYDICT(pd);
  insert_PYDICT(pd, "y", "B");
  insert_PYDICT(pd, "c", "C");
  insert_PYDICT(pd, "a", "D");
  print_PYDICT(pd);
  printf("Length = %zu\n", len_PYDICT(pd));

  printf("z=%s\n", get_PYDICT(pd, "z"));
  printf("x=%s\n", get_PYDICT(pd, "x"));
  del_PYDICT(pd);
}
