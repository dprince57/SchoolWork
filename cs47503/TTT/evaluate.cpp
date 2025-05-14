#include <iostream>
using namespace std;

int wtw[8][3] = {{0,1,2},
		 {3,4,5},
		 {6,7,8},
		 {0,3,6},
		 {1,4,7},
		 {2,5,8},
		 {0,4,8},
		 {2,4,6}};

int main()
{
  int bor[9];
  int i;
  int j;
  int k;
  k = 0;
    
  for(i = 0; i < 9; i++)
  {
    cin >> bor[i];
  }
  for(i = 0;i<7;i++)
  {
    k = 0;
    for(j = 0;j<2;j++)
    {
      if(bor[wtw[i][j]] == 1)
        k++;
    }
    if(k == 3)
      cout << "You Win!!!" << endl;
  }
  return 0;
}
