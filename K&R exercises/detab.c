#include <stdio.h>

#define MAX_BUFFER 1000

int detab(char* buffer, int pos, int blanks, int max_size);

int main() {
    int max_size = MAX_BUFFER;
    char buffer[max_size];
    int c;
    int write = 0;
    int overflow = 0;
    int tab_width = 4; /*tabs to blanks*/
    while((c = getchar()) != EOF) {
        if (write == max_size - 1) {
            overflow = 1;
            break;
        }
        if (c == '\t') {
           int spaces = tab_width - (write % tab_width);
           write = detab(buffer, write, spaces, max_size);
        } else {
            buffer[write] = c;
            ++write;
        }
    }

    if (overflow) {
        printf("Error buffer overflow!!!\n");
        return -1;
    }

    buffer[write] = '\0';

    printf("DETAB: %s\n", buffer);

    return 0;
}


int detab( char* buffer, int position, int blanks, int max_size)  {
     while (position < max_size - 1 && blanks ) {
        buffer[position] = ' ';
        ++position;
        --blanks;
     }
     return position;
}

