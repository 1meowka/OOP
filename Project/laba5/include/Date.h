#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
    int day;
    int month;
    int year;

    int daysInMonth(int month, int year) const;

public:
    Date();
    Date(int d, int m, int y);
    Date(const std::string& dateStr);
    Date(const Date& other);

    Date& operator=(const Date& other);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);

    static bool isValid(int day, int month, int year);
    static bool parseDate(const std::string& dateStr, int& d, int& m, int& y);

    std::string toString() const;

    Date operator+(int days) const;
    Date operator++(int);
};

#endif // DATE_H
