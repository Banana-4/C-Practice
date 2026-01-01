#include <stdio.h>
#define SIZE 32
#define NOT_A_NUMBER 0

char buffer[SIZE] = {0};
int sp = 0;

int getch() {
  return (sp > 0 ? buffer[sp--] : getchar());
}

void ungetch(int c) {
  if (sp < SIZE) {
    buffer[sp++] = c;
  } else {
    printf("To many characters in ungetch.\n");
  }
}

int get_float(double* v) {
  int c, sign;
  double power;
  while((c = getch()) == ' ' || c == '\t' || c == '\n');
  sign = 1;
  if (c == '+' || c == '-') {
    sign = (c == '+') ? 1 : -1;
    c = getch();
  }
  
  if ( c != '.' && (c < '0' || c > '9')) return NOT_A_NUMBER;

  for (*v = 0; c >= '0' && c <= '9'; c = getch()) {
    *v = 10 * *v + c - '0';
  }

  if(c == '.') {
      c = getch(); 
      if ( c < '0' || c > '9') 
        return NOT_A_NUMBER;
    }
  for (power = 1.0; c >= '0' && c <= '9'; c = getch()) {
    *v = 10 * *v + c - '0';
     power *= 10;
    }
  *v = sign * *v  / power;
  if (c != EOF) {
    ungetch(c);
  }
  return c;
}
