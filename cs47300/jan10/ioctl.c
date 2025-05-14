
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define K 1024

int main() {
  int err, nbytes;
  char s[K];

  for(;;){
    printf("Hello.\n");
    usleep(500000);
    err = ioctl(0, FIONREAD, &nbytes);
    if(nbytes > 0){
      fgets(s,K,stdin);
      printf("%s\n", s);
    }
  }
}
