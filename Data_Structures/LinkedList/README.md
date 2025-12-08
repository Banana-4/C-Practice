# Linked List

## Goal:
A practice project for C programing and system design.
The goal is to design a data storing system (Linked List), that:
1. Stores sequential data.
2. It is made from a chain of nodes, links
3. The node knows only what the data is and what is the next node in sequence
4. Any amount of data can be stored, only if ther is enough memory.
5. Safe to use.


## Use cases:
This data structure is for my personal use. I intend to use it in my projects, as a base for other data structures example stack.
For a system that needs to work with collections of data of unknow sizes and that uses as least memory as posbile, a dynamic array uses double memory when it grows, both for the new array and inside the grow function.
For fast end point accses, modifications, creation and removal.
The user wants to use only a pointer to a linked list without any knowledge of nodes or how the operations work.

## Requerments - Feauters:
0. The size of the list should always be known and accsesd in O(1).
1. End point operation should be done in constant time.
2. Memory use should not be much greater then the memory needed to store the data.
3. Liner traversel.
4. Support of removing and inserting elements at any position in the sequence, linear time.
5. The travelser will be done using a iterator with a next method and a value method that returns the data.
6. Work only with integer type.
7. destruction is linear, each node needs to be destroyed.

## System Description:

### Main idea:
A Linked list is a system for storing sequential data. The system uses a chain of nodes to create a sequence from non-contiguous memory. That is achived by nodes having a pointer to the next node address.
Having such a system, gives the abilty to store unknow number of elements in the collection, that is only limited by the amount of memory avaliable to the system. The tradeoff is that data can be accsess only in sequence and a double amount of memory needed to store the data. In turn using the data at the end points, adding and removing nodes to ends is O(1).

## How the system operates:

The data enters the Linked List through the append and add methods.
The data is inside a node, that is inserted to position in the chain of nodes that a list manages.
The list stores the first and last node, head and tail, and the length of the list.
Traversing the list is done using a iterator. The iterator is a struct that contains a node from the list, and can only show the stored data using the list_value() or move to the next node by passing it to the list_next().
Using iterator is the best option, other options would be to complex to use, store the current node in the linkelist, use a function to move it forward, if there is a need to start oveer the current node needs to be reseted.

## Tech:
C programing language:
    1. Pointers.
    2. Structs.

## Modules:
Structure:
LinkedList - struct that has two nodes, the start and end node, and a varaible for the size.
Node - struct of a pointer to the next node in sequence and holds the data value.
Iterator - a struct that is used to iterate over the list. It contains a node pointer, that is set to the head on createon.

Operations:
Bool values are used to signal the succses or failure of a operation.
LinkedList* build_list() - returns a empty LinkedList struct, both pointers are set to null
LinkedList* build_list_array(Array a) - creates a linked list from a array.
Both constructors return null on error.

int len_list(LinkedList* l) - the legth of the list

Iterator* iterator(LinkedList* l) - returns Iterator pointer that holds the head of the list.
bool append_list(LinkedList* l, int n) - creates a new node with n and adds it to the end of the list.
bool add_list(LinkedList* l, int n) - adds a node that holds n to the front of the list.
bool remove_list(LinkedList* l, unsigned p, int* out) - removes a node at position p and returns the stored data at p.
bool insert_list(LinkedList* l, unsigned p, int n) - inserts a new node at position p.
Iterator* next(Iterator* i) - moves the iterator forward, returns null if it gets beyond the end.
bool value(Iterator* i, int* out) - output the value of the node, returns false if the iterator is null.

void destroy_iterator(Iterator* i) - free the memory used by the iterator.
void destroy_list(LinkedList* l) - free the used memory, linear time.

## File organization:
/LinkedList
    /src
        LinkedList.c - contains all the methods and struct defenitions.
    LinkedList.h - provides only the interface.
    README.md

## Functions Documentation:



## Tests:
1. Create a empty list
2. Create a list from a array
3. Create a list from a empty array.
4. add to front
5. append to end
6. remove front and end.
7. remove a elemnt in the range of the list.
8. try to remove a  element out of bonds.
9. insert a item in the list.
10. insert a item out of bonds.
11. destroy a list
12. destroy a empty list.
13. create iterator
14. iterate to the end and print each item.
15. try to go beyond the end of the list and use the value.
16. destroy a iterator.

## Future improvments:
1. signal errors, a system that will track the state of the list, if a memory allocation faild, out of bonds.
2. Allow the list to hold any data type.
