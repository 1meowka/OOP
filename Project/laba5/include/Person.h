#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "Date.h"
#include "Address.h"

class Person {
protected:
    std::string lastName;
    std::string firstName;
    std::string middleName;
    Date dateOfBirth;
    Address address;
    unsigned long long phone;
    char gender;

public:
    Person();
    virtual ~Person();

    virtual void printRole() const = 0;

    // Геттеры
    std::string getLastName() const;
    std::string getFirstName() const;
    std::string getMiddleName() const;
    Date getDateOfBirth() const;
    Address getAddress() const;
    unsigned long long getPhone() const;
    char getGender() const;

    // Подсчет возраста на основе текущей даты
    int calculateAge() const;

    // Проверка имени (валидность)
    static bool isValidName(const std::string& name);

    // Проверка номера телефона
    static bool isValidPhoneNumber(unsigned long long phone);
};

#endif // PERSON_H
