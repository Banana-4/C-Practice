#include <stdio.h>

size_t get_line(char *line, size_t limit) {
    char c;
    size_t i = 0;
    for (; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        line[i] = c;
    }

    if (c == '\n') {
        line[i++] = c;
    }

    line[i] = '\0';

    return i;
}
void reverse(char *s, size_t len) {
    if (!s || len == 0) {
      return;
    }

    char *left = s;
    char *right = s[len - 1] != '\n' ? &s[len - 1] : &s[len - 2];
    char left_ch;
    while (left < right) {
        left_ch = *left;
        *left = *right;
        *right = left_ch;
        ++left;
        --right;
    }
}

int main() {
    const size_t MAX = 10000;
    char line[MAX];
    size_t len;
    while ((len = get_line(line, MAX)) > 0) {
        reverse(line, len);
        printf("%s",line);
    }
    return 0;
}
