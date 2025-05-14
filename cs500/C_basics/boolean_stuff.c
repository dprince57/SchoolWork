#include <stdio.h>
#include <stdlib.h>

int do_something() {
  printf("Hello, did something, return'ing 1.\n");
  return 1;
}

int do_something_else() {
  printf("Did something else, return'ing 0.\n");
  return 0;
}

int main(int argc, char *argv[]) {

  if (do_something())
    printf("  It returned true.\n");
  else
    printf("  It returned FALSE.\n");

  if (do_something_else())
    printf("  It returned true.\n");
  else
    printf("  It returned FALSE.\n");

  printf("...\n");

  // short circuit evaluation of || 
  if (do_something() || do_something_else())
    printf("  It returned true.\n");
  else
    printf("  It returned FALSE.\n");

  printf("...\n");
  
  // short circuit evaluation of &&
  if (do_something() && do_something_else())
    printf("  It returned true.\n");
  else
    printf("  It returned FALSE.\n");

  printf("...\n");
  
  // short circuit evaluation of &&
  if (do_something_else() && do_something())
    printf("  It returned true.\n");
  else
    printf("  It returned FALSE.\n");

  // note: && and || are not actually commutative,
  //        in particular if you are calling functions
  //        with side effects.

  return 0;
}
