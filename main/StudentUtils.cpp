#include "StudentUtils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

bool readDate(const std::string& prompt, int& d, int& m, int& y) {
    std::string line;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, line);

        if (line.empty()) {
            std::cout << "Date cannot be empty. Try again.\n";
            continue;
        }

        int dotCount = 0;
        for (char c : line) {
            if (c == '.') dotCount++;
        }

        if (dotCount != 2) {
            std::cout << "Invalid format. Use dd.mm.yyyy\n";
            continue;
        }

        for (char& c : line) {
            if (c == '.') c = ' ';
        }

        std::stringstream ss(line);
        char extra;

        if ((ss >> d >> m >> y) && !(ss >> extra)) {
            return true;
        }
        else {
            std::cout << "Invalid format. Use dd.mm.yyyy\n";
        }
    }
}


void addStudent(vector<Student>& group) {
    cout << "\n--- Add student ---\n";

    string name;
    cout << "Name: ";
    getline(cin, name);

    string fn;
    cout << "Faculty number: ";
    getline(cin, fn);

    int bd, bm, by;
    readDate("Birth date (dd.mm.yyyy): ", bd, bm, by);
    Date bdate(bd, bm, by);
    Student s(name, fn, bdate);


    int countGrades;
    cout << "How many grades to enter? ";
    cin >> countGrades;

    for (int i = 0; i < countGrades; ++i) {
        double g;

        while (true) {
            cout << "Grade " << i + 1 << " (2 - 6): ";
            cin >> g;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            if (g >= 2.0 && g <= 6.0) {
                s.addGrade(g);
                break;
            }

            cout << "Grade must be between 2 and 6. Try again.\n";
        }
    }


    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    group.push_back(s);
    cout << "Student added.\n";
}

void printAllStudents(const vector<Student>& group, const Date& today) {
    cout << "\n--- All students ---\n";
    if (group.empty()) {
        cout << "No students.\n";
        return;
    }

    for (const auto& s : group) {
        cout << "---------------------------\n";
        cout << s;
        cout << "Age: " << s.getAge(today) << "\n";
    }
}

void printMaxAverage(const vector<Student>& group, const Date& today) {
    cout << "\n--- Student with maximal average grade ---\n";
    if (group.empty()) {
        cout << "No students.\n";
        return;
    }

    int idxMax = 0;
    for (int i = 1; i < (int)group.size(); ++i) {
        if (group[i].getAverageGrade() > group[idxMax].getAverageGrade()) {
            idxMax = i;
        }
    }

    cout << group[idxMax];
    cout << "Age: " << group[idxMax].getAge(today) << "\n";
}

void printStudents18to26(const vector<Student>& group, const Date& today) {
    cout << "\n--- Students between 18 and 26 (inclusive) ---\n";
    bool found = false;

    for (const auto& s : group) {
        int age = s.getAge(today);
        if (age >= 18 && age <= 26) {
            cout << "---------------------------\n";
            cout << s;
            cout << "Age: " << age << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No students in this age range.\n";
    }
}

void searchByFacultyNumber(const vector<Student>& group, const Date& today) {
    cout << "\n--- Search by faculty number ---\n";
    if (group.empty()) {
        cout << "No students.\n";
        return;
    }

    string fn;
    cout << "Enter faculty number: ";
    getline(cin, fn);

    bool found = false;
    for (const auto& s : group) {
        if (s.getFacultyNumber() == fn) {
            cout << "Student found:\n";
            cout << s;
            cout << "Age: " << s.getAge(today) << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No student with this faculty number.\n";
    }
}

void sortByName(vector<Student>& group) {
    sort(group.begin(), group.end(),
        [](const Student& a, const Student& b) {
            return a.getName() < b.getName();
        });
    cout << "Students sorted by name.\n";
}

void sortByAverage(vector<Student>& group) {
    sort(group.begin(), group.end(),
        [](const Student& a, const Student& b) {
            return a.getAverageGrade() > b.getAverageGrade();
        });
    cout << "Students sorted by average grade (descending).\n";
}

void saveToFile(const vector<Student>& group, const Date& today,
    const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Error opening file " << filename << " for writing.\n";
        return;
    }

    for (const auto& s : group) {
        fout << s.getName() << "\n";
        fout << s.getFacultyNumber() << "\n";
        fout << s.getBirthDate().getDay() << " "
            << s.getBirthDate().getMonth() << " "
            << s.getBirthDate().getYear() << "\n";
        fout << s.getAverageGrade() << "\n";
        fout << s.getAge(today) << "\n";
        fout << "----\n";
    }

    fout.close();
    cout << "Data saved to file " << filename << "\n";
}

void loadFromFile(vector<Student>& group, const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Error opening file " << filename << " for reading.\n";
        return;
    }

    group.clear();

    string line;
    while (true) {
        string name;
        if (!getline(fin, name)) break;
        if (name.empty()) break;

        string fn;
        if (!getline(fin, fn)) break;

        string dateLine;
        if (!getline(fin, dateLine)) break;
        stringstream ss(dateLine);
        int d, m, y;
        ss >> d >> m >> y;
        Date bd(d, m, y);

        string avgLine;
        if (!getline(fin, avgLine)) break;
        double avg;
        {
            stringstream ss2(avgLine);
            ss2 >> avg;
        }

        // age line
        getline(fin, line);
        // separator line
        getline(fin, line);

        Student s(name, fn, bd);
        s.addGrade(avg);

        group.push_back(s);
    }

    fin.close();
    cout << "Data loaded from file " << filename << "\n";
}
