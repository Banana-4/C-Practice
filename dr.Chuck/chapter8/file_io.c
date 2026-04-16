
#include <stdlib.h>
#define _BUFFSIZE 512
#define _NFILES 20

typedef struct {
  char *_bp;
  char *_base;
  int _cnt;
  struct {
    unsigned int _READ : 1;
    unsigned int _WRITE : 1;
    unsigned int _EOF : 1;
    unsigned int _ERR : 1;
    unsigned int _UNBUF : 1;
    unsigned int _BIGBUF : 1;
  } _flag;

  int _fd;
} FILE;

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

// #define _READ 01
// #define _WRITE 02
// #define _UNBUF 04
// #define _BIGBUF 010
// #define _EOF 020
// #define _ERR 040
#define NULL 0
#define EOF (-1)

FILE _iob[_NFILES] = {
    {NULL, NULL, 0, {1, 0, 0, 0, 0, 0}, 0},
    {NULL, NULL, 0, {0, 1, 0, 0, 0, 0}, 1},
    {NULL, NULL, 0, {0, 1, 0, 0, 1, 0}, 2},
};

int _fillbuf(FILE *f);
int _flushbuf(FILE *f, int c);
inline int getc(FILE *f) {
  return (--f->_cnt >= 0 ? *(f->_bp++) : _fillbuf(f));
}
inline int getchar() { return getc(stdin); }

inline void putc(FILE *f, char c) {
  --f->_cnt >= 0 ? *(f->_bp++) = c : _flushbuf(f, c);
}
inline void putchar(int c) { putc(stdout, c); }

#define PMODE 0644

FILE *fopen(const char *name, const char *mode) {
  if (mode != "r" || mode != "w" || mode != "a") {
    fprintf(stderr, "Illegal mode %s opening %s\n", mode, name);
    exit(1);
  }
  FILE *fp;
  int fd;
  for (fp = _iob; fp < _iob + _NFILES; ++fp) {
    if (!fp->_flag._READ && !fp->_flag._WRITE)
      break;
  }
  if (fp >= _iob + _NFILES) {
    return NULL;
  }
  switch (*mode) {
  case 'w':
    fd = create(name, PMODE);
    break;
  case 'a':
    if (fd = open(name, 1) == -1)
      fd = create(name, PMODE);
    lseek(fd, 0L, 2);
    break;
  case 'r':
    fd = open(name, 0);
    if (fd == -1)
      return NULL;
    break;
  }
  fp->_fd = fd;
  fp->_cnt = 0;
  fp->_base = NULL;
  fp->_flag = (typeof(fp->_flag)){0};
  if (*mode == 'r') {
    fp->_flag._READ = 1;
  } else {
    fp->_flag._WRITE = 1;
  }
  return (fp);
}
int _fillbuf(FILE *fp) {
  static char smallbuf[_NFILES];

  if (!fp->_flag._READ || fp->_flag._EOF || fp->_flag._ERR)
    return EOF;
  while (fp->_base == NULL) /* find buffer space */
    if (fp->_flag._UNBUF)   /* unbuffered */
      fp->_base = &smallbuf[fp->_fd];
    else if ((fp->_base = calloc(_BUFFSIZE, 1)) == NULL)
      fp->_flag._UNBUF = 1; /* can't get big buf */
    else
      fp->_flag._BIGBUF = 1; /* got big one */
  fp->_bp = fp->_base;
  fp->_cnt = read(fp->_fd, fp->_bp, fp->_flag._UNBUF ? 1 : _BUFFSIZE);
  if (--fp->_cnt < 0) {
    if (fp->_cnt == -1)
      fp->_flag._EOF = 1;
    else
      fp->_flag._ERR = 1;
    fp->_cnt = 0;
    return (EOF);
  }
  return (*fp->_bp++);
}

int _flushbuf(FILE *fp, int c) {

  static char smallbuf[_NFILES];
  if (!fp->_flag._WRITE || fp->_flag._ERR)
    return EOF; // not ideal but it does say nothing more can be writen to the
                // file

  // write data to file
  int amount = fp->_bp - fp->_base;
  if (write(fp->_fd, fp->_base, amount) != amount) {
    fp->_flag._ERR = 1;
    return EOF;
  }

  while (fp->_base == NULL) {
    if (fp->_flag._UNBUF)
      fp->_base = &smallbuf[fp->_fd];
    else if ((fp->_base = calloc(_BUFFSIZE, 1)) == NULL) {
      fp->_flag._UNBUF = 1;
      fp->_cnt = 1;
    } else {
      fp->_flag._BIGBUF = 1;
      fp->_cnt = _BUFFSIZE;
    }
  }
  fp->_bp = fp->_base;
  *fp->_bp++ = c;
  --fp->_cnt;
  return c;
}

void fclose(FILE *fp) {
  if (fp->_flag._WRITE) {
    _flushbuf(fp, '\0');
  }
  if (fp->_flag._BIGBUF)
    free(fp->_base);
  fp->_base = NULL;
  fp->_bp = NULL;
  fp->_cnt = 0;
  fp->_flag._READ = 0;
  fp->_flag._BIGBUF = 0;
  fp->_flag._EOF = 0;
  fp->_flag._ERR = 0;
  fp->_flag._UNBUF = 0;
  fp->_flag._WRITE = 0;
  close(fp->_fd);
}

void fseek(FILE *fp, long offset, int origin) {
  if (fp->_flag._WRITE) {
    if (write(fp->_fd, fp->_base, fp->_bp - fp->_base) != fp->_bp - fp->_base) {
      fp->_flag._ERR = 1;
      return;
    }
  }

  if (fp->_flag._READ && origin == 1) {
    offset -= fp->_cnt;
  }
  lseek(fp->_fd, offset, origin);
  fp->_cnt = 0;
  fp->_bp = fp->_base;
}
