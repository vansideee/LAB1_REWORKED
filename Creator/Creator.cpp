#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "employee.h" // Убедись, что файл лежит рядом или добавь путь

using namespace std;

int main(int argc, char* argv[]) {
    // Creator.exe data.bin 3 (пример вызова)

    if (argc != 3) {
        // Если запустили просто так, без аргументов — спросим руками (для удобства тестов)
        cout << "Usage: Creator.exe <filename> <count>" << endl;
        return 1;
    }

    char* filename = argv[1];
    int count = atoi(argv[2]);

    ofstream out(filename, ios::binary);

    if (!out.is_open()) {
        cout << "Error: could not create file " << filename << endl;
        return 0;
    }

    employee emp;
    for (int i = 0; i < count; i++) {
        cout << "\nEmployee " << (i + 1) << ":" << endl;
        cout << "ID number: "; cin >> emp.num;
        cout << "Name: "; cin >> emp.name;
        cout << "Hours: "; cin >> emp.hours;

        out.write((char*)&emp, sizeof(employee));
    }

    out.close();
    return 0;
}