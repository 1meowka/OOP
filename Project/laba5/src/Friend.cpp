#include "Friend.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

// Конструкторы
Friend::Friend() : Person() {}

Friend::Friend(const std::string& ln, const std::string& fn) {
    lastName = ln;
    firstName = fn;
}

Friend::Friend(const std::string& ln, const std::string& fn, const std::string& mn,
               const Date& dob, const Address& addr,
               unsigned long long ph, char g) {
    lastName = ln;
    firstName = fn;
    middleName = mn;
    dateOfBirth = dob;
    address = addr;
    phone = ph;
    gender = g;
}

Friend::Friend(const Friend& other) {
    this->lastName = other.lastName;
    this->firstName = other.firstName;
    this->middleName = other.middleName;
    this->dateOfBirth = other.dateOfBirth;
    this->address = other.address;
    this->phone = other.phone;
    this->gender = other.gender;
}

// Оператор присваивания
Friend& Friend::operator=(const Friend& other) {
    if (this != &other) {
        this->lastName = other.lastName;
        this->firstName = other.firstName;
        this->middleName = other.middleName;
        this->dateOfBirth = other.dateOfBirth;
        this->address = other.address;
        this->phone = other.phone;
        this->gender = other.gender;
    }
    return *this;
}

// Реализация чисто виртуальной функции из Person
void Friend::printRole() const {
    std::cout << "Role: Friend";
}

// Перегрузка оператора < для сравнения по возрасту
bool Friend::operator<(const Friend& other) const {
    return this->calculateAge() < other.calculateAge();
}

// Перегрузка префиксного оператора --
Friend& Friend::operator--() {
    int y = dateOfBirth.getYear();
    if (y > 1900) {
        dateOfBirth.setYear(y - 1);
    }
    return *this;
}

// Метод для ввода данных друга
void Friend::inputFriend() {
    // lastName
    do {
        std::cout << "Enter last name: ";
        std::getline(std::cin, lastName);
        if (!isValidName(lastName)) {
            std::cout << "Invalid input. Please enter a valid name (e.g. Petrov).\n";
        }
    } while (!isValidName(lastName));

    // firstName
    do {
        std::cout << "Enter first name: ";
        std::getline(std::cin, firstName);
        if (!isValidName(firstName)) {
            std::cout << "Invalid input. Please enter a valid name (e.g. Ivan).\n";
        }
    } while (!isValidName(firstName));

    // middleName
    do {
        std::cout << "Enter middle name: ";
        std::getline(std::cin, middleName);
        if (!isValidName(middleName)) {
            std::cout << "Invalid input. Please enter a valid name (e.g. Nikolaevich).\n";
        }
    } while (!isValidName(middleName));

    // Дата рождения
    while (true) {
        std::cout << "Enter date of birth (DD-MM-YYYY): ";
        std::string dateStr;
        std::getline(std::cin, dateStr);
        int d, m, y;
        if (Date::parseDate(dateStr, d, m, y)) {
            dateOfBirth.setDay(d);
            dateOfBirth.setMonth(m);
            dateOfBirth.setYear(y);
            break;
        } else {
            std::cout << "Invalid date or format. Try again.\n";
        }
    }

    // Пол
    while (true) {
        std::cout << "Enter gender (M/F): ";
        std::cin >> gender;
        std::cin.ignore();
        gender = toupper(gender);
        if (gender != 'M' && gender != 'F') {
            std::cout << "Invalid input. Please enter 'M' or 'F'.\n";
        } else {
            break;
        }
    }

    // Адрес
    address.inputAddress();

    // Телефон
    while (true) {
        std::cout << "Enter phone number (89xxxxxxxxx): ";
        std::string phoneInput;
        std::getline(std::cin, phoneInput);
        try {
            unsigned long long phoneNum = std::stoull(phoneInput);
            if (isValidPhoneNumber(phoneNum)) {
                phone = phoneNum;
                break;
            } else {
                std::cout << "Invalid phone number.\n";
            }
        } catch (...) {
            std::cout << "Invalid input. Please enter numeric digits only.\n";
        }
    }
}

// Вывод информации о друге
void Friend::printFriend(int id) const {
    // Готовим данные для построчного вывода
    std::string idParts[MAX_LINES];       int idCount=0;
    splitString(std::to_string(id), idParts, idCount);

    std::string lnParts[MAX_LINES];       int lnCount=0;
    splitString(lastName, lnParts, lnCount);

    std::string fnParts[MAX_LINES];       int fnCount=0;
    splitString(firstName, fnParts, fnCount);

    std::string mnParts[MAX_LINES];       int mnCount=0;
    splitString(middleName, mnParts, mnCount);

    std::string dob = dateOfBirth.toString();
    std::string dobParts[MAX_LINES];      int dobCount=0;
    splitString(dob, dobParts, dobCount);

    std::string ageStr = std::to_string(calculateAge());
    std::string ageParts[MAX_LINES];      int ageCount=0;
    splitString(ageStr, ageParts, ageCount);

    std::string genStr(1, gender);
    std::string genParts[MAX_LINES];      int genCount=0;
    splitString(genStr, genParts, genCount);

    std::string addrStr = address.getFullAddress();
    std::string addrParts[MAX_LINES];     int addrCount=0;
    splitString(addrStr, addrParts, addrCount);

    std::string phoneStr = std::to_string(phone);
    std::string phoneParts[MAX_LINES];    int phoneCount=0;
    splitString(phoneStr, phoneParts, phoneCount);

    // Узнаем, сколько максимум нужно строк
    int maxLines = std::max({idCount, lnCount, fnCount, mnCount,
                             dobCount, ageCount, genCount, addrCount, phoneCount});

    for (int i = 0; i < maxLines; ++i) {
        std::cout << "| " << std::setw(3) << std::left << (i < idCount      ? idParts[i]   : "")
                  << "| " << std::setw(COLUMN_WIDTH) << std::left << (i < lnCount ? lnParts[i] : "")
                  << "| " << std::setw(COLUMN_WIDTH) << std::left << (i < fnCount ? fnParts[i] : "")
                  << "| " << std::setw(COLUMN_WIDTH) << std::left << (i < mnCount ? mnParts[i] : "")
                  << "| " << std::setw(COLUMN_WIDTH) << std::left << (i < dobCount? dobParts[i]: "")
                  << "| " << std::setw(COLUMN_WIDTH) << std::left << (i < ageCount? ageParts[i]: "")
                  << "| " << std::setw(COLUMN_WIDTH) << std::left << (i < genCount? genParts[i]: "")
                  << "| " << std::setw(COLUMN_WIDTH) << std::left << (i < addrCount?addrParts[i]:"")
                  << "| " << std::setw(COLUMN_WIDTH) << std::left << (i < phoneCount?phoneParts[i]:"")
                  << " |\n";
    }
}
