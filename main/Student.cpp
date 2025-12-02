#include "Student.h"
#include <iostream>
#include <iomanip>

using namespace std;

Student::Student()
    : name(""), facultyNumber(""), birthDate(), averageGrade(0.0) {
}

Student::Student(const string& n,
    const string& fn,
    const Date& bd)
    : name(n), facultyNumber(fn), birthDate(bd), averageGrade(0.0) {
}

void Student::recalculateAverage() {
    if (grades.empty()) {
        averageGrade = 0.0;
        return;
    }
    double sum = 0.0;
    for (double g : grades) sum += g;
    averageGrade = sum / grades.size();
}

string Student::getName() const { return name; }
string Student::getFacultyNumber() const { return facultyNumber; }
Date Student::getBirthDate() const { return birthDate; }
double Student::getAverageGrade() const { return averageGrade; }

void Student::setName(const string& n) { name = n; }
void Student::setFacultyNumber(const string& fn) { facultyNumber = fn; }
void Student::setBirthDate(const Date& bd) { birthDate = bd; }

void Student::addGrade(double g) {
    grades.push_back(g);
    recalculateAverage();
}

int Student::getAge(const Date& today) const {
    return today.differenceInYears(birthDate);
}

ostream& operator<<(ostream& os, const Student& s) {
    os << "Name: " << s.name << "\n"
        << "Faculty number: " << s.facultyNumber << "\n"
        << "Birth date: " << s.birthDate << "\n"
        << "Average grade: "
		<< fixed << setprecision(2) << s.averageGrade << "\n";
    return os;
}
