// findNumber.cpp - the second program, which find routes by entered number
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

    int g;
    do {
        g = EnterNumber("Номер шуканого маршруту: "); // get number of route to find
    } while (g < 1);

    cout << "\n\nШуканий маршрут:\n";
    FindNumberMarshruts(routes, n, g); // find and output route

    delete[]routes;
    cout << "\n\n!--- The end ---!\n" << endl;

    return 0;
}
