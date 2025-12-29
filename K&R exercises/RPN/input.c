#include <stdio.h>
#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

getch() /* get a (possibly pushed back) character */
{
  return((bufp > 0) ? buf[--bufp] : getchar());
}

ungetch (c) /* push character back on input */
int c;
{ 
if (c == EOF) {
	  bufp = 0;
	  buf[bufp++] = c;
	  return;
	}
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else 
    buf[bufp++] = c;

}

void ungets(char* s) {
	int i;
	while(s[i] != '\0') {
		++i;
	}
	--i;
	for(; s[i] != '\0' && i < BUFFERSIZE - 1; i--) {
		ungetch(s[i]);
	}
	if(i != 0) {
		printf("ungets: too many characters\n");
	}
}
