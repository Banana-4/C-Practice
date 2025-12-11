#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  int_type,
  double_type,
  char_type,
} TYPE;

typedef struct Array Array;

Array *build_array(unsigned size, TYPE t);
Array *build_array_default(TYPE t);
bool append_array(Array *a, void* n);
bool at_array(Array *a, unsigned p, void* out);
bool pop_array(Array *a,  void* out);
bool array_remove(Array *a, unsigned p);
void destroy_array(Array *a);
