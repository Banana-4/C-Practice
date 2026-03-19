#include <stdio.h>
#include <stdbool.h>

int main() {
   inword = false;
   char c;
   while ((c = getchar()) != EOF) {
       if( c != ' ' && c != '\t' && c != '\n' ) {
           inword = true;
           printf(c);
       } else if (inword == true) {
           printf("\n");
           inword = false;
       }
   }
}
