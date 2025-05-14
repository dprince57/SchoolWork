#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int allNum = 1, number = 0, all_ok = 1, inOrder = 1;
  int *array_rows = (int *)malloc(argc-1 * sizeof(int));

  if(array_rows == NULL){fprintf(stderr, "Malloc failed\n");return 1;}

  for(int i=1; i < argc; i++) {
    if(sscanf(argv[i], "%d", &number) != 1){
      allNum = 0;
    }else{
      array_rows[i-1] = atoi(argv[i]);
    }
  }
  //if only numbers are found
  if(allNum){
    for(int i = 1; i < argc-2; i++){
      if(array_rows[i] > array_rows[i+1]){
        printf("Not in numeric order, %d should be after %d.\n",array_rows[i], array_rows[i+1]);
        inOrder = 0;
      }
    }
    if(inOrder)printf("In Numerical order\n");
  }
  //if a word is found
  if(!allNum){
    for(int i=2; i < argc; i++) {
      // check if argv[i] is after argv[i-1]
      if (strcmp(argv[i], argv[i-1]) < 0) {
        printf(" Not alphabetical in order, %s should be after %s.\n",
	       argv[i-1], argv[i]);
        all_ok = 0;
      }
    }
    if (all_ok) printf("In alphabetical order\n");
  }
  free(array_rows);
  return 0;
}
