// sortRoutes.cpp - the first program, which sort routes
#include"headFile.h"

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int n; // count of routes
    do {
        n = EnterNumber("Кількість маршрутів: ");
    } while (n < 1);
    cout << endl;

    MARSHRUT* routes = new MARSHRUT[n]; // dynamic array of routes

    EnterArrayMarshruts(routes, n); cout << endl; // enter routes
    PrintArrayMarshruts(routes, n, "Введені маршрути: "); cout << endl; // output routes
    SortArrayMarshruts(routes, n, "Посортовані маршрути: "); // sort and output routes

    delete[]routes;
    cout << "\n\n!--- The end ---!\n" << endl;

    return 0;
}
