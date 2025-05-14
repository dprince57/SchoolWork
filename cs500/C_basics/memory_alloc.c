#include <stdio.h>
#include <stdlib.h>


char set_to_char(char A[], long int n, char x) {
  for(long int i=0; i < n; i++)
    A[i] = x;
}

char global_A[1 << 30]; 

int main(int argc, char *argv[]) {

  //set_to_char(global_A, 1 << 30, 'a');

  // this would be a seg fault
  //char local_A[1 << 30];
  //set_to_char(local_A, 1 << 30, 'a');

  char * heap_A = (char *) malloc(sizeof(char) * (1L << 50));
  if (heap_A == NULL) {
    printf("malloc failed.\n");
  }
  else {
    set_to_char(heap_A, 1L << 50, 'a');
  }
  return 0;
}
