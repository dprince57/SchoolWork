#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define K 1024

int main(int argc, char *argv[]) {
  if(argc < 2) {
    fprintf(stderr, "usage: %s dumpfile\n", argv[0]);
    exit(0);
  }
  FILE *fd;
  char yep[1024];

  fd = fopen(argv[1], "r");
  if(!fd){
    fprintf(stderr, "cannot open file %s\n", argv[1]);
    exit(0);
  }
  read(fd, yep, K);
  printf("%14x\n", yep);

}
