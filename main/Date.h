#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
private:
    int day;
    int month;
    int year;

    static bool isLeapYear(int y);
    static int daysInMonth(int m, int y);
    static bool isValidDate(int d, int m, int y);

public:
    Date();
    Date(int d, int m, int y);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);
    void setDate(int d, int m, int y);

    void addDays(int n);
    int differenceInYears(const Date& other) const;

    bool operator<(const Date& o) const;
    bool operator==(const Date& o) const;

    friend std::ostream& operator<<(std::ostream& os, const Date& d);
};

#endif // DATE_H
