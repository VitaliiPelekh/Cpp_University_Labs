//main.cpp
#include"headFile.h"
#include"headOperFile.h"

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	int n; 
	do {
		n = EnterNumber("Кількість співробітників: ");
	} while (n < 1);
	cout << endl;

	Employee* person = new Employee[n];

	const char* fileName = "fileEmployees.txt";
	FILE* file = 0; // initialization file variable

	EnterArrayEmployees(person, n); // fill array of employees

	if (n == 0) {
		puts("Array is empty");
		return 1;
	}

	if (!createFile(person, n, file , fileName)) { // create file and fill array of employees
		printf("Error\n");
		return 1;
	}
	
	if (!printFile(file, fileName)) { // output file content
		puts("Error");
		return 1;
	}

	char str1[BUFSIZ], str2[BUFSIZ]; // variables for surname and initials
	cout << "\n\n!--Вводьте шуканого співробітника--!\n";

	cout << "\nПрізвище:  "; gets_s(str1);
	cout << "\nІніціали:  "; gets_s(str2);
	while (strlen(str1) < 1 || strlen(str2) < 1 || strlen(str2) > 4) { // check for correct entered data
		cout << "\nКоректне прізвище:  "; gets_s(str1);
		cout << "\nКоректні ініціали:  "; gets_s(str2);
	}

	if (!findPerson(file, fileName, str1, str2)) { // find and output employee
		puts("Error");
		return 1;
	}

	delete[]person;
	cout << "\n\n!--- The end ---!\n" << endl;

	return 0;
}