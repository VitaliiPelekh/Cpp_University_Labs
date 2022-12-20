// findCity.cpp - the third program, which find city in routes by entered city
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

    char str[sizePos]; 
    do {
        cout << "Назва шуканого міста: "; gets_s(str); // get city to find
    } while (strlen(str) < 1);

    cout << "\n\nШукане місто у маршрутах:\n";  
    FindPointMarshruts(routes, n, str); // find and output route

    delete[]routes;
    cout << "\n\n!--- The end ---!\n" << endl;

    return 0;
}
