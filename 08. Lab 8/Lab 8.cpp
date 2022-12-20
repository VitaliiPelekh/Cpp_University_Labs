// Develop procedures to verify that the relationship given by the matrix is a complete order relationship.
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void deleteMtrx(int** arrMtrx, int n); // видалення динамічного масиву

struct PAIRS {
	int i, j; // координати елемента
	int value; // значення елемента
};

int main() {
	ifstream in("input.txt"); // створюємо файловий потік

	if (in.is_open()) { // якщо успішно відкрився файл

		// Рахуємо к-сть елементів в файлі
		int countNums = 0; // к-сть чисел в файлі
		int temp; // допоміжна змінна
		int countNumsOne = 0; // к-сть пар у матриці

		while (!in.eof()) { // поки не кінець файлу
			in >> temp; // зчитуємо елемент
			if (temp != 0 && temp != 1) { // перевіряємо, чи елементи матриці 0 та 1
				cout << "The matrix isn't binary!" << endl;
				return 0;
			}
			else {
				countNums++; // інкрементуємо змінну к-сті чисел у файлі
				if (temp == 1) countNumsOne++; // якщо це пара, то інкрементуємо змінну-лічильник
			}
		}

		if (float(sqrt(countNums)) != int(sqrt(countNums)) || countNums < 4) { // перевіряємо, чи матриця квадратна
			cout << "The matrix isn't square!" << endl;
			return 0;
		}
		
		in.seekg(0, ios::beg); // переводимо курсор на початок файлу
		in.clear();

		// Підрахуємо к-сть чисел в одному рядку, а саме рахуємо к-сть пробілів до знака переводу на новий рядок 
		int countSpace = 0; // к-сть пробілів ставимо 0
		char symbol; // змінна для зчитування символів
		while (!in.eof()) { // поки не кінець файлу
			in.get(symbol); // зчитуємо посимвольно дані
			if (symbol == ' ') countSpace++; // якщо зчитане дане пробіл, то інкрементумо змінну
			if (symbol == '\n') break; // якщо кінець рядка, то зупиняємо цикл, так як матриця має бути квадратна
		}

		in.seekg(0, ios::beg); // переводимо курсор на початок файлу
		in.clear();
		
		// Утворюємо матрицю
		int n = countSpace + 1; // рахуємо к-сть рядків і одночасно стовпців, бо матриця квадратна. Число стовпців на одиницю більше за к-сть пробілів
		int** arrMtrx; // вказівник на вказівники
		arrMtrx = new int* [n]; // масив рядків
		for (int i = 0; i < n; i++) arrMtrx[i] = new int[n]; // ініціалізуємо стовпці

		// Зчитуємо елементи з файлу і заносимо в матрицю
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				in >> arrMtrx[i][j];

		// Виводимо матрицю
		cout << endl << "!--The matrix output--!" << endl << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				cout << arrMtrx[i][j] << "\t";
			cout << "\n";
		}
		cout << endl;

		// Перевіряємо чи є відношення, задане за допомогою матриці, відношенням повного порядку
		// 1. рефлексивність: 
		for (int i = 0; i < n; i++) {
			if (arrMtrx[i][i] != 1) {
				cout << "The matrix isn't reflexive! Hence the matrix isn't a total order." << endl;
				deleteMtrx(arrMtrx, n); // видалення динамічного масиву
				in.close();
				return 0;
			}
		}

		//2. антисиметричність: 
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i != j && arrMtrx[i][j] == arrMtrx[j][i] && arrMtrx[i][j] != 0) {
					cout << "The matrix isn't antisymmetric! Hence the matrix isn't a total order." << endl;
					deleteMtrx(arrMtrx, n); // видалення динамічного масиву
					in.close();
					return 0;
				}
			}
		}

		//3. транзитивність: 
		
		//Утворюємо структуру, щоб виконати композицію пар
		PAIRS* arrPairs = new PAIRS[countNumsOne];
		int k = 0; // лічильник для структури
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				if (arrMtrx[i][j] == 1) { // якщо це пара, то заносимо в структуру дані про неї
					arrPairs[k].value = arrMtrx[i][j];
					arrPairs[k].i = i;
					arrPairs[k].j = j;
					k++;
				}
			}	

		bool flagTrans = false; // прапорець-індикатор транзитивності
		for (int k1 = 0; k1 < countNumsOne; k1++) {
			for (int k2 = 0; k2 < countNumsOne; k2++) {
				if (k1 != k2 && arrPairs[k1].j == arrPairs[k2].i) { // якщо знайдено дві пари для композиції
					for (int k3 = 0; k3 < countNumsOne; k3++) { // порівнюємо результат композиції з існуючими парами в структурі
						if (arrPairs[k3].i == arrPairs[k1].i && arrPairs[k3].j == arrPairs[k2].j) { // якщо результат транзитивності не сходиться з існуючою парою в структурі
							flagTrans = true;
						}
					}
					if (!flagTrans) { // Якщо відношення не транзитивне
						cout << "The matrix isn't transitive! Hence the matrix isn't a total order." << endl;
						delete[]arrPairs; // видалення динамічного масиву структури
						deleteMtrx(arrMtrx, n); // видалення динамічного масиву
						in.close();
						return 0;
					}
				}
				flagTrans = false;
			}
		}
		
		// Отже, перші три перевірки перевіряють, чи відношення часткового порядку
		// Тепер перевіряємо на сумісність відношення, якщо так, тоді відношення повного порядку

		// Беремо матрицю 3х3, наприклад пара a,b => aRb || bRa - умова має виконуватися
		// пара a,c => aRc || cRa - умова має виконуватися
		// пара b,c => bRc || cRb - умова має виконуватися

		//4. сумісність: 

		bool flagComp = false; // прапорець-індикатор сумісності
		for (int k1 = 1; k1 < n - 1; k1++) { // TEST EXAMPLE: a,b; a,c; b,c;
			for (int k2 = k1 + 1; k2 < n; k2++) {
				for (int k = 0; k < countNumsOne; k++) { // проглядаємо всі пари в структурі
					if ((arrPairs[k].i == k1 && arrPairs[k].j == k2) || (arrPairs[k].j == k1 && arrPairs[k].i == k2)) { //наприклад a,b = > aRb || bRa
						flagComp = true;
					}
				}
				if (!flagComp) { // Якщо відношення не сумісне
					cout << "The matrix isn't comparable! Hence the matrix isn't a total order." << endl;
					delete[]arrPairs; // видалення динамічного масиву структури
					deleteMtrx(arrMtrx, n); // видалення динамічного масиву
					in.close();
					return 0;
				}
				flagComp = false;
			}
		}
			
		cout << endl << "The matrix is: reflexive, antisymmetric, transitive and comparable." << endl << "Hence, the matrix is a total order!" << endl;
		deleteMtrx(arrMtrx, n); // видалення динамічного масиву
		delete[]arrPairs; // видалення динамічного масиву структури
		in.close();
	}
	else { // якщо виникла помилка у відкритті файлу
		cout << "File not found!";
	}
	return 0;
}

void deleteMtrx(int** arrMtrx, int n) { // видалення динамічного масиву
	for (int i = 0; i < n; i++) delete[] arrMtrx[i];
	delete[] arrMtrx;
}