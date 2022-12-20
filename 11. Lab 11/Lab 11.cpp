// Check that the graph specified by the K-list is connected.

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ifstream in("input.txt"); // створюємо файловий потік

    if (in.is_open()) { // якщо успішно відкрився файл
        // Рахуємо к-сть елементів в файлі
        int countNums = 0; // к-сть чисел в файлі
        int n = 0, m = 0; // n - к-сть вершин, m - к-сть ребер
        int temp; // допоміжна змінна

        while (!in.eof()) { // поки не кінець файлу
            in >> temp; // зчитуємо елемент
            if (temp > n) n = temp; // вичисляємо кількість вершин
            countNums++; // інкрементуємо змінну к-сті чисел у файлі
        }

        if (countNums % 2) { // перевіряємо на парну кількість елементів заданого списку
            cout << "Incorrect entered data!" << endl;
            return 0;
        }

        in.seekg(0, ios::beg); // переводимо курсор на початок файлу
        in.clear();

        int k = 1; // змінна прапорець
        while (!in.eof()) { // поки не кінець файлу
            in >> temp; // зчитуємо елемент
            if (k > 1) { // виводимо введений список у консоль та рахуємо кількість ребер
                m++;
                k = 1;
                cout << temp << ' ';
                cout << endl;
            }
            else {
                cout << temp << ' ';
                k++;
            }
        }

        cout << "\nEntered graph has:  "<<n<<"-vertices, "<<m<<"-edges.\n";

        in.seekg(0, ios::beg); // переводимо курсор на початок файлу
        in.clear();

        vector<vector<int>> graph(n); // граф
        int u = 0, v = 0; // u - перша вершина у парі, v - друга вершина у парі

        k = 1; // змінна прапорець
        for (int i = 0; i < countNums; i++) { // зчитуємо граф
            
            in >> temp; // Зчитуємо елементи з файлу і заносимо по черзі у вектор

            if (k == 1) {
                u = temp;
            }
            else {
                v = temp;
            }

            if (k == 2) {
                graph[u - 1].push_back(v - 1);
                graph[v - 1].push_back(u - 1);
                k = 1;
            }else k++;
        }

        int sp = 0; // початкова вершина
        queue<int> queueGraph; // черга, що містить вершини
        queueGraph.push(sp); // перший елемент
        vector<bool> flag(n); // булевий вектор-прапорець, який вказує на зв'язність вершини з іншими
        flag[sp] = true;

        while (!queueGraph.empty()) {// поки цикл не пройде всі вершини, які є зв'язані з даною
            int fp = queueGraph.front(); // отримуємо посилання на перший елемент черги
            queueGraph.pop(); // забираємо з черги одну вершину
            for (int i = 0; i < graph[fp].size(); ++i) { // проходимо по всіх ребрах, які зв'язані з даною вершиною
                int actualVert = graph[fp][i]; // поточна вершина
                if (!flag[actualVert]) { // якщо поточна вершина ще не відмічена
                    flag[actualVert] = true; // відмічаємо її
                    queueGraph.push(actualVert); // та додаємо її у чергу
                }
            }
        }
        
        vector<bool>::iterator itFlag; // змінна для швидкого проходу по вектору
        itFlag = find(flag.begin(), flag.end(), false); // дивимося, чи залишилися вершини, які незв'язані ні з однією вершиною

        if (itFlag == flag.end()) cout << endl << "Entered graph is connected!"; // якщо всі вершини обійшли, то граф є зв'язним
        else cout << endl << "Entered graph isn't connected!";

        return 0;
    }
    else { // якщо виникла помилка у відкритті файлу
        cout << "File not found!";
        return 0;
    }
}