#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char letters[5]; // an array of 5 char's
  printf("%d %d %d %d %d\n", letters[0], letters[1], letters[2], letters[3], letters[4]);
  
  // char is a letter, also an integer
  letters[0] = 'h';
  letters[1] = 'i';
  //letters[2] = ' ';
  //letters[3] = 32; // ASCII value for ' '
  //letters[4] = ' ';
  letters[2] = 'a';
  letters[3] = 'b';
  letters[4] = 'c';

  // "C string" is an array of characters
  // many functions will take a character array
  // as an argument/parameter and treat like text

  printf("%s\n", letters);

  // when does printf stop printing the string?
  // how does it know where the end is?
  //  it could be - stop at index 4, because that's how
  //  it was declared.
  //  that's not what happens. C = does the smallest
  //   amount possible, trust the programmer.
  // what does C do - looks for "magic"/special value
  //  to indicate the end of the string. Goes until
  //  it sees 0.

  // this is a buffer overflow, though probably doesn't
  //  crash
  letters[5] = 'x';
  letters[6] = 0;
  printf("%s\n", letters);

  // note: what printf("%s\n", letters) is doing...
  for(int i=0; letters[i] != 0; i++) {
    printf("%c", letters[i]) ;
  }
  printf("\n");

  return 0;
}
