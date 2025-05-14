// lab8 - nothing to do for this, but code like this may be helpful for
//  one of the other programs, so I am leaving the file here in the
//  lab8 directory

#include <stdio.h>
#include <stdlib.h>

int compare_int (const void * a, const void * b) {
  int *left = (int *) a;
  int *right = (int *) b;
  return (*left - *right);
}

int main(int argc, char *argv[]) {
  /*
    ./sorting.o how_many n
      how_many - # of random integers to create and sort
      n - how many to print
  */
  if (argc < 3) {
    printf("Usage: ./sorting.o how_many n\n"
	   "  how_many - # of random integers to create and sort\n"
	   "  n - how many to print\n");
    exit(0);
  }

  int how_many = atoi(argv[1]);
  int n = atoi(argv[2]);

  int *nums = (int *) malloc(sizeof(int) * how_many);
  for(int i=0; i < how_many; i++) {
    nums[i] = rand();
  }

  qsort (nums, how_many, sizeof(int), compare_int);

  for(int i=0; i < n && i < how_many; i++) {
    printf("%d\n", nums[i]);
  }

  free(nums);

  return 0;
}


/*
  person_t {
   char *name;
   float age;
  }

  person_t ** people = (person_t **) malloc(sizeof(person_t *) * 1000);
  people[i] = new_person(); // returns person_t *

  qsort(people, 1000, sizeof(person_t *), compare_person_t_star)

int compare_person_t_star (const void * a, const void * b) {
  person_t *left = *((person_t **) a);
  person_t *right = *((person_t **) b);

  // put them in order by age
  return (left->age - right->age);

  // put them in order by age
  return (strcmp(left->name, right->name));
}
*/
