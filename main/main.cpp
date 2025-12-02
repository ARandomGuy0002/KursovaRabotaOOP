#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <limits>
#include <vector>
#include "StudentUtils.h"


using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int td, tm, ty;
    readDate("Enter today's date (dd.mm.yyyy): ", td, tm, ty);
    Date today(td, tm, ty);


    vector<Student> group;
    bool running = true;

    while (running) {
        cout << "\n===== MENU =====\n";
        cout << "1. Add student\n";
        cout << "2. Show all students\n";
        cout << "3. Show student with maximal average grade\n";
        cout << "4. Show students between 18 and 26 years\n";
        cout << "5. Search by faculty number\n";
        cout << "6. Sort students by name\n";
        cout << "7. Sort students by average grade\n";
        cout << "8. Save to file\n";
        cout << "9. Load from file\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            addStudent(group);
            break;
        case 2:
            printAllStudents(group, today);
            break;
        case 3:
            printMaxAverage(group, today);
            break;
        case 4:
            printStudents18to26(group, today);
            break;
        case 5:
            searchByFacultyNumber(group, today);
            break;
        case 6:
            sortByName(group);
            break;
        case 7:
            sortByAverage(group);
            break;
        case 8: {
            string filename;
            cout << "File name: ";
            getline(cin, filename);
            saveToFile(group, today, filename);
            break;
        }
        case 9: {
            string filename;
            cout << "File name: ";
            getline(cin, filename);
            loadFromFile(group, filename);
            break;
        }
        case 0:
            running = false;
            break;
        default:
            cout << "Invalid option.\n";
            break;
        }
    }

    cout << "Goodbye!\n";
    return 0;
}
