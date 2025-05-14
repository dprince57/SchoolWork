#include <iostream>
#include <math.h>

using namespace std;

int main(){
  int n;

  n = 150780; 
  char c;
 
  c = "This is RSA";

  cout << c << endl;

  c = (c^17)%n;
  
  cout << c << endl;
  
  return 0;
}
