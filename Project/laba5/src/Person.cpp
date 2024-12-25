#include "Person.h"
#include <regex>
#include <ctime>
#include <iostream>

Person::Person() 
    : lastName(""), firstName(""), middleName(""), phone(0), gender('M') {}

Person::~Person() = default;

// Геттеры
std::string Person::getLastName() const { return lastName; }
std::string Person::getFirstName() const { return firstName; }
std::string Person::getMiddleName() const { return middleName; }
Date Person::getDateOfBirth() const { return dateOfBirth; }
Address Person::getAddress() const { return address; }
unsigned long long Person::getPhone() const { return phone; }
char Person::getGender() const { return gender; }

// Подсчет возраста
int Person::calculateAge() const {
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    int currentYear = now->tm_year + 1900;
    int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;

    int age = currentYear - dateOfBirth.getYear();
    if (dateOfBirth.getMonth() > currentMonth ||
       (dateOfBirth.getMonth() == currentMonth && dateOfBirth.getDay() > currentDay)) {
        age--;
    }
    return age;
}

// Проверка имени
bool Person::isValidName(const std::string& name) {
    // Пример: фамилия/имя/отчество начинаются с заглавной, затем строчные
    std::regex nameRegex("^[A-Z][a-z]*$");
    return std::regex_match(name, nameRegex);
}

// Проверка номера телефона
bool Person::isValidPhoneNumber(unsigned long long phoneNum) {
    // Условимся, что номер должен быть в диапазоне [89000000000..89999999999]
    return (phoneNum >= 89000000000ULL && phoneNum <= 89999999999ULL);
}
