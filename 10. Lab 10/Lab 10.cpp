//Determine whether the given function is monotonic.

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

bool isMonotone(const vector<bool>& vec, int n) {
	int shift = vec.size(); // ����� ��� ������� ��������� � ����, ��� ��������� ���� ����������� ������
	
	while ((shift /= 2) > 0) { // ����� ������� �� �������� "�������",
							   //��� ���������� ����� ������ �������� �� 1 ����,� ���� �� 2 � �.�.
		int i = 0;
		while (i < vec.size()) {
			for (int j = shift; j--; ++i) { // ���� j > 0
				if (vec[i] > vec[i + shift]) { // ��������� ����� ������
					return false; // ����� ����������� ��������
				}
			}
			i += shift; // ���������� �� �������� �������� ������
		}
	}
	return true;
}

int main() {
	ifstream in("input.txt"); // ��������� �������� ����

	if (in.is_open()) { // ���� ������ �������� ����
		// ������ �-��� �������� � ����
		int countNums = 0; // �-��� ����� � ����
		int temp; // �������� �����

		while (!in.eof()) { // ���� �� ����� �����
			in >> temp; // ������� �������
			if (temp != 0 && temp != 1) { // ����������, �� �������� 0 �� 1
				cout << "The vector isn't binary!" << endl;
				return 0;
			}
			else countNums++; // ������������ ����� �-�� ����� � ����
		}

		double checkLength = log2(countNums);
		//cout << "Length: " << checkLength << endl;

		if (float(checkLength) != int(checkLength)) { // ����������, �� ������� ������� ������ ���������
			cout << "The length of vector isn't 2^n!" << endl;
			return 0;
		}

		in.seekg(0, ios::beg); // ���������� ������ �� ������� �����
		in.clear();

		// ��������� ������
		vector<bool> myVector(countNums);		//int* boolFunc = new int[countNums]; // ��������� �����

		int tempbool = 0; // ��������� �����-�������, �� ������� �����(int) �� ������� � ������(bool)
		// ������� �������� � ����� � �������� � ������
		for (int i = 0; i < countNums; i++) {
			in >> tempbool; // �������� ���� ����� ���� � int ����� ������� �������
			myVector[i] = tempbool; // � ����� ����� int ������������ � bool 
		}

		// �������� ������
		cout << endl << "!--The vector output--!" << endl << endl;
		cout << "F(x) = (";
		for (int i = 0; i < countNums; i++) {
			cout << myVector[i];
			if (i != countNums - 1) cout << ", ";
		}
		cout << ")" << endl;

		// �������� �� �����������
		
		if (isMonotone(myVector, countNums)) {
			cout << "The function is monotonic!" << endl;
			return 0;
		}
		else {
			cout << "The function isn't monotonic!" << endl;
			return 0;
		}

		return 0;
	}
	else { // ���� ������� ������� � ������� �����
		cout << "File not found!";
		return 0;
	}
}