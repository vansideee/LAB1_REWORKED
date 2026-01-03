#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "employee.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Ожидаем: Reporter.exe <bin_file> <report_file> <rate>

    if (argc != 4) {
        cout << "Usage: Reporter.exe <input_bin> <output_txt> <pay_rate>" << endl;
        return 1;
    }

    char* binFile = argv[1];
    char* reportFile = argv[2];
    double rate = atof(argv[3]);

    ifstream in(binFile, ios::binary);
    ofstream out(reportFile);

    if (!in.is_open()) {
        cout << "Error: Could not open binary file." << endl;
        return 1;
    }

    out << "Report file: " << binFile << "\n";
    out << "Num, Name, Hours, Salary\n"; // По формату задания

    employee emp;
    while (in.read((char*)&emp, sizeof(employee))) {
        double salary = emp.hours * rate;
        out << emp.num << ", "
            << emp.name << ", "
            << emp.hours << ", "
            << fixed << setprecision(2) << salary << endl;
    }

    in.close();
    out.close();
    cout << "Report generated successfully." << endl;
    return 0;
}