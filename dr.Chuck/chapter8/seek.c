#include <stdio.h>
#include <unistd.h>

#define BLOCKSIZE 512
#define MAX_INT 65535
void my_seek(int fd, int offset, int origin) {
  if (fd < 0) {
    fprintf(stderr, "Invalid file descriptor.\n");
    return;
  }
  if (origin < 0 || origin > 5) {
    fprintf(stderr, "The value %d is not a valid origin position.\n", origin);
    return;
  }
  long _offset = offset;
  if (origin > 2 && origin <= 5) {
    _offset *= BLOCKSIZE;
    origin -= 3;
  }

  lseek(fd, _offset, origin);
}

void my_lseek(int fd, long offset, int origin) {
  if (fd < 0) {
    fprintf(stderr, "Invalid file descriptor.\n");
    return;
  }
  if (origin < 0 || origin > 2) {
    fprintf(stderr, "The value %d is not a valid origin position.\n", origin);
    return;
  }

  if (offset > MAX_INT) {
    int block = 0;
    long _offset = offset;
    while (_offset > MAX_INT) {
      _offset /= BLOCKSIZE;
      ++block;
    }
    offset = offset / (block * BLOCKSIZE) + offset % (block * BLOCKSIZE);
    seek(fd, block, origin + 3);
    origin = 1;
  }

  seek(fd, (int)offset, origin);
}
