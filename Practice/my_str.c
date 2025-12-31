#include <stdio.h>
#include <stdlib.h>

int my_strlen(const char* s) {
  if(!s) return -1;
  int i = 0;
  while(*s++) i++;
  return i;
}

char* my_strdup(char* s) {
  if (!s) {
    return NULL;
  }
  unsigned len = my_strlen(s);
  char* dup = (char*)malloc(sizeof(char)*len + 1);
  if (!dup) {
    return NULL;
  }
  unsigned i;
  for(i = 0; s[i]; i++) {
    dup[i] = s[i];
  }
  dup[i] = '\0';
  return dup;
}

// tests
int main() {
  printf("Testing my_strlen:\n");
  printf("Expected: 0, Got: %d\n", my_strlen("") );
  printf("Expected: 14, Got: %d\n", my_strlen("hello, world!\n"));
  printf("Expected: -1, Got: %d\n", my_strlen(NULL));
  
  printf("Testing my_strdup:\n");
  printf("Expected: , Got: %s\n", my_strdup("") );
  printf("Expected: hello, world!, Got: %s", my_strdup("hello, world!\n"));
  printf("Expected: NULL, Got: %s\n", my_strdup(NULL));

  return 0;
}
