#include "../Array.h"
#include <stdbool.h>
#include <stdlib.h>

struct Array{
  unsigned size;
  unsigned used;
  void* array;
  TYPE type;
};


bool grow_array(Array *a) {
  const int GROWTH_FACTOR = 2;
  switch (a->type) {
  case int_type: {
    int* new = malloc(a->size * GROWTH_FACTOR * sizeof(int));
    if (new) {
      int * array = (int*) a->array;
      memcpy(new, a->array, a->used * sizeof(int));
      free(a->array);
      a->array = (void *)new;
      a->size = a->size * GROWTH_FACTOR;
      return true;
    }
    return false;
  }
  case double_type: {
    double *new = malloc(a->size * GROWTH_FACTOR * sizeof(double));
    if (new) {
      double *array = (double *)a->array;
      memcpy(new, a->array, a->used * sizeof(double));
      free(a->array);
      a->array = (void *)new;
      a->size *= GROWTH_FACTOR;
      return true;
    }
    return false;
    }
  case char_type: {
    char *new = malloc(a->size * GROWTH_FACTOR * sizeof(char));
    if (new) {
      char* array = (char*) a->array;
      memcpy(new, a->array, a->used * sizeof(char));
      free(a->array);
      a->array = (void*)new;
      a->size = a->size * GROWTH_FACTOR;
      return true;
    }
    return false;
  }
  default:
      return false;
    }
}

Array *build_array(unsigned size, TYPE t) {
  Array *a = (Array *)malloc(sizeof(Array));
  if (!a) {
    return NULL;
  }
  a->size = size;
  a->type = t;
  a->used = 0;
  switch (a->type) {
  case int_type:
    a->array = malloc(a->size * sizeof(int));
    break;
  case double_type:
    a->array = malloc(a->size * sizeof(double));
    break;
  case char_type:
    a->array = malloc(a->size * sizeof(char));
    break;
  default:
    a->array = NULL;
    break;
  }
  if (!a->array) {
    free(a);
    return NULL;
  }
  return a;
}

Array *build_array_default(TYPE t) {
  return build_array(8, t);
}

bool append_array(Array *a, void* n) {
  if (!a)
    return false;

  if (a->used == a->size) {
    if (!grow_array(a)) {
      return false;
    }
  }
  switch (a->type) {
  case int_type:
    ((int*)a->array)[a->used++] = *(int*)n;
    break;
  case double_type:
    ((double *)a->array)[a->used++] = *(double *)n;
    break;
  case char_type:
    ((char *)a->array)[a->used++] = *(char *)n;
    break;
  default:
    break;
  }
  return true;
}

bool at_array(Array *a, unsigned p, void* out) {
  if (!a || p >= a->used)
    return false;
  switch (a->type) {
  case int_type:
    *(int*)out = ((int*)a->array)[p];
    break;
  case double_type:
    *(double *)out = ((double *)a->array)[p];
    break;
  case char_type:
    *(char *)out = ((char *)a->array)[p];
    break;
  default:
    break;
  }
  return true;
}
bool pop_array(Array *a, void* out) {
  if (!a || !a->used) {
    return false;
  }
  --a->used;
  switch (a->type) {
  case int_type:
    *(int *)out = ((int *)a->array)[a->used];
    break;
  case double_type:
    *(double *)out = ((double *)a->array)[a->used];
    break;
  case char_type:
    *(char *)out = ((char *)a->array)[a->used];
    break;
  default:
    break;
  }
  return true;
}

bool array_remove(Array *a, unsigned p) {
  if (!a || p >= a->used)
    return false;
  switch (a->type) {
  case int_type: {
    int* array = (int*) a->array;
    for (unsigned i = p + 1, j = p; i < a->used; ++i)
      array[j++] = array[i];
    break;
  }
  case double_type: {
    double *array = (double *)a->array;
    for (unsigned i = p + 1, j = p; i < a->used; ++i)
      array[j++] = array[i];
    break;
  }
  case char_type: {
    char *array = (char *)a->array;
    for (unsigned i = p + 1, j = p; i < a->used; ++i)
      array[j++] = array[i];
    break;
  }
  default:
    break;
  }
  --a->used;
  return true;
}

void destroy_array(Array *a) {
  free(a->array);
  free(a);
}
