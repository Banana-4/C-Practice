#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Stack
{
    size_t len;
    size_t size;
    char* items;

}Stack;

Stack *create_stack();
bool push(Stack *s, char ch);
int peek(const Stack *s);
void pop(Stack *s);
void stack_delete(Stack *s);
