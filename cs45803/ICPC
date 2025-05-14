/* Dakota Prince */

#include <iostream>

using namespace std;

int main()
{
  int nline;
  int lines;
  int num;
  int lnum;
  int i;
  
  cin >> lines;

/* For loop to gather data and to compute the values */

  for(i = 0;i < lines; i++)
  {
    cin >> nline >> num;

    lnum = num;

/*while loop to do the math for us */

    while(num > 1)
    {
      if(num % 2 == 0)
        num = num / 2;
      else
        num = (num * 3) + 1;
      if(num > lnum)
        lnum = num;
    }
    cout << nline << " " << lnum << endl;
  }
  return 0;
} 

