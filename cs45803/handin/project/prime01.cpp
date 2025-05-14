#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

int main(){
	long int n;
	long int x,i,j,a,k;
	
	srand(time(NULL));

	cout << "Enter a number for Prime Testing " << endl;
	cin >> n;

	//WARNING: Using a number as bigger than the prime will cause it to take longer than expected!
	cout << "Enter number for times to be repeated" << endl;
	cin>> k;

	//For Loop for the Fermat Function
	for(i=0;i<k;i++){
		//Picking a random number(1 =< a < n)
		a = (rand() % (n-1)) + 1;
	 	j = 0;
		x = 1;
		//While loop for Modular Exponentiation
		while(j<n-1){
			x=x*a;
			x=x%n;
			j++;
		}
		if(x!=1){
			cout << "The Number entered is not a prime!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	cout << "The Number you have choosen is most likely Prime! Congrats!" << endl;
	return 0;
}
