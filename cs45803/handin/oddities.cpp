#include <iostream>

using namespace std;

int main(){
  int i,j,k;
  
  cin >> i;
  
  for(j;j<i;j++){
    cin >> k;
    if(k%2 != 0){
      cout << k << " is odd" << endl;
    }else{
      cout << k << " is even" << endl;
    }
  }
}
