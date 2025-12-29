#include <stdio.h>
#include "memory.h"

#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0; /* stack pointer */
double val[MAXVAL]; /* value stack */

int inUse[26] = {0};
double vars[26] {0};

double push(f) /* push f onto value stack */
double f;
{
  if (sp < MAXVAL)
    return(val[sp++] = f);
  else {
    printf("error: stack full\n");
    clear();
    return(0);
  }
}

double pop() /* pop top value from stack */
{
  if (sp > 0)
    return(val[--sp]);
  else {
    printf("error: stack empty\n");
    clear();
    return(0);
  }
}

clear() /* clear stack */
{
  sp = 0;
}



void store_var(char name,double f) {
	if (name >= 'a' && name <= 'z') {
			int index = name - 'a';
			vars[index] = f;
			inUse[index] = 1;
	} else {
		printf("Variable names can only by single letters from a-z.\n");
	}
}

int get_val(char name, double* val) {
	if (name >= 'a' && name <= 'z') {
		int index = name - 'a';
		if (inUse[index]) {
			*val = vars[index];
			return 1;
		}
	}
	return 0;
}

int stack_odd() {
	return sp % 2;
}
