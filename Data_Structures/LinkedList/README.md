# Linked List
DATE: 23-12-2025

## What is it?

Linked List is a memory managment subsystem that manages disjointed memory blocks by arranging them into a sequence.
That allows storing arbitary amounts of data, and provides constant time end points insertion, deletion and data accsess.

## Terms:

1. Node - a single memory block.
2. Head - the first node of a sequence.
3. Tail - the last node of a sequence.
4. Iterator - a object used in traversing the list in sequential order, by passing it to a function that moves the iterator to the next node in sequence.

## Structure of The Linked List:

Linked List is a sequence of nodes that are linked by pointers.

A list stores:
    1. the head.
    2. the tail.
    3. the length.

A NULL pointer is used as a terminator to signal the end of the sequence.

## Structure of a node:

A node is a plain data structure that stores:
    1. Value, the data that is stored in the list.
    2. Pointer to the next node in the sequence.

## Supported Operations:
    0. Building - creates a new Linked List.
    1. Insertion - inserts a new node at any point in the sequence.
    2. Iteration - moves through the nodes one by one in sequence
    3. Removal - removing a node from the list
    4. Appending - adding to the end
    5. Pushing - adding to the front
    7. Pop - removing from the start

## Invariants:
    1. A Linked List operation removal and insertion will never break the node sequence.
    2. NULL pointer is only used as a terminator to signal the end of the list.
    3. The list will not have a node without data
    4. Each node in the list points to the next node except the last it points to null.
    5. The head and tail nodes are null only if the list is empty.
    6. A Node will only by linked to its neighbours in sequence, this Data Structure is not a graph or a tree.
    7. A empty list can be only used to insert a node at start.
    8. The state where a part of the list is left dangling, without a pointer that leads to it, will not be reached.
    9. A null node will never be used in iterations.

## File Organization:
```
/LinkedList
    /include
        LinkedList.h
    /src
        linkedList.c
    /test
        brackets.c
    README.md

```

## Tech Stack:

C programing language

## Impplementation:
LinkedList that stores only int.

## Structs:

```
Node:
    int data;
    Node* next;

LinkedList:
    Node* head;
    Node* tail
    unsigned length;

LinkedListIterator:
    Node* current;


```
## Error Enum:
```
ERROR {
  index_out_of_range,
  empty_list,
  null_node,
  memory_fail
}
```
## Interface:

```
typedef LinkedList - the linked list struct
typedef ListIterator - the iterator struct
enum ERROR - the signals for various errors.

LinkedList* build_linkedList() - creates the LinkedList struct and sets the head and tail to point to null, length to zero.

int peekHead(LinkedList* l, ERROR* signal) - returns the value stored at the head node
int peekTail(LinkedList* l, ERROR* signal) - return the value stored in the tail node
void insertList(LinkedList* l, int n, int pos, ERROR* signal) - inserts a node at position p, only if p is in the range [0, length].
void removeList(LinkedList* l, int pos, ERROR signal) - removes the node at position p if p is in the list range else signals a error
void pushList(LinkedList* l, int n, ERROR* signal) - adds a new node to the start
void appendList(LinkedList* l, int n, ERROR* signal) - adds a new node to the end, if the list is empty adds to the start.
int peekFrontList(LinkedList* l, ERROR* signal) - returns the value at the head
int peekBackList(LinkedList* l, ERROR* signal) - returns the value at the tail.
void destroyList(LinkedList* l, ERROR* signal) - frees the used memory.
int popList(LinkedList* l, ERROR* signal) - removes the first node and returns the stored value.

IteratorList* iteratorList(LinkedList* l, ERROR* signal) - creates a iterator
void nextNode(IteratorList* iter, ERROR* signal) - moves the iterator to the next node in sequence
int valueNode(IteratorList* iter, ERROR* signal) - returns the value of the current node

```


