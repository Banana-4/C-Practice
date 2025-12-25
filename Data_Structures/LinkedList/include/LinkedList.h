#include <stdbool.h>
#include <stdlib.h>

typedef struct LinkedList LinkedList;
typedef struct IteratorList IteratorList;
typedef enum { no_error, index_out_of_range, empty_list, null_node, memory_fail, null_iter, end_of_list, no_list } ERROR;

LinkedList *buildLinkedList(ERROR* signal);
int* peekFront(LinkedList *l, ERROR *signal);
int* peekBack(LinkedList *l, ERROR *signal);
int* atList(LinkedList* l, unsigned pos, ERROR* signal);
void insertList(LinkedList *l, unsigned pos, int n, ERROR* signal);
void removeList(LinkedList *l, unsigned pos, ERROR *signal);
void pushList(LinkedList *l, int n, ERROR *signal);
void appendList(LinkedList *l, int n, ERROR *signal);
int popList(LinkedList *l, ERROR *signal);
bool emptyList(LinkedList* l, ERROR* signal);

void destroyList(LinkedList *l, ERROR *signal);

IteratorList *iteratorList(LinkedList *l, ERROR* signal);
void nextNode(IteratorList *iter, ERROR* signal);
int* valueNode(IteratorList* iter, ERROR* signal);