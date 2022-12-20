// operFunc.cpp - main file for function operating
#include"headFile.h"
#include"headOperFile.h"

bool createFile(Employee* employee, int n, FILE* file, const char* filename) {
	if (!checkFile(file, filename, "w")) return false;

	fwrite((char*)employee, sizeof(Employee), n, file); // write whole array of structure to file

	fclose(file); // close file
	return true;
}

bool printFile(FILE* file, const char* filename) {
	if (!checkFile(file, filename, "r")) return false;

	Employee employee; // variable to save, read from file, current structure 
	fread((char*)&employee, sizeof(Employee), 1, file); // read current type of structure from file 

	cout << "Введені співробітники: " << endl;
	while (!feof(file)) { // if not end of file
		printf("%s %s", employee.Name.surname, employee.Name.initials); // output data 
		printf("\t%c%d ", '+', employee.phoneNumber);
		puts("");
		fread((char*)&employee, sizeof(Employee), 1, file); // read next type of structure from file 
	}

	fclose(file); // close file
	return true;
}

bool findPerson(FILE* file, const char* filename, char* str1, char* str2) {
	if (!checkFile(file, filename, "r")) return false;

	Employee employee; // variable to save, read from file, current structure 
	fread((char*)&employee, sizeof(Employee), 1, file); // read current type of structure from file

	while (!feof(file)) { // if not end of file
		if ((strcmp(str1, employee.Name.surname) == 0) && (strcmp(str2, employee.Name.initials) == 0)) { // compare entered and saved names
			cout << "\nШуканий номер: +" << employee.phoneNumber << endl; // output searched number
			fclose(file); // close file
			return true;
		}
		fread((char*)&employee, sizeof(Employee), 1, file); // read next type of structure from file
	}

	cout << "\nШуканого співробітника не знайдено!" << endl;
	fclose(file); // close file

	return true;
}

bool checkNumber(Employee* employee, int n, int num) { // check for unicity entered phone number
	for (int i = 0; i < n; i++) {
		if (employee[i].phoneNumber == num) return false; 
	}
	return true;
}

int EnterNumber(const char* text) { // convert str to int
	cout << "\n" << text;
	char arr[BUFSIZ];
	gets_s(arr);
	return atoi(arr);
}

void FullName::EnterFullName() { 
	cout << "\nПрізвище:  "; gets_s(surname);
	cout << "\nІніціали:  "; gets_s(initials);
	while (strlen(surname) < 1 || strlen(initials) < 1 || strlen(initials) > 4) {
		cout << "\nКоректне прізвище:  "; gets_s(surname);
		cout << "\nКоректні ініціали:  "; gets_s(initials);
	}
	cout << endl;
}

void Employee::EnterEmployee(Employee* employee, const char* text, int n) {
	cout << "\n!--- Вводьте " << text << " ---!" << endl;

	int num = EnterNumber("Номер телефону: "); // enter phone number 
	while (num < 1 || (checkNumber(employee, n, num) == false)) {  // check whether number is unrepeatable
		num = EnterNumber("Коректний номер телефону: ");
	}

	phoneNumber = num; // save phone number in structure
	Name.EnterFullName(); // fill field of full name
}

void EnterArrayEmployees(Employee* employee, int n) { 
	for (int i = 0; i < n; i++) {
		employee[i].EnterEmployee(employee, "співробітника", n); // fill array of employees
	}
}