#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  /*

  counts down from commandline given number or starts from 10 if
  no number given in one loop. No real error checking as I am still reading the man page for strtol
  */
  long conv = 0;
  //if we have an argument in the commandline convert it to a long
  if(argc != 1){
    conv = strtol(argv[1],NULL,10);
  }
  //this is my super cool error checker. if you used a string and not number we use 10 as a default
  if(conv == 0)conv = 10;

  //for loop to coun to 1 then back up
  for(int i = 0;i <= conv+15;i++){
    if(i < conv-1){printf("%ld\n",conv - i);}
    else{printf("%ld\n",i - (conv-2));}
  }

  printf("We have reached our cruising altitude!!\n");


  return 0;
}
