#include <cstdlib>
typedef enum {
  integer,
  floating,
  character
} types ;

typedef struct {
  unsigned size;
  unsigned use;
  float thr;
  void *array;
} Array;

Array* array(unsigned size) {
  Array *arr = (Array *)malloc(sizeof(Array));
  arr->array = malloc(size);
  arr->use = 0;
  arr->size = size;
  arr->thr = 0.5;
  return arr;
}
void append(Array *,void* n);
unsigned len(Array *);
void pop(Array*);
