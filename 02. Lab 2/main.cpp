// Calculate 𝑆𝑛, for which the inequality |𝑆𝑛 − 𝑆𝑛−1|<𝜀, 𝜀=0.001 is fulfilled. Specify 𝑛 for which this inequality holds.
#define _USE_MATH_DEFINES // for using M_E
#include <cmath>
#include <iostream>
using namespace std;

int main() {
	double eps, x, fact = 2; // fact - factorial, which will be change in cycle
	long double SummPrev, Summ; // Summ at i=1,n; SummPrev at i=1,n-1;
	int n = 2;

	do {
		cout << "Enter eps > 0: "; cin >> eps;
	} while (eps < 0);

	cout << "Enter x: "; cin >> x;
	cout << endl;

	SummPrev = -x / M_E, Summ = pow(2 * x, 2) / (pow(M_E, 2) * 2) + SummPrev; // calculate Summ at i=1, and SummPrev at i=2
	//cout << "Summ: " << Summ;
	//cout << "\tSummPrev: " << SummPrev;
	//cout << "\t|Summ - SummPrev|: " << fabs(Summ-SummPrev) << endl;

	for (int i = 3; fabs(Summ - SummPrev) > eps; i++, n++) { // if condition |Summ - SummPrev| < eps completed, cycle will stop
		SummPrev = Summ; 
		fact *= i; // calculate factorial
		Summ += (pow(i*x, i) * pow(-1, i)) / (pow(M_E, i) * fact);
		//cout << "Summ: " << Summ;
		//cout << "\tSummPrev: " << SummPrev;
		//cout << "\t|Summ - SummPrev|: " << fabs(Summ - SummPrev) << endl;
	}
	cout << "n: " << n << endl;
	return 0;
}