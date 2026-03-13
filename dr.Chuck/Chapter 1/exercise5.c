#include <stdio.h>

int main() {
    int s = 0;
    int t = 0;
    int nl = 0;
    char c;
    while ((c = getchar()) != EOF) {
        if (c == ' ')
            s++;
        if (c == '\t')
            t++;
        if (c == '\n')
            nl++;
    }
    printf("Spaces: %d, Tabs: %d, New Lines: %d\n", s, t, nl);
}
