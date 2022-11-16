#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
using namespace std;

void insSort(int* xArr, int* yArr, size_t arrSize){
	size_t i = 1;
	size_t curr = 1;
	for(int i=1;i<arrSize;i++){ 
		for(int j=i; j>0; j--){
			if (xArr[j] < xArr[j-1]){
				swap(xArr[j-1],xArr[j]);  
			}
			else if (xArr[j] == xArr[j-1]){
				if (yArr[j] < yArr[j-1]){
					swap(xArr[j-1],xArr[j]);  
				}
				else{
					break;
				}
			}
			else{
				break;
			}
		}
	}
}

int main(int argc, char const *argv[]){
	size_t arrSize; 
	int n;
	int xMin, yMin, indexMin;

	cin >> arrSize;
	int* xArr = new int[arrSize];
	int* yArr = new int[arrSize];
	double* angleArr = new double[arrSize-1]


	for (int i = 0; i < arrSize; ++i){
		int x, y;
		if (x < xMin){
			xMin = x;
			yMin = y
			indexMin = i;
		}

		else if(x == xMin){
			if (y < yMin){
				xMin = x;
				yMin = y;
				indexMin = i;
			}
		}

		cin >> x >> y;
		xArr[i] = x;
		yArr[i] = y;
	}

	swap(xArr[indexMin], xArr[0]);
	swap(yArr[indexMin], yArr[0]);

	for (int i = 1; i < arrSize; ++i){
		angleArr = (xArr)
	}

	insSort(xArr, yArr, arrSize);

	minDot = xArr[i];
	for (int i = 0; i < ; ++i)
	{
		/* code */
	}

	for (int i = 0; i < arrSize; ++i){
		cout << xArr[i] << " " << yArr[i] << endl;
	}

	return 0;
}