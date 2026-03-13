#include <stdio.h>
#define TAB '>'
#define BSPACE '<'
int main() {
    char c;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            putchar(TAB);
            putchar(TAB);
            putchar(TAB);
        }
        if (c == '\b') {
            putchar(BSPACE);
            putchar(BSPACE);
            putchar(BSPACE);
        }
    }
}
