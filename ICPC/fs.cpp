
#include <iostream>

using namespace std;

int main()
{
  int i,k,g,d,temp;
  int W,P;
  int ndiv;
  cin >> W >> P;
  int pLoc[P],pLen[W];
  for(i=0;i<W;i++)
  {
    pLen[i] = 0;
  }
  for(i = 0;i < P;i++)
  {
    cin >> pLoc[i];
  }
  for(i = 0;i<P;i++)
  {
    d = pLoc[i] - 0;
    pLen[d] = d;
    k = i + 1;
    if(k >= P){
      k = P;
    }
    for(k;k<P;k++)
    {
      d = pLoc[k] - pLoc[i];
      pLen[d] = d;
    }

    d = W - pLoc[i];
    pLen[d] = d;
  }
  for(i = 1;i<W;i++)
  {
    if(pLen[i] != 0){
      cout << pLen[i] << " ";
    }
  }
  cout << W;
  return 0;
}

