#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dnode  {
    char *_key;
    char *_value;
    struct dnode *_left;
    struct dnode *_right;
} dnode;

typedef struct PYDICT {
    size_t size;
    dnode *root;
}PYDICT;

PYDICT *new_PYDICT() {
    PYDICT *d = (PYDICT *)malloc(sizeof(PYDICT));
    if (!d)
        return NULL;
    d->root = NULL;
    d->size = 0;
    return d;
}
void del_dnode(PYDICT *d, dnode *dn) {
    if (!dn)
        return;
    del_dnode(d, dn->_left);
    del_dnode(d, dn->_right);
    free(dn->_key);
    free(dn->_value);
    free(dn);
    d->size--;
}

void del_PYDICT(PYDICT *d) {
  del_dnode(d, d->root);
}

dnode *insert_dnode(PYDICT *d, dnode *dn, char *key, char *val) {
  if (!dn) {
      dn = malloc(sizeof(dnode));
      if (!dn)
        return NULL;
      dn->_key = strdup(key);
      if (!dn->_key) {
          free(dn);
          return NULL;
      }
      dn->_value = strdup(val);
      if (!dn->_value) {
          free(dn->_key);
          free(dn);
          return NULL;
      }
      d->size++;
      return dn;
  }

  int cmp = strcmp(key, dn->_key);
  if (cmp == 0) {
      char *tmp = strdup(val);
      if (tmp) {
          free(dn->_value);
          dn->_value = tmp;
      }
      return dn;

  } else if (cmp > 0) {
      dn->_right = insert_dnode(d, dn->_right, key, val);
  } else {
      dn->_left = insert_dnode(d, dn->_left, key, val);
  }
  return dn;
}

void insert_PYDICT(PYDICT *d, char *key, char *val) {
  d->root = insert_dnode(d, d->root, key, val);
}



void remove_PYDICT(PYDICT *d, char *key) {
  if (!d)
    return;

  dnode *n = d->root;
  dnode *par = n;

  while (n) {
    int cmp = strcmp(key, n->_key);
    if (cmp == 0)
      break;
    par = n;
    if (cmp > 0)
      n = n->_right;
    else
      n = n->_left;
  }

  if (!n)
    return;

  if (n == d->root && d->size == 1) {
    free(n->_key);
    free(n->_value);
    free(n);
    d->root = NULL;
    d->size = 0;
  }


  if (!n->_right && n->_left)  {
    par->_left == n ? (par->_left = n->_left) : (par->_right = n->_left);
    d->size--;
    free(n->_key);
    free(n->_value);
    free(n);
    return;
  }

  if (!n->_left && n->_right) {
    par->_left == n ? (par->_left = n->_right) : (par->_right = n->_right);
    d->size--;
    free(n->_key);
    free(n->_value);
    free(n);
    return;
  }

  if (!n->_left && !n->_right) {
    par->_left == n ? (par->_left = NULL) : (par->_right = NULL);
    d->size--;
    free(n->_key);
    free(n->_value);
    free(n);
    return;
  }


  dnode *r = n->_right;
  while (r->_left) {
    par = r;
    r = r->_left;
  }
  free(n->_key);
  free(n->_value);
  n->_key = r->_key;
  n->_value = r->_value;
  free(r);
  if (r != n->_right) {
    par->_left = NULL;
  }
  d->size--;
}

char *get_dnode(dnode *dn, char *key) {
  if (!dn)
    return NULL;
  int cmp = strcmp(key, dn->_key);
  if (cmp == 0)
    return dn->_value;
  else if (cmp > 0)
    return get_dnode(dn->_right, key);
  else
    return get_dnode(dn->_left, key);
}

char *get_PYDICT(PYDICT *d, char *key) {
  return get_dnode(d->root, key);
}

void print_dnode(dnode *dn) {
  if (!dn)
    return;

  print_dnode(dn->_left);
  printf("'%s' : '%s' ", dn->_key, dn->_value);
  print_dnode(dn->_right);
}

void print_PYDICT(PYDICT *d) {
  printf("[ ");
  print_dnode(d->root);
  printf("]\n");
}

size_t len_PYDICT(PYDICT *d) {
  return d->size;
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
