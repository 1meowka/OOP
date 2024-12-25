#include "Date.h"
#include <regex>
#include <stdexcept>

Date::Date() : day(1), month(1), year(1900) {}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

Date::Date(const std::string& dateStr) {
    if (!parseDate(dateStr, day, month, year)) {
        day = 1; month = 1; year = 1900;
    }
}

Date::Date(const Date& other)
    : day(other.day), month(other.month), year(other.year) {}

Date& Date::operator=(const Date& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
    }
    return *this;
}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

void Date::setDay(int d) { day = d; }
void Date::setMonth(int m) { month = m; }
void Date::setYear(int y) { year = y; }

int Date::daysInMonth(int month, int year) const {
    int dim[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // Корректировка на високосный год
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        dim[1] = 29;
    }
    return dim[month - 1];
}

bool Date::isValid(int d, int m, int y) {
    if (y < 1900 || y > 2008) return false;
    if (m < 1 || m > 12) return false;

    int daysInMonthArr[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    // Високосный год
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        daysInMonthArr[1] = 29;
    }
    if (d < 1 || d > daysInMonthArr[m - 1]) return false;
    return true;
}

bool Date::parseDate(const std::string& dateStr, int& d, int& m, int& y) {
    // Формат DD-MM-YYYY
    std::regex dateRegex("^\\d{2}-\\d{2}-\\d{4}$");
    if (std::regex_match(dateStr, dateRegex)) {
        d = std::stoi(dateStr.substr(0, 2));
        m = std::stoi(dateStr.substr(3, 2));
        y = std::stoi(dateStr.substr(6, 4));
        return isValid(d, m, y);
    }
    return false;
}

std::string Date::toString() const {
    // Вывод в формате D.M.YYYY (с добавлением 0 к месяцу, если <10)
    std::string formattedDate = std::to_string(day) + ".";
    if (month < 10) formattedDate += "0";
    formattedDate += std::to_string(month) + "." + std::to_string(year);
    return formattedDate;
}

Date Date::operator+(int days) const {
    Date result = *this;
    result.day += days;
    while (result.day > result.daysInMonth(result.month, result.year)) {
        result.day -= result.daysInMonth(result.month, result.year);
        result.month++;
        if (result.month > 12) {
            result.month = 1;
            result.year++;
        }
    }
    return result;
}

Date Date::operator++(int) {
    Date temp = *this;
    *this = *this + 1;
    return temp;
}
