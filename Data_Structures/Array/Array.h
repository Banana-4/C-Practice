#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  unsigned size;
  unsigned used;
  int* array;
} Array;

Array *build_array(unsigned size);
Array *build_array_default();
bool append_array(Array *a, int n);
bool at_array(Array *a, unsigned p, int* out);
bool pop_array(Array *a, int* out);
bool array_remove(Array *a, unsigned p);
void destroy_array(Array *a);
