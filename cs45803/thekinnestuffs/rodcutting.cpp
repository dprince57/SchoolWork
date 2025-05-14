#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 4) {
    cout << "Usage: ./rodcutting dynamic|greedy n randSeed" << endl;
    return 0;
  }

  string which = argv[1];
  if (which != "dynamic" && which != "greedy") {
    cout << " Error: specify dynamic or greedy only." << endl;
    return 0;
  }

  int n = atoi(argv[2]);

  srand(atoi(argv[3]));

  int p[n];
  for(int i=0;i<n;i++)
    p[i] = (rand() % 100) * (i+1);

  if (which == "greedy") {
    // put greedy algorithm here.  when done, output just the 
    // optimal value.
  }
  else {
    // put the dynamic programming algorithm here.  when done, output
    // just the optimal value.
  }

  return 0;
}
