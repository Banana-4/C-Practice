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

int main() {
    const int TARGET_LENGTH = 80;
    const size_t MAX = 10000;
    char line[MAX];
    size_t length;
    while ((length = get_line(line, MAX)) > 0) {
        if (length >= TARGET_LENGTH) {
            printf("%s", line);
      }
    }
    return 0;
}
