/*
Theory of grammars and formal languages.

Grammar generates a sequence of relations of form:
	<variable> <relation operation> <number>

where:
	<variable> consists of letters and has an arbitrary length,
	<relationship operation>: <<=>> = <> =
	<number> - an integer without a sign of arbitrary length.

The relations are separated from each other by commas, 
the comma cannot be after the last in the sequence of relations.
*/

#include <iostream>
#include <regex>
#include <string>
#pragma warning( disable:4996);

using namespace std;

bool Isrelation(char* str) { // перевірка на правильно введене відношення
	bool flag = false;

	regex isrelation(R"(([A-Z]|[a-z])+(<>|<=|>=|>|<|=)(-[0-9]|[0-9])*)");
	if (regex_match(str, isrelation)) flag = true;

	return flag;
}

int main() {
	char data[BUFSIZ];
	const char* separator = ",";
	char* word;

	cout << "Enter your text!\n";
	cin.getline(data, BUFSIZ - 1);
	int n = strlen(data);

	if (data[n - 1] == ',') { // перевірка умови, чи вкінці послідовності відношень стоїть кома
		cout << "ERROR: separator ',' is defined at the end!!!" << endl;
		return 0;
	}

	if (!isdigit(data[n - 1]) && !isdigit(data[n - 2])) { // додаткова перевірка граматики, чи вкінці відношення задане як мінімум одне число
		cout << "\nGrammar isn't correct!";
		return 0;
	}

	bool flag = false; //прапорець для перевірки граматики
	word = strtok(data, separator);
	while (word) { // перевірка заданої послідовності відношень
		if (Isrelation(word)) flag = true;
		else flag = false;
		word = strtok(NULL, separator);
	}

	if (flag) cout << "\nGrammar is correct!";
	else cout << "\nGrammar isn't correct!";

	return 0;
}