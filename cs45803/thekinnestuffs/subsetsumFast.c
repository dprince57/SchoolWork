#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Note: more testing, debugging needed...\n");

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
  int total=0;
  printf("Type the numbers, one after another, space in between, then enter.\n");
  for(i=0;i<n;i++) {
    scanf("%i",&(A[i]));
    total += A[i];
  }

  // note: assuming fewer than 1000 numbers, and total < 1000
  // table[row][col]
  // table[0][...] represents adding up to 0
  int table[1000][1000];

  // initially, we assume we can't do anything.
  int sum, index;
  for(sum=0; sum <= total; sum++)
    for(index=0; index <= n; index++)
      table[sum][index] = 0;

  // but we can do a sum of 0 by including nothing
  table[0][0] = 1;

  for(index=1; index <= n; index++) {
    // what if we now can use A[index], what new sum's can we get
    for(sum=0; sum <= total; sum++) {
      // can we add up to sum?
      // table[sum][index]?

      if (table[sum][index-1] == 1) // already could add up to sum before
	table[sum][index] = 1; //      still can

      if (table[sum-A[index-1]][index-1] == 1)
	table[sum][index] = 1;
    }
  }

  // look at row "target", last column, see if we can do that
  if (table[target][n] == 1) {
    printf("Yes, we can hit that target.\n");
    sum = target;
    for(index=n; index > 0; index--) {
      if (table[sum][index-1] == 0) {
	printf("%i ", A[index-1]);
	sum -= A[index-1];
      }
    }
    printf("\n");
  }
  else
    printf("No solution.\n");

  return 0;
}
