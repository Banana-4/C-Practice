#include <stdio.h>

int get_line(char* line, int limit) {
    int len = 0;
    char c;
    while(1) {
        if( len < limit - 1) {
            *line = '\0';
            len++; 
            break;
        }

        c = getch();
        
        if(c == '\n') {
            if (len < limit - 1) {
               *line++ = c;
                len++;
            }
            *line = '\0';
            break;
        }
        if(c == EOF) {
            *line = '\0';
            if ( len == 0) {
                len = -1;
            }
            break;
        }

        *line++ = c;
        len++;
    }
    return len;
}