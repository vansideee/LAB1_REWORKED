#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h> // Обязательно для CreateProcess и WaitForSingleObject
#include "employee.h"

using namespace std;

void printBinary(const char* filename) {
    ifstream in(filename, ios::binary);
    employee emp;
    cout << "\n>>> Binary File Content (" << filename << "):" << endl;
    while (in.read((char*)&emp, sizeof(employee))) {
        cout << "ID: " << emp.num
            << " | Name: " << emp.name
            << " | Hours: " << emp.hours << endl;
    }
    in.close();
    cout << "------------------------------------\n";
}

void printReport(const char* filename) {
    ifstream in(filename);
    string line;
    cout << "\n>>> Report File Content (" << filename << "):" << endl;
    while (getline(in, line)) {
        cout << line << endl;
    }
    in.close();
    cout << "------------------------------------\n";
}

int main() {
    // Переменные для ввода
    char binFilename[100];
    int recordCount;
    char reportFilename[100];
    double hourlyRate;

    // 1. Ввод для Creator
    cout << "Enter binary filename (e.g., data.bin): ";
    cin >> binFilename;
    cout << "Enter number of records: ";
    cin >> recordCount;

    // Формируем команду для запуска Creator
    // Creator.exe имя_файла число
    string cmdCreator = "Creator.exe " + string(binFilename) + " " + to_string(recordCount);

    // Структуры запуска процесса
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // 2. Запускаем Creator
    // CreateProcess хочет не const char*, поэтому берем указатель на буфер строки
    // Обязательно ставим FALSE в inheritHandles
    if (CreateProcess(NULL, &cmdCreator[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cout << "[Main] Creator process started..." << endl;
        // 3. Ждем завершения
        WaitForSingleObject(pi.hProcess, INFINITE);
        cout << "[Main] Creator process finished." << endl;

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        cout << "[Main] Error launching Creator. Make sure Creator.exe is in the same folder!" << endl;
        return 1;
    }

    // 4. Выводим бинарный файл
    printBinary(binFilename);

    // 5. Ввод для Reporter
    cout << "Enter report filename (e.g., report.txt): ";
    cin >> reportFilename;
    cout << "Enter hourly rate: ";
    cin >> hourlyRate;

    // 6. Запускаем Reporter
    // Reporter.exe бинарник отчет ставка
    string cmdReporter = "Reporter.exe " + string(binFilename) + " " + string(reportFilename) + " " + to_string(hourlyRate);

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcess(NULL, &cmdReporter[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cout << "[Main] Reporter process started..." << endl;
        // 7. Ждем
        WaitForSingleObject(pi.hProcess, INFINITE);
        cout << "[Main] Reporter process finished." << endl;

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        cout << "[Main] Error launching Reporter." << endl;
        return 1;
    }

    // 8. Выводим отчет
    printReport(reportFilename);

    cout << "Main program finished." << endl;
    system("pause"); // Чтобы консоль не закрылась мгновенно
    return 0;
}