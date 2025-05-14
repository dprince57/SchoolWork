#include <iostream>

using namespace std;

int main(){
  int i,j,k,x,y,f,d;
  int ws,lenS,coun;
  char a[120][120];
  char nM;
  cin >> k;
  
  for(i = 0;i<k;i++){
    coun = 1;
    for(f=0;i<120;i++){
      for(d=0;j<120;j++){
        a[f][d] = 'A';
      }
    }
    cin >> lenS;
    x = 60;
    y = 60;
    for(j=0;j<lenS;j++){
      cin >> nM;
      a[x][y] = nM;
      if(nM == 'N') y+=1;
      if(nM == 'S') y-=1;
      if(nM == 'E') x+=1;
      if(nM == 'W') x-=1;
    }
    x,y = 60;
    for(j=0;j<lenS;j++){
      if(a[x][y] == 'N'){ 
        cout << a[x][y] << endl;
	y+=1;
	coun++;}
      else if(a[x][y] == 'S'){ 
        cout << a[x][y] << endl;
	y-=1;
	coun++;}
      else if(a[x][y] == 'E'){ 
        cout << a[x][y] << endl;
        x+=1;
	coun++;}
      else if(a[x][y] == 'W'){
        cout << a[x][y] << endl;
	x-=1;
	coun++;}
    }
    cout << coun << endl;
  }
}
