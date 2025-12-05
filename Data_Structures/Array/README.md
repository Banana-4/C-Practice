# Dynamic Array

Dynamic array is a seqeuntial linear data structure, that supports adding new elements in amortized constant time.

## Goal
Create a extenadble array for use inside my C programs.

## Why
Demonstartion of my skills:
- Memory managment
- Knowledge and understanding of Data Structures
- C programing skills
- System design

Personal use case:
- Building my own DS library.
- To solve my need for a dynamic array.
- To have a stack, for algorithms

## Feauters:
0. The Array works only with integer values.
1. Adding new elements to the end in amortized constant time
2. Random accsess in constant time.
3. Removing elements in linear time
4. Removing the last element in constant time, pop.
5. Efficently use of memory

## Tech:
1. C programing language
2. Heap memory

## Design:
The user works with a pointer to a Array, that is a struct.
Array operations are implamented as functions that use a pointer to the Array.
Array is a blackbox for the user, he doesnt needs to know what is inside.
The operations are self documenting.

### Moduls:
1. Data struct named Array.
2. Interface functions, operations that can be done with the Dynamic array.

### File Organization:
 Array
├──  src
│  └──  Array.c
├──  Array.h
└── README.md

### Operations:
0. Array(unsigened size)- creates a Array with the specifed size and return a pointer to it.
1. append(Array* a, int n)- the core function of the array, handles growing a array and adding new elements.
2. pop(Array* a) - removes the last element and returns its value.
3. at(Array* a, unsigned pos) - returns the element at position pos.
4. update(Array* a, unsigned pos, int n) - changes the value at position pos.
5. rempve(Array* a, unsigned pos) - removes the element at position pos.
6. destroy(Array* a) - clears the memory used by the Array a, sets the value of a = null;

### Implementation Details:  \
Array.h contains all the data needed to use the array.
The Array will only grow if the array is full and a new element is added, lazy grow.
The Array never shrinks, it is assumed that new elements will be added as long as the array is alive.
The growth factor is 2.
The default size is 8.

## Tests:




