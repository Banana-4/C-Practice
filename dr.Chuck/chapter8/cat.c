#include <fcntl.h> // open(), O_* flags
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // close(), read(), write()
#define BUFSIZE 512

enum ERROR_CODES {
  NO_ERROR,
  WRITE_FAIL,
  READ_FAIL,
};

void error(char *s1, char *s2);
enum ERROR_CODES copy(int fd);
int main(int argc, char *argv[]) {
  if (argc == 1) {
    switch (copy(0)) {
    case NO_ERROR:
      break;
    case READ_FAIL:
      error("Failed to read stdin.", "");
      break;
    case WRITE_FAIL:
      error("Faild to write to output.", "");
      break;
    }
  } else {
    while (argc > 1) {
      int fd = open(argv[argc - 1], O_RDONLY);
      if (fd == -1) {
        error("Can't open file %s.", argv[argc - 1]);
      }
      switch (copy(0)) {
      case NO_ERROR:
        break;
      case READ_FAIL:
        error("Failed to read file %s.", argv[argc - 1]);
        break;
      case WRITE_FAIL:
        error("Failed to write %s to output.", argv[argc - 1]);
        break;
      }
      close(fd);
      --argc;
    }
  }
  return 0;
}

void error(char *s1, char *s2) {
  fprintf(stderr, s1, s2);
  fprintf(stderr, "\n");
  exit(1);
}

enum ERROR_CODES copy(int fd) {
  int n = 0;
  char buf[BUFSIZE];
  while ((n = read(fd, buf, BUFSIZE)) > 0) {
    if (n == -1) {
      return READ_FAIL;
    }
    if (write(1, buf, n) != n) {
      return WRITE_FAIL;
    }
  }
  return 0;
}
