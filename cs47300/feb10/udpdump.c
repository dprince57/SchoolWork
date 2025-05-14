
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *fd;

  if(argc < 2){
    fprintf(stderr,"usage: %s [dump-file]\n",argv[0]);
    exit(0);
  }
}
