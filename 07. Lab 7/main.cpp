//In ascending order, print all integers in the range 1… 1000000, which are represented as k = m^2 + n^2, where m>0, n>0

#include<iostream>
#include<cmath>
#pragma warning(disable :4996)
using namespace std;
const double maxVal = 1000; // верхня межа діапазону

struct list { 
	long double value;
	struct list* next, *prev;
} *head, *tail;

void sum(); // генерування числа k за формулою
void sort(); // сортування елементів вузлів черги за зростанням
void checkValue(); // шукаємо здубльовані числа при генерації, та видаляємо
void AddElemList(long double); // додавання згенерованого числа у чергу
void PrintList(); // вивід черги
void DestroyList(); // звільнення пам’яті

int main() {
	sum(); 
	sort();
	checkValue();
	PrintList();
	DestroyList();
	return 0;
}

void sum() { // генерування числа k за формулою
	long double k = 2, i = 1, j = 2;

	AddElemList(2); // створення першого вузла head

	while (true) { 
		k = pow(i, 2) + pow(j, 2); // формула генерації числа k

		if (k > 1 && k <= maxVal) { // поки згенероване число k знаходиться в заданому діапазоні
			AddElemList(k); // накопичення вузлів у чергу
			j++; 
		}
		else if (k > maxVal && (j > i)) { // якщо змінна j занадто велика, тобто збільшувати її немає змісту 
			i++; // збільшуємо тоді змінну і
			j = i; // перезадаємо стартове значення j так, щоб числа k менше повторювалися 
		} else break; // якщо i та j великі настільки, що число k виходить за заданий діапазон, тоді генерація чисел закінчена
	}
}

void AddElemList(long double number) { // додавання згенерованого числа у чергу
	list* ptr = new list;
	ptr->next = NULL;   // останній елемент у черзі
	ptr->value = number; 

	if (!head) { // якщо черга порожня
		ptr->prev = NULL; 
		head = tail = ptr;
	}
	else {
		ptr->prev = tail; 
		tail->next = ptr; 
		tail = ptr; 
	}
}

void sort() { // сортування елементів вузлів черги за зростанням
	list* left = head; 
	list* right = head->next; 

	list* ptr = new list; 

	// Адаптований метод Неймана (метод бульбашки)
	while (left->next) { 
		while (right) {  
			if ((left->value) > (right->value)) { // умова обміну елементами сусідніх вузлів
				ptr->value = left->value;  
				left->value = right->value;  
				right->value = ptr->value;
			}
			right = right->next;  // переходимо до наступного елементу для right
		}
		left = left->next;  // переходимо до наступного елементу для left
		right = left->next; // перезадаємо стартове значення right
	}
}

void checkValue() { // шукаємо здубльовані числа при генерації, та видаляємо
	list* left = head; 
	list* right = head->next; 

	while (left->next) { 
		while (right) { 
			if ((left->value) == (right->value)) { // умова рівності двох елементів
				left->next = right->next;
				delete right;
				right = left;
			}
			right = right->next;  // переходимо до наступного елементу для right
		}
		left = left->next;  // переходимо до наступного елементу для left
		if (left) right = left->next; // якщо не кінець черги, перезадаємо стартове значення right
		else break;
	}
}


void PrintList() { // вивід черги 
	cout << endl;
	while (head) {
		cout << head->value << ' ';
		head = head->next;
	}
	cout << endl;
}

void DestroyList() { // звільнення пам’яті
	list* ptr;
	while (head) {
		ptr = head->next; 
		delete head; 
		head = ptr; 
	}
}