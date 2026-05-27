#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

char line[MAXLINE]; /* input line */
char save[MAXLINE]; /* longest line saved here */
int max; /* length of longest line seen so far */

int get_line();
void copy();

int main() /* find longest line; specialized version */
{
    int len;
    extern int max;
    extern char save[];
    max = 0;
    while ((len = get_line()) > 0)
        if (len > max) {
            max = len;
            copy();
        }
    if (max > 0) /* there was a line */
        printf("%s", save);
    return 0;
}

int get_line() /* specialized version */
{
    int c, i;
    extern char line[];

    for (i = 0; i < MAXLINE-1; ++i)
    {
       if((c = getchar()) == EOF) {
           line[i] = '\0';
           break;
       }
       line[i] = c;
       if (c == '\n') {
           line[++i] = '\0';
           break;
       }
    }
    return(i);
}

void copy() /* specialized version */
{
    int i;
    extern char line[], save[];

    i = 0;
    while ((save[i] = line[i]) != '\0')
        ++i;
}
