#include <stdio.h>
#include <stdlib.h>

int main() {
  int A[100];

  // how many numbers in the subset
  printf("How many numbers in the subset? ");
  int n;
  scanf("%i",&n);

  if (n > 30) {
    printf("No, it will take too long.\n");
    return 0;
  }

  // get the target valyue
  printf("What is the target value? ");
  int target;
  scanf("%i",&target);


  // read in the numbers
  int i;
  printf("Type the numbers, one after another, space in between, then enter.\n");
  for(i=0;i<n;i++)
    scanf("%i",&(A[i]));



  unsigned long int x;
  int maxVal = 1 << n;
  int solved=0;

  for(x = 0; x < maxVal; x++) {
    int total = 0;

    int index;
    int b;
    for(index=n-1;index>=0;index--) {
      b = (x & (1 << index)) >> index;
      if (b == 1) {
	total += A[index];
      }
      //printf("%i", b);
    }
    //printf(" %i\n", total);

    if (total == target) {
      printf("Solved!  As follows...\n");
      for(index=n-1;index>=0;index--) {
	b = (x & (1 << index)) >> index;
	if (b == 1) {
	  printf("%i ", A[index]);
	}
      }
      printf("\n");
      solved=1;
      break;
    }
  }

  if (solved == 0) printf("No solution.\n");

  return 0;
}
