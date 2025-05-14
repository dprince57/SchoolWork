#define K 16
#define FILENAME "data"

// following used for file stuff
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// following used for exit stuff
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

int main() {
  char data[K];
  int n, fd;

  fd = open(FILENAME, O_RDONLY);
  if(fd < 0)
    exit(0);
  for(;;){
    n = read(fd, data, K);
    if(n > 0)
      write(1, data, n);
    else
      break;
  }
  close(fd);
}
