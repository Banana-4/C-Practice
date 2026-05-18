#include <stdio.h>
int lower(int c) { return (c >= 'A' && c <= 'Z') ? ('a' + (c - 'A')) : c; }

int main() {
  const char *str = "(111HELLO, WORLD!!!111)";
  while (*str) {
    printf("%c", lower(*str));
    str++;
  }
  printf("\n");
  return 0;
}
