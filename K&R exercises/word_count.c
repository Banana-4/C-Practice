#include <stdio.h>
#include <string.h>
#define NKEYS 7
#define MAXWORD 20
#define LETTER 'a'
#define DIGIT '0'
#define type(c) (ascii_table[(unsigned char)c]) 

static const uint8_t ascii_table[128] = {
    /* 0x00–0x1F: control characters */
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9,10,11,12,13,14,15,
   16,17,18,19,20,21,22,23,
   24,25,26,27,28,29,30,31,

    /* 0x20–0x2F: space and punctuation */
    32,33,34,35,36,37,38,39,
    40,41,42,43,44,45,46,47,

    /* 0x30–0x39: '0'–'9' */
    DIGIT, DIGIT, DIGIT, DIGIT, DIGIT,
    DIGIT, DIGIT, DIGIT, DIGIT, DIGIT,

    /* 0x3A–0x40 */
    58,59,60,61,62,63,64,

    /* 0x41–0x5A: 'A'–'Z' */
    LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,
    LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,
    LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,
    LETTER, LETTER, LETTER, LETTER, LETTER,

    /* 0x5B–0x60 */
    91,92,93,94,95,96,

    /* 0x61–0x7A: 'a'–'z' */
    LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,
    LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,
    LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,
    LETTER, LETTER, LETTER, LETTER, LETTER,

    /* 0x7B–0x7F */
    123,124,125,126,127
};

int main() {

  struct Key {
    char* key;
    int keycount;
  };
  Key keytab[]{
    "break", 0,
    "case", 0,
    "char", 0,
    "continue", 0,
    "default", 0,
    "unsigned", 0,
    "while",0
  };

  int n, t;
  char word[MAXWORD];
  while ((t = getword(word, MAXWORD)) != EOF) {
    if (t == LETTER) 
      if ((n = binary(word, keytab, NKEYS)) >= 0) 
        keytab[n].keycount++;
    }

  for (n = 0; n < NKEYS; n++)
    if(keytab[n].keycount > 0) 
      printf("%4d %s\n",keytab[n].keycount, keytab[n].keyword);
    return 0;
}

int binary(char* word, Key tab[], int n) {
    int low = 0;
    int high = n - 1;
    int mid = -1;
    int cond;
    while (low <= high) {
      mid = (low + high) / 2;
      if((cond = strcmp(word, tab[mid].keyword)) < 0)
        high = mid - 1;
      else if (cond > 0)
        low = mid + 1;
      else
        return mid;
    }
    return -1;
  }

int sp = -1;
char buff[10];

int getch() {
  return (sp >= 0) ? buff[sp--] : getchar();
  }

void ungetch(int ch) {
    if (sp >= 10) {
      printf("Buffer full.\n");
    } else 
      buff[++sp] = ch;
  }

int getword(char* w, int lim) {
  int c, t;
  if(type(c = *w++ = getch()) != LETTER) {
    *w = '\0';
     //eat the chars between ""
     if (c == '"') {
        while ((c = getch()) != '"')
          if(c == EOF)
          return UNMATCHED_QUOTES;
      }
     return c;
    }
    while (--lim > 0) {
      t = type(c = *w++ = getch());
      if(t != LETTER && t != DIGIT) {
        ungetch(c);
        break;
      }
    }
  *(w-1) = '\0';
  return LETTER;
  }

