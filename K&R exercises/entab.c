#include <stdio.h>

#define MAX_SIZE 1000

int next_tab_stop(int start, int tab_width);
int entab(int write, int start, int end, char* buffer, int size, int tab_width);

int main() {
    char buffer[MAX_SIZE];
    int c;
    int write = 0;
    const int tab_width = 4;
    int start;
    int end;
    while((c = getchar()) != EOF) {
        if (write >= MAX_SIZE - 1) {
            return -1;
        }
        if (c == ' ') {
          end = start = write;
          while((c = getchar()) == ' ' && c != EOF) {
            ++end;
          }

          write = entab(write, start, end, buffer, MAX_SIZE - 1, tab_width);
          ungetc(c, stdin);
        }

        buffer[write++] = c;

    }
    buffer[write] = '\0';
    printf("Entab: %s\n", buffer);
    return 0;
}

inline int next_tab_stop(int start, int tab_width) {
    return tab_width - (start % tab_width);
}

int entab(int write, int start, int end, char* buffer, int size, int tab_width) {
    int tab_stop = 0;
    int total = end - start + 1;
    while((total - (tab_stop = next_tab_stop(start, tab_width))) > 0 && write < size) {
        start += tab_stop;
        total -= tab_stop;
        buffer[write++] = '\t';
    }

    while(total && write < size) {
        buffer[write++] = ' ';
        --total;
        }
    return write;
}
