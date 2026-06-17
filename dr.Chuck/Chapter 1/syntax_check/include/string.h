#pragma once
#include <stddef.h>
#include <stdlib.h>

typedef struct String {
  size_t len;
  size_t size;
  char *str;

} String;

String *create_str(size_t size);
void str_append(String *s, const char ch);
size_t str_len(const String *s);
const char *str(const String *s);
void str_delete(String *s);
