/*
Write a program for generating words that can be obtained 
by permutations of the first four letters of a given word. 
The input word is entered from the keyboard, 
and the letters in the word may be repeated.
*/

#include <iostream>
#include <string>
#include <algorithm>

#pragma warning (disable :4996)
using namespace std;

void display(char a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << "  ";
    }
}

// Function to find the permutations
void findPermutations(char a[], int n, string str, string strEnd) {
    int k = 0;
    
    cout << "Possible permutations for word {" << str << "} are:\n";

    // Sort the given array
    sort(a, a + n);

    // Find all possible permutations
    do {
        display(a, n);
        cout << strEnd << endl;
        k++;
    } while (next_permutation(a, a + n));

    cout << endl << "Count of all permutations is: " << k << endl;
}

int main() {
    char data[5];
    string str, str1, str2;

    cout << "Enter word: ";
    getline(cin, str, '\n');

    if (str.size() < 4) {
        cout << "Entered word hasn't enough length!" << endl;
        return 0;
    }
    else {
        for (int i = 0; i < str.size(); i++) 
            if (!(isalpha(str[i]))) {
                cout << "Entered word not contain latina!" << endl;
                return 0;
            }
    }

    str1 = string(str, 0, 4);
    str2 = string(str, 4, str.size());

    for (int i = 0; i < str1.size(); i++) {
        data[i] = str[i];
    }

    findPermutations(data, 4, str1, str2);
    return 0;
}