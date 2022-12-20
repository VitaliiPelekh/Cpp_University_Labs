//In ascending order, print all integers in the range 1� 1000000, which are represented as k = m^2 + n^2, where m>0, n>0

#include<iostream>
#include<cmath>
#pragma warning(disable :4996)
using namespace std;
const double maxVal = 1000; // ������ ���� ��������

struct list { 
	long double value;
	struct list* next, *prev;
} *head, *tail;

void sum(); // ����������� ����� k �� ��������
void sort(); // ���������� �������� ����� ����� �� ����������
void checkValue(); // ������ ���������� ����� ��� ���������, �� ���������
void AddElemList(long double); // ��������� ������������� ����� � �����
void PrintList(); // ���� �����
void DestroyList(); // ��������� �����

int main() {
	sum(); 
	sort();
	checkValue();
	PrintList();
	DestroyList();
	return 0;
}

void sum() { // ����������� ����� k �� ��������
	long double k = 2, i = 1, j = 2;

	AddElemList(2); // ��������� ������� ����� head

	while (true) { 
		k = pow(i, 2) + pow(j, 2); // ������� ��������� ����� k

		if (k > 1 && k <= maxVal) { // ���� ����������� ����� k ����������� � �������� �������
			AddElemList(k); // ����������� ����� � �����
			j++; 
		}
		else if (k > maxVal && (j > i)) { // ���� ����� j ������� ������, ����� ���������� �� ���� ����� 
			i++; // �������� ��� ����� �
			j = i; // ���������� �������� �������� j ���, ��� ����� k ����� ������������� 
		} else break; // ���� i �� j ����� ��������, �� ����� k �������� �� ������� �������, ��� ��������� ����� ��������
	}
}

void AddElemList(long double number) { // ��������� ������������� ����� � �����
	list* ptr = new list;
	ptr->next = NULL;   // ������� ������� � ����
	ptr->value = number; 

	if (!head) { // ���� ����� �������
		ptr->prev = NULL; 
		head = tail = ptr;
	}
	else {
		ptr->prev = tail; 
		tail->next = ptr; 
		tail = ptr; 
	}
}

void sort() { // ���������� �������� ����� ����� �� ����������
	list* left = head; 
	list* right = head->next; 

	list* ptr = new list; 

	// ����������� ����� ������� (����� ���������)
	while (left->next) { 
		while (right) {  
			if ((left->value) > (right->value)) { // ����� ����� ���������� ������ �����
				ptr->value = left->value;  
				left->value = right->value;  
				right->value = ptr->value;
			}
			right = right->next;  // ���������� �� ���������� �������� ��� right
		}
		left = left->next;  // ���������� �� ���������� �������� ��� left
		right = left->next; // ���������� �������� �������� right
	}
}

void checkValue() { // ������ ���������� ����� ��� ���������, �� ���������
	list* left = head; 
	list* right = head->next; 

	while (left->next) { 
		while (right) { 
			if ((left->value) == (right->value)) { // ����� ������ ���� ��������
				left->next = right->next;
				delete right;
				right = left;
			}
			right = right->next;  // ���������� �� ���������� �������� ��� right
		}
		left = left->next;  // ���������� �� ���������� �������� ��� left
		if (left) right = left->next; // ���� �� ����� �����, ���������� �������� �������� right
		else break;
	}
}


void PrintList() { // ���� ����� 
	cout << endl;
	while (head) {
		cout << head->value << ' ';
		head = head->next;
	}
	cout << endl;
}

void DestroyList() { // ��������� �����
	list* ptr;
	while (head) {
		ptr = head->next; 
		delete head; 
		head = ptr; 
	}
}