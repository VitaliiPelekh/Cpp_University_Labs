// headFile.h
#pragma once
#include<iostream>
#include<cstring>
#include<Windows.h>

#pragma warning(disable:4996)

using namespace std;
const int sizePos = BUFSIZ; // size of string

struct Positions {
	char startPos[sizePos], finalPos[sizePos]; // variables of start and final cities of route
	void EnterPos(); // enter city
	void PrintPos(); // output city
};

struct MARSHRUT {
	struct Positions points; // field cities in route
	int numberPos; // number of route
	void EnterMarshrut(MARSHRUT*, const char*, int); // enter route
	void PrintMarshrut(); // output route
};

int EnterNumber(const char*); // enter number
bool checkNumber(MARSHRUT*, int, int); // check if number of route don't exist yet
void EnterArrayMarshruts(MARSHRUT*, int); // enter array of routes
void SortArrayMarshruts(MARSHRUT*, int, const char*); // sort array of routes
void PrintArrayMarshruts(MARSHRUT*, int, const char*); // output array of routes
void FindNumberMarshruts(MARSHRUT*, int, int); // find number of route in array
void FindPointMarshruts(MARSHRUT*, int, char*); // find city in array of routes