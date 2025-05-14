/* Dakota Prince */

#include <iostream>

using namespace std;

int main()
{
  int i,k,j,temp;
  i = 1;
  k = 1;
  while(1)
  {
    cin >> i >> k;
    if(i == 0 && k == 0){break;}
    cout << i/k <<" " << i%k << " / " << k << endl;
  }
  return 0;
}
