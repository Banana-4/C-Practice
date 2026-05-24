#include <stdio.h>
#include <stdbool.h>

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

size_t strip(char *line, size_t len) {
    if (len <= 0 || !line) {
        return 0;
    }
    
    bool nl = line[len - 1] == '\n';
    while ( len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\t' || line[len - 1] == ' ')) {
        --len;
    }

    if (nl && len != 0) {
        line[len++] = '\n';
    }

    line[len] = '\0';

    return len;
}

int main() {
    const size_t MAX = 10000;
    char line[MAX];
    size_t len;
    while ((len = get_line(line, MAX)) > 0) {
        len = strip(line, len);
        if (len > 0)
            printf("New Line: %s", line);

    }
    return 0;
}
