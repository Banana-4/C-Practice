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
void del_dnode(dnode *dn) {
    if (!dn)
        return;
    del_dnode(dn->_left);
    del_dnode(dn->_right);
    free(dn->_key);
    free(dn->_value);
    free(dn);
}

void del_PYDICT(PYDICT *d) {
    del_dnode(d->root);
}

dnode *insert_dnode(dnode *dn, char *key, char *val) {
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
      return dn;
  }

  int cmp = strcmp(dn->_key, key);
  if (cmp == 0) {
      char *tmp = strdup(val);
      if (tmp) {
          free(dn->_value);
          dn->_value = tmp;
      }
  } else if (cmp > 0) {
      dn->_right = insert_dnode(dn->_right, key, val);
  } else {
      dn->_left = insert_dnode(dn->_left, key, val);
  }
  return dn;
}

void insert_PYDICT(PYDICT *d, char *key, char *val) {
    d->root = insert_dnode(d->root, key, val);
}


int main() {

}
