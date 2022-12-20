//Determine whether the given function is monotonic.

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

bool isMonotone(const vector<bool>& vec, int n) {
	int shift = vec.size(); // змінна для зміщення ітератора в циклі, для порівняння саме порівняльних наборів
	
	while ((shift /= 2) > 0) { // ділимо постійно на половину "зміщувач",
							   //щоб порівнювати сусідні набори спочатку по 1 змінні,а потім по 2 і т.к.
		int i = 0;
		while (i < vec.size()) {
			for (int j = shift; j--; ++i) { // доки j > 0
				if (vec[i] > vec[i + shift]) { // порівнюємо сусідні набори
					return false; // умова монотонності порушена
				}
			}
			i += shift; // переходимо до наступної половини наборів
		}
	}
	return true;
}

int main() {
	ifstream in("input.txt"); // створюємо файловий потік

	if (in.is_open()) { // якщо успішно відкрився файл
		// Рахуємо к-сть елементів в файлі
		int countNums = 0; // к-сть чисел в файлі
		int temp; // допоміжна змінна

		while (!in.eof()) { // поки не кінець файлу
			in >> temp; // зчитуємо елемент
			if (temp != 0 && temp != 1) { // перевіряємо, чи елементи 0 та 1
				cout << "The vector isn't binary!" << endl;
				return 0;
			}
			else countNums++; // інкрементуємо змінну к-сті чисел у файлі
		}

		double checkLength = log2(countNums);
		//cout << "Length: " << checkLength << endl;

		if (float(checkLength) != int(checkLength)) { // перевіряємо, чи довжина вектора задана правильно
			cout << "The length of vector isn't 2^n!" << endl;
			return 0;
		}

		in.seekg(0, ios::beg); // переводимо курсор на початок файлу
		in.clear();

		// Утворюємо вектор
		vector<bool> myVector(countNums);		//int* boolFunc = new int[countNums]; // динамічний масив

		int tempbool = 0; // створюємо змінну-гаранта, бо напряму число(int) не занесеш в вектор(bool)
		// Зчитуємо елементи з файлу і заносимо у вектор
		for (int i = 0; i < countNums; i++) {
			in >> tempbool; // файловий потік тільки може в int змінну занести введене
			myVector[i] = tempbool; // а тепер легко int конвертується в bool 
		}

		// Виводимо вектор
		cout << endl << "!--The vector output--!" << endl << endl;
		cout << "F(x) = (";
		for (int i = 0; i < countNums; i++) {
			cout << myVector[i];
			if (i != countNums - 1) cout << ", ";
		}
		cout << ")" << endl;

		// Перевірка на монотонність
		
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
	else { // якщо виникла помилка у відкритті файлу
		cout << "File not found!";
		return 0;
	}
}