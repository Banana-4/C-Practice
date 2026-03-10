#include <stdio.h>
#include <stdlib.h>

struct pystring {
    size_t size;
    size_t len;
    char *string;

    struct pystring *(*append) (struct pystring*, char);
    char (*get)(struct pystring*, int);
    void (*del)(struct pystring *);
    struct pystring *(*appends) (struct pystring*, char*);

};

struct pystring *append(struct pystring *s, char c) {
  if (s == NULL)
      return NULL;

  if (s->len == s->size) {
      s->size *= 2;
      char* tmp = realloc(s->string, s->size);
        if (!tmp) {
          return NULL;
      }
      s->string = tmp;
  }
  s->string[s->len++] = c;
  s->string[s->len] = '\0';
  return s;
}

char get(struct pystring *s, int i) {
  if (i > -1 && i < s->len) {
      return s->string[i];
  }
  return NULL;
}


void del(struct pystring *s) {
  if (!s)
      return;
  free(s->string);
  free(s);
}

struct pystring *appends(struct pystring *s, char *str) {
    char c;   
    while ((c = *str++)) {
      s->append(s, c);
  }
  return s;
}

void dump(struct pystring *s) {
    printf("Length: %zu, Size: %zu, String: %s\n", s->len, s->size, s->string);
}

struct pystring *new_pystring() {
    static const size_t size = 8;
    struct pystring *s = (struct pystring*) malloc(sizeof(struct pystring));
    if (!s)
        return NULL;
    s->string = malloc(size);
    if (!s->string) {
        free(s);
        return NULL;
    }
    s->string[0] = '\0';
    s->size = size;
    s->len = 0;
    s->append = &append;
    s->del = &del;
    s->appends = &appends;
    s->get = &get;

    return s;
}

struct pystring *assign_pystring(struct pystring *s, char *str) {
    s = new_pystring();
    if (!s)
        return NULL;
    return s->appends(s, str);
}


int main() {
    struct pystring *s1 = new_pystring();
    s1->append(s1, 'H');
    dump(s1);
    s1->appends(s1, "ello world!");
    dump(s1);
    s1->del(s1);
    s1 = assign_pystring(s1, "A new Day!");
    dump(s1);
    s1->del(s1);
}
