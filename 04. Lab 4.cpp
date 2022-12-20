/*
Enter a string data of arbitrary length, which will be interpreted as text in which, 
words are separated by one or more spaces (word length, in general, arbitrary). 
Assuming that in the given text repetition of words is possible, 
output all words in a column without repetitions. 
In the second column, print the frequency of use of the corresponding word.
*/

#include <iostream>
#include <cstring>
#pragma warning (disable :4996)
using namespace std;

void Print_text(char** a, int n) { // text output
	for (int i = 0; i < n; i++)
		cout << *(a + i) << endl;
}

int check_line(char** a, int n, int* rc) { // search for repeated words
	int k = 0;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (stricmp(*(a + i), *(a + j)) == 0) { 
				k = j; // index of repeated element
				*(rc + i) += 1; // count of repeated word
				return k; 
			}
		}
	}
	return k;
}

char** Delete_line(char** a, int n, int k) { 
	int shift = 0; 
	char** c = new char* [--n];
	for (int i = 0; i < n; i++) {
		if (i == k) {
			shift = 1; // skip repeated word
		}
		c[i] = a[i + shift];
	}

	return c;
}

int main() {
	char data[BUFSIZ];
	const char* separator = " \t\n.,"; // initialization of separators between words
	char* word; // variable for word separation
	int k = 0; // will save index of repeated word

	cout << "Enter your text!\n";
	cin.getline(data, BUFSIZ - 1); 
	int n = strlen(data); 
	
	char* s1 = new char[n + 1]; // created dynamic array for separating and counting words

	strcpy(s1, data); 
	word = strtok(s1, separator);
	n = 0;
	for (int i = 0; word; i++) {
		word = strtok(NULL, separator);
		n++; // count of separated words
	}

	if (n == 0) { // if string is empty, it's no sense to move on
		cout << "\nString is empty!\n";
		delete[]s1;
		return 0;
	}

	char** s2 = new char* [n + 1]; // created dynamic array of pointers for save words from text line
	strcpy(s1, data);
	word = strtok(s1, separator);
	for (int i = 0; word; i++) {
		*(s2 + i) = word;
		word = strtok(NULL, separator);
	}

	int* rc = new int[n]; // created dynamic array for save count of repeated every word
	for (int i = 0; i < n; i++) *(rc + i) = 0; // initialization of every line in array for future word repeating count

	char** s3 = s2; // created dynamic array of pointers for words manipulating and outputting 
	k = check_line(s2, n, rc); // first search for repeating word

	while (k != 0) { // search and skip repeating words
		s3 = Delete_line(s3, n, k);
		n--;
		k = check_line(s3, n, rc);
	}

	cout << "\n*** String without repetitions ***\n";
	for (int i = 0; i < n; i++) {
		cout << *(s3 + i) << ": " << *(rc + i) << " repetitions." << endl;
	}
	delete[]s1;
	if (s3 != s2) delete[]s3; // if s3 stay as pointer on pointer, the dynamic memory not release 
	delete[]s2;
	delete[]rc;
	return 0;
}