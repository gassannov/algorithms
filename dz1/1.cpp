#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//1.3

int one_three(unsigned N){
	size_t ones = 0;
	while(N > 0){
		if (N & 1)
		{
			ones ++;
		}
		N = N >> 1;
	}
	if (ones != 1){
		//cout << "FAIL" << endl;
		return 0;
	}
	else{
		//cout << "OK" << endl;
		return 1;
	}
}



int main(int argc, char const *argv[])
{	
	unsigned number =  0;
	cin >> number;
	if(one_three(number)){
	    cout << "OK" << endl;
	}
	else {
	    cout << "FAIL" << endl;
	}
	return 0;
}