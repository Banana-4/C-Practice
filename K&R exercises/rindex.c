#include <stdio.h>
#include <string.h>
// assumes int is 4 bytes
int rtindex(char s[], char p[]) {
  int end_p = (sizeof(char) * strlen(p)) / sizeof(int);
  int end_s = (sizeof(char) * strlen(s)) / sizeof(int);
  if (end_p > 0) {
    int* s_int = (int *)s;
    int* p_int = (int *)p;
    for (int i = end_s - 1; i >= 0; --i) {
      int k = end_p - 1;
      int j = i;
      while (k >= 0 && j >= 0 && s_int[j] == p_int[k]) {
        --k;
        --j;
      }
      if (k < 0)
        return j + 1;
    }
  } else {
    int end_s = (int)strlen(s) - 1;
    int end_p = (int)strlen(p) - 1;

    for (int i = end_s; i >= 0; --i) {
      int j = i;
      int k = end_p;

      while (j >= 0 && k >= 0 && s[j] == p[k]) {
        j--;
        k--;
      }

      if (k < 0) {
        return j + 1;
      }
    }
    }
  return -1;
}

int main() {
  char *test[] = {"the man", "sleeps", " in the barn."};
  for (int i = 0; i < 3; ++i) {
    if (rtindex(test[i], "the") > -1) {
      printf("%s\n", test[i]);
    }
  }
  return 0;
}
