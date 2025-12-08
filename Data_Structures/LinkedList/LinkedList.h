#include <stdbool.h>
#include <stdlib.h>
#include "../Array/Array.h"

typedef struct LinkedList LinkedList;
typedef struct ListIterator ListIterator;
LinkedList* build_list();
LinkedList* build_list_array(Array* a);
void destroy_list(LinkedList *l);
unsigned len_list(LinkedList *l);

bool append_list(LinkedList *l, int n);
bool add_list(LinkedList *l, int n);
bool remove_list(LinkedList *l, unsigned p, int *out);
bool insert_list(LinkedList *l, unsigned p, int n);
bool list_next(ListIterator *i);
ListIterator *list_iterator(LinkedList *l);
bool list_value(ListIterator* i, int* out);
void destroy_list_iterator(ListIterator* i);
