/*
Determine the largest and smallest values of the function in the tabulation interval, 
as well as the corresponding values of the arguments.
The function is: ( tg(x) + ctg(1-x^2) )
*/

#define _USE_MATH_DEFINES // for using M_PI
#include <iostream>
#include <cmath>
#include <iomanip> // manipulation with in/out
using namespace std;

double func(double z) { // I separeted my function for code optimization
    return tan(z) + 1 / tan(1 - pow(z, 2)); // function: ctg x = 1 / tg x 
}

double verificationFunc(double a, double b) { // verification algorithm, which contain three conditions of discontinuity and compare periods n of my function at [a,b]
    double xa = a, xb = b; // start value for x
    double na1 = xa / M_PI - (double)1 / 2; // formula from the first condition of discontinuity at x = a
    //cout << "na1: " << na1 << endl;
    //cout << "na1: " << round(na1) << endl;
    double nb1 = xb / M_PI - (double)1 / 2; // formula from the first condition of discontinuity at x = b
    //cout << "nb1: " << nb1 << endl;
    //cout << "nb1: " << round(nb1) << endl;

    return !(round(na1) == round(nb1)); // comparing periods n of my function at [a,b] from the first condition of discontinuity and detecting break points of my function

    xa = a, xb = b; // update value to calculate x from the second condition of discontinuity
    double na2 = (pow(xa, 2) + 1) / M_PI;
    //cout << "na2: " << na2 << endl;
    //cout << "na2: " << round(na2) << endl;
    double nb2 = (pow(xb, 2) + 1) / M_PI;
    //cout << "nb2: " << nb2 << endl;
    //cout << "nb2: " << round(nb2) << endl;

    return !(na2 <= 0 && nb2 <= 0 && round(na2) == round(nb2)); // do the same as at na1 and nb1, but in the second condition in the formula must be n <= 0 

    xa = a, xb = b; // update value again
    double na3 = -((pow(xa, 2) - 1) / M_PI);
    //cout << "na3: " << na3 << endl;
    //cout << "na3: " << round(na3) << endl;
    double nb3 = -((pow(xb, 2) - 1) / M_PI);
    //cout << "nb3: " << nb3 << endl;
    //cout << "nb3: " << round(nb3) << endl;

    return !(na3 <= 0 && nb3 <= 0 && round(na3) == round(nb3));
}

void coutFunc(double x, double func) {
    cout << "|" << setw(10) << x << setw(10) << "|" << setw(10) << func << setw(10) << "|" << endl; // output x and output value of function at the point x
}

int main() {
    int n;
    long double a, b, x, h, maxF, minF, maxI, minI, maxX, minX;

    do {
        cout << "\nEnter n > 1\nn = ";
        cin >> n;
    } while (n <= 1);

    do {
        cout << "\nEnter [a;b]\na = ";
        cin >> a;
        cout << "\nb = ";
        cin >> b;
    } while (a == b); // if a == b, this cycle will send a request again

    if (verificationFunc(a, b) == false) { // verification, if this interval has any break points this cycle will send a request again
        do {
            cout << "\nEnter [a;b]\na = ";
            cin >> a;
            cout << "\nb = ";
            cin >> b;
        } while (verificationFunc(a, b) == false); 
    }

    if (a > b) { // if a > b, this algorithm will change a and b
        double g = a; a = b; b = g;
    }

    cout << "-----------------------------------------\n";
    cout << "|" << setw(10) << "x" << setw(10) << "|" << setw(10) << "f(x)" << setw(10) << "|" << endl; // head of output table
    cout << "-----------------------------------------\n";

    x = a; // start value for x
    h = (b - a) / ((double)n - 1); // formula of computing step h
    maxF = minF = func(x), maxI = minI = 0, maxX = minX = x; // start value for min and max
    coutFunc(x, func(x)); // the first output at x = a

    for (int i = 1; i < n; i++) {
        x = a + i * h; // incremention of x
        if (maxF < func(x)) { // calculation of max
            maxF = func(x);
            maxI = i;
            maxX = x;
        }
        if (minF > func(x)) { // calculation of min
            minF = func(x);
            minI = i;
            minX = x;
        }
        coutFunc(x, func(x));
    }

    // version with "while" cycle
    /*int i = 1;
    while (i < n) {
       x = a + i * h; // incremention of x
        if (maxF < func(x)) { // calculation of max
            maxF = func(x);
            maxI = i;
            maxX = x;
        }
        if (minF > func(x)) { // calculation of min
            minF = func(x);
            minI = i;
            minX = x;
        }
        coutFunc(x, func(x));
        i++;
    }*/

    // another version with "do while" cycle
    /*int i = 1;
    do{
       x = a + i * h; // incremention of x
        if (maxF < func(x)) { // calculation of max
            maxF = func(x);
            maxI = i;
            maxX = x;
        }
        if (minF > func(x)) { // calculation of min
            minF = func(x);
            minI = i;
            minX = x;
        }
        coutFunc(x, func(x));
        i++;
    }while (i < n);*/

    // output max, min and their arguments
    cout << "-----------------------------------------\n";
    cout << "Min f(x): " << minF << endl;
    cout << "Iteration: " << minI << endl;
    cout << "Argument x: " << minX << endl;
    cout << "-----------------------------------------\n";
    cout << "Max f(x): " << maxF << endl;
    cout << "Iteration: " << maxI << endl;
    cout << "Argument x: " << maxX << endl;
    cout << "-----------------------------------------\n";
    return 0;
}