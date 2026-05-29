#include "linkedList.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t getLine(char *line, const size_t LIMIT) {
  int c, i;

  for (i = 0; i < LIMIT - 1; ++i) {
    if ((c = getchar()) == EOF) {
      break;
    }
      line[i] = c;
    if (c == '\n') {
        ++i;
        break;
      }
  }
  line[i] = '\0';
  return i;
}

//note detab functions can remove parts of the line if the tabs expansion hits the limit
size_t detab(char* buffer, char *line, const size_t LIMIT, const int TABSTOP) {
  size_t i = 0;
  for (; i < LIMIT - 1 && *line != '\0'; ++line) {
    if (*line == '\t') {
      int spaces = TABSTOP - (i % TABSTOP);
      while (i < LIMIT - 1 && (spaces > 0)) {
          buffer[i++] = ' ';
          --spaces;
      }
    } else {
      buffer[i++] = *line;
    }
  }
  buffer[i] = '\0';
  return i;
}

bool save_str(char *s, size_t len, LinkedList *list) {
  char *save = (char *)malloc(len + 1);
  if (!save) {
    return false;
  }
  strncpy(save, s, len);
  return append(list, save);
}
void print_lines(LinkedList *lines) {
  printf("Printing lines\n");
  Node *node = lines->head;
  while (node) {
    printf("%s", node->value);
    node = node->next;
  }
}

int main() {
  const size_t LIMIT = 1000;
  const int TABSTOP = 4;
  char line[LIMIT];
  size_t len;
  LinkedList *lines = constructList();
  bool fail = false;
  if (!lines) {
    return 1;
  }

  while (!fail && getLine(line, LIMIT) > 0) {
    char buffer[LIMIT];
    len = detab(buffer, line, LIMIT, TABSTOP);
    fail = !save_str(buffer, len, lines);
  }

  if (!fail) {
    print_lines(lines);
  }

  destroy(lines);
  return fail ? 1 : 0;
}
