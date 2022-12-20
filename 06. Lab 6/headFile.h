// headFile.h - main header file
#pragma once
#include <iostream>
#include <cstring>
#include <Windows.h>
#pragma warning (disable:4996)
using namespace std;

struct FullName { 
	char surname[BUFSIZ], initials[BUFSIZ];
	void EnterFullName();
};

struct Employee {
	FullName Name;
	int phoneNumber;
	void EnterEmployee(Employee*, const char*, int);
};

bool createFile(Employee*, int, FILE*, const char*); // create binary structure file 
bool printFile(FILE*, const char*); // output file content
bool findPerson(FILE*, const char*, char*, char*); // find and output employee
bool checkNumber(Employee*, int, int); // check for unicity entered phone number
int EnterNumber(const char*); 
void EnterArrayEmployees(Employee*, int); 