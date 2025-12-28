#include <stdio.h>
#define MAXOP 20 /* max size of operand, operator */
#define NUMBER '0' /* signal that number found */
#define TOOBIG '9' /* signal that string is too big */
#define VAR '$'
#define var_VAL '*'

main() /* reverse Polish desk calculator */
{
  int type;
  char s[MAXOP];
  double op2, atof(), pop(), push();

  while ((type = getop(s, MAXOP)) != EOF)
    switch (type) {

    case NUMBER:
        push(atof(s));
        break;
    case 'a' ... 'z':
		if (getop(s, MAXOP) == '=') {
			
		}
		push(get_var(type, s));
		break;
    case '+':
        push(pop() + pop());
        break;
    case '*':
        push(pop() * pop());
        break;
    case '-':
        op2 = pop();
        push(pop() - op2);
        break;
    case '/':
        op2 = pop();
        if (op2 != 0.0)
          push(pop() / op2);
        else
          printf("zero divisor popped\n");
        break;
    case '%':
			op2 = pop();
			push(pop() % pop());
			break;
	case VAR:
		store_var(atof(s));
		break;
    case '=':
        printf("\t%f\n", push(pop()));
        break;
    case 'c':
        clear();
        break;
    case TOOBIG:
        printf("%.20s ... is too long\n", s);
        break;
    default:
        printf("unknown command %c\n", type);
        break;
    }
}
