#include <string.h>
#include <stdbool.h>

bool atoi(char* s, int* v) {
    *v = 0;
    int sign = 1;
    while(*s == ' ' || *s =='\t' || *s == '\n') ++s;
    
    if(*s == '+' || *s == '-') {
        sign = (*s++ == '-') ? -1 : 1;
    }

    if(*s == '\0' || *s < '0' || *s > '9') return false;
    
    while(*s >= '0' && *s <= '9') {
        *v = 10 * *v + *s++ - '0';
    }
    
    *v *= sign;

    return true;
}


bool itoa(int v, char* s, int limit) {
    char d;
    char* start = s;
    s += limit - 2;
    int n = 0;
    do {
        d = (v % 10) + '0';
        if(n++ < limit - 1) {
           *s-- = d; 
        } else {
            return false;
        }
    } while (v /= 10);
    ++s;
   
    memmove(start, s, n);
    *(start + n) = '\0';
    return true;
}

