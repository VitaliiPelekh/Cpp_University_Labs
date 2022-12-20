// operFunc.cpp - file with functions
#include"headFile.h"

bool checkNumber(MARSHRUT* arrPos, int n, int num) { // check if number of route don't exist yet
	for (int i = 0; i < n; i++) {
		if (arrPos[i].numberPos == num) return false;
	}
	return true;
}

int EnterNumber(const char* text) { // convert str to int
	cout << "\n" << text;
	char arr[20];
	gets_s(arr);
	return atoi(arr);
}

void Positions::EnterPos() { // enter cities
	cout << "\nПункт відправлення: "; gets_s(startPos);
	cout << "\nПункт призначення: "; gets_s(finalPos);
	cout << endl;
}

void Positions::PrintPos() { // output cities
	cout << startPos << " - " << finalPos << endl;
}

void MARSHRUT::EnterMarshrut(MARSHRUT* arrPos, const char* text, int n) { // enter route
	cout << "\n!--- Вводьте " << text << " ---!" << endl;

	int num = EnterNumber("Номер маршруту: "); // enter number 
	while (num < 1 || checkNumber(arrPos, n, num) == false) {  // check whether number is correct
		num = EnterNumber("Коректний номер маршруту: ");
	}

	numberPos = num;
	points.EnterPos(); // fill field of cities
}

void MARSHRUT::PrintMarshrut() { // output route
	cout << numberPos << ". ";
	points.PrintPos(); // output field of cities
}

void EnterArrayMarshruts(MARSHRUT* arrPos, int n) { // enter array of routes
	for (int i = 0; i < n; i++) {
		arrPos[i].EnterMarshrut(arrPos, "маршрут", n); 
	}
}

void PrintArrayMarshruts(MARSHRUT* arrPos, int n, const char* text) { // output array of routes
	cout << "\n" << text << endl;
	for (int i = 0; i < n; i++) {
		cout << endl;
		arrPos[i].PrintMarshrut();
	}
}

void SortArrayMarshruts(MARSHRUT* arrPos, int n, const char* text) { // sort array of routes
	// Neumann sorting method
	int k = n;
	bool flag = true;
	while (flag && k > 1) {
		flag = false; k--;
		for (int i = 0; i < k; i++) {
			if (arrPos[i].numberPos > arrPos[i+1].numberPos) {
				MARSHRUT exchangePos = arrPos[i];
				arrPos[i] = arrPos[i+1];
				arrPos[i + 1] = exchangePos;
				flag = true; // change flag to True
			}
		}
	}
	PrintArrayMarshruts(arrPos, n, text); // output sorted array of routes
}

void FindNumberMarshruts(MARSHRUT* arrPos, int n, int g) { // find number of route in array
	cout << endl;
	bool flag = false; // variable that check whether number was found
	for (int i = 0; i < n; i++) {
		if (g == arrPos[i].numberPos) { // check every number in array of routes
			arrPos[i].PrintMarshrut(); 
			flag = true; // number was found
		}
	}
	if (flag == false) {
		cout << "Маршрут під таким номером не існує!" << endl;
	}
}

void FindPointMarshruts(MARSHRUT* arrPos, int n, char* str) { // find city in array of routes
	cout << endl;
	bool flag = false; // variable that check whether number was found
	for (int i = 0; i < n; i++) {
		if (strcmp(str, arrPos[i].points.startPos) == 0 || strcmp(str, arrPos[i].points.finalPos) == 0) {
			arrPos[i].PrintMarshrut();
			flag = true; // city was found
		}
	}
	if (flag == false) {
		cout << "Не знайдено шуканого міста у маршрутах!" << endl;
	}
}