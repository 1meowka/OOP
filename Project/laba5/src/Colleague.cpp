#include "Colleague.h"
#include <iostream>

Colleague::Colleague() : Person() {}

void Colleague::printRole() const {
    std::cout << "Role: Colleague";
}

void Colleague::inputColleague() {
    // lastName
    do {
        std::cout << "Enter last name: ";
        std::getline(std::cin, lastName);
        if (!isValidName(lastName)) {
            std::cout << "Invalid input. Please enter a valid name.\n";
        }
    } while (!isValidName(lastName));

    // firstName
    do {
        std::cout << "Enter first name: ";
        std::getline(std::cin, firstName);
        if (!isValidName(firstName)) {
            std::cout << "Invalid input. Please enter a valid name.\n";
        }
    } while (!isValidName(firstName));

    // middleName
    do {
        std::cout << "Enter middle name: ";
        std::getline(std::cin, middleName);
        if (!isValidName(middleName)) {
            std::cout << "Invalid input. Please enter a valid name.\n";
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
            std::cout << "Invalid date or format. Please try again.\n";
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
