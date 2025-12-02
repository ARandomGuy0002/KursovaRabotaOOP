#include "Date.h"
#include <iostream>

using namespace std;

bool Date::isLeapYear(int y) {
    return (y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0));
}

int Date::daysInMonth(int m, int y) {
    switch (m) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return isLeapYear(y) ? 29 : 28;
    default:
        return 0;
    }
}

bool Date::isValidDate(int d, int m, int y) {
    if (y < 0 || m < 1 || m > 12)
        return false;
    int maxDay = daysInMonth(m, y);
    if (maxDay == 0) return false;
    return d >= 1 && d <= maxDay;
}

Date::Date() : day(1), month(1), year(2000) {}

Date::Date(int d, int m, int y) {
    if (isValidDate(d, m, y)) {
        day = d;
        month = m;
        year = y;
    }
    else {
        cerr << "Invalid date, set to default 01.01.2000\n";
        day = 1;
        month = 1;
        year = 2000;
    }
}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

void Date::setDay(int d) {
    if (isValidDate(d, month, year)) {
        day = d;
    }
    else {
        cerr << "Invalid day for current month/year\n";
    }
}

void Date::setMonth(int m) {
    if (isValidDate(day, m, year)) {
        month = m;
    }
    else {
        cerr << "Invalid month (day may not fit in that month)\n";
    }
}

void Date::setYear(int y) {
    if (isValidDate(day, month, y)) {
        year = y;
    }
    else {
        cerr << "Invalid year (day/month combination invalid)\n";
    }
}

void Date::setDate(int d, int m, int y) {
    if (isValidDate(d, m, y)) {
        day = d;
        month = m;
        year = y;
    }
    else {
        cerr << "Invalid date, not changed\n";
    }
}

void Date::addDays(int n) {
    if (n < 0) {
        cerr << "addDays with negative n is not supported\n";
        return;
    }
    while (n > 0) {
        day++;
        if (day > daysInMonth(month, year)) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        --n;
    }
}

int Date::differenceInYears(const Date& other) const {
    const Date* bigger = this;
    const Date* smaller = &other;

    if (*bigger < *smaller) {
        bigger = &other;
        smaller = this;
    }

    int diff = bigger->year - smaller->year;
    if (bigger->month < smaller->month ||
        (bigger->month == smaller->month && bigger->day < smaller->day)) {
        diff--;
    }
    return diff;
}

bool Date::operator<(const Date& o) const {
    if (year != o.year) return year < o.year;
    if (month != o.month) return month < o.month;
    return day < o.day;
}

bool Date::operator==(const Date& o) const {
    return day == o.day && month == o.month && year == o.year;
}

ostream& operator<<(ostream& os, const Date& d) {
    os << (d.day < 10 ? "0" : "") << d.day << "."
        << (d.month < 10 ? "0" : "") << d.month << "."
        << d.year;
    return os;
}
