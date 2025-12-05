#include "../Array.h"
#include <stdbool.h>
#include <stdlib.h>

bool grow_array(Array *a) {
  const int GROWTH_FACTOR = 2;
  int *new = (int *)malloc(a->size * GROWTH_FACTOR * sizeof(int));
  if (new) {
    for (int i = 0; i < a->used; ++i) {
      new[i] = a->array[i];
    }
    free(a->array);
    a->array = new;
    a->size = a->size * GROWTH_FACTOR;
    return true;
  }
  return false;
}

Array *build_array(unsigned size) {
  Array *a = (Array*)malloc(sizeof(Array));
  if (!a) {
    return a;
  }
  a->size = size;
  a->used = 0;
  a->array = (int *)malloc(a->size * sizeof(int));
  if (!a->array) {
    free(a);
    return NULL;
  }
  return a;
}

Array *build_array_default() {
  return build_array(8);
}
bool append_array(Array *a, int n) {
  if (a->used == a->size) {
    if (!grow_array(a)) {
      return false;
    }
  }
  a->array[a->used++] = n;
  return true;
}

bool at_array(Array *a, unsigned p, int* out) {
  if (p >= a->used) return false;
  *out = a->array[p];
  return true;
}
bool pop_array(Array *a, int* out) {
  if (!a->used) {
    return false;
  }
  --a->used;
  *out = a->array[a->used];
  return true;
}

bool array_remove(Array *a, unsigned p) {
  if (p >= a->used) return false;
  for (int i = 0, j = 0; i < a->used; ++i) {
    if (i != p) {
      a->array[j++] = a->array[i];
    }
  }
  --a->used;
  return true;
}
void destroy_array(Array *a) {
  free(a->array);
  free(a);
}
