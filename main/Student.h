#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Date.h"

class Student {
private:
    std::string name;
    std::string facultyNumber;
    Date birthDate;
    double averageGrade;
    std::vector<double> grades;

    void recalculateAverage();

public:
    Student();
    Student(const std::string& n,
        const std::string& fn,
        const Date& bd);

    std::string getName() const;
    std::string getFacultyNumber() const;
    Date getBirthDate() const;
    double getAverageGrade() const;

    void setName(const std::string& n);
    void setFacultyNumber(const std::string& fn);
    void setBirthDate(const Date& bd);

    void addGrade(double g);
    int getAge(const Date& today) const;

    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};

#endif // STUDENT_H
