#include "../include/LinkedList.h"
#include <stdio.h>
#include <stdbool.h>

bool validBracket(char *brackets, ERROR* signal) {
  LinkedList *stack = buildLinkedList(signal);
  if (*signal == no_error) {
    int i = 0;
    char b;
    while ((b = brackets[i]) != '\0') {
      if (b == ')' || b == ']' || b == '}') {
        int left = popList(stack, signal);
        if (*signal == empty_list || ((int)b) != left) {
          return false;
        }
      }
      switch (b) {
      case '(':
        pushList(stack, ')', signal);
        if (*signal != no_error)
          return false;
        break;
      case '[':
        pushList(stack, ']', signal);
        if (*signal != no_error)
          return false;
        break;
      case '{':
        pushList(stack, '}', signal);
        if (*signal != no_error)
          return false;
        break;
      }
      ++i;
    }
  bool res = emptyList(stack, signal);

  if (*signal == no_error) {
    return res;
  }
  }
  return false;
}

int main() {
  ERROR signal = no_error;
  char *brackets = "[([]{})]";
  if (validBracket(brackets, &signal)) {
    printf("Good Bracket String\n");
  } else {
    printf("Bad Bracket String\n");
  }
  return 0;
}