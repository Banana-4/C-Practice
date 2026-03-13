#include <stdio.h>
#include <stdbool.h>
int main() {
    bool s = false;
    char c;
    while ((c = getchar()) != EOF) {
        if (s && c != ' ') {
          s = false;
        }
        if (!s) {
            putchar(c);
            if (c == ' ')
                s = true;
        }
    }
}
