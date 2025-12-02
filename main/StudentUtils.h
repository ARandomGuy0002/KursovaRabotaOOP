#ifndef STUDENT_UTILS_H
#define STUDENT_UTILS_H

#include <vector>
#include <string>
#include "Student.h"

void addStudent(std::vector<Student>& group);
void printAllStudents(const std::vector<Student>& group, const Date& today);
void printMaxAverage(const std::vector<Student>& group, const Date& today);
void printStudents18to26(const std::vector<Student>& group, const Date& today);
void searchByFacultyNumber(const std::vector<Student>& group, const Date& today);
void sortByName(std::vector<Student>& group);
void sortByAverage(std::vector<Student>& group);
void saveToFile(const std::vector<Student>& group, const Date& today, const std::string& filename);
void loadFromFile(std::vector<Student>& group, const std::string& filename);
bool readDate(const std::string& prompt, int& d, int& m, int& y);

#endif // STUDENT_UTILS_H
