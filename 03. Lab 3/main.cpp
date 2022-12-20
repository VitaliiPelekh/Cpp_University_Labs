//In the square matrix sort the columns in ascending order of the sums of their elements

#include <iostream>
#include <stdlib.h> // implement srand
#include <time.h> // manipulation with data and time
using namespace std;

int sum(int* arr, int n) { // separate sum of rows function
	int s = 0;
	for (int i = 0; i < n; i++) {
		s += *(arr + i); // sum of rows of transposed matrix
	}
	return s;
}

void outputMtrx(int** arr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout.width(5);
			cout << *(*(arr + j) + i);
		}
		cout << endl;
	}
}

int main() {
	int size; //  initialization size of square matrix
	
	do {
		cout << "Enter size of square matrix (size > 0):\t"; cin >> size;
	} while (size < 1);
	cout << endl;

	int** arr = new int* [size]; // dynamical array of pointers
	for (int i = 0; i < size; i++) {
		arr[i] = new int[size];
	}

	srand(unsigned(time(0)));

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int c = 10, d = 100;
			arr[j][i] = rand() % (d - c); // fill square matrix by random numbers
		}
	}

	cout << "\t---Generated matrix---\n\n";
	outputMtrx(arr, size);

	// Neumann sorting method
	int k = size;
	bool flag = true;
	while (flag && k > 1) {
		flag = false; k--;
		int s1 = sum(*arr, size); // suma of first row
		for (int i = 1; i <= k; i++) {
			int s2 = sum(*(arr + i), size); // suma of next row
			if (s1 > s2) {
				int* ptr1 = *(arr + i - 1);
				*(arr + i - 1) = *(arr + i); // rows exchange
				*(arr + i) = ptr1;
				flag = true; // change flag to True
			}
			else s1 = s2;
		}
	}

	cout << "\n\t---Sorted matrix---\n\n";
	outputMtrx(arr, size);

	for (int i = 0; i < size; i++) {
		delete[]arr[i];
	}
	delete[] arr;

	return 0;
}