#include "Address.h"
#include <iostream>

Address::Address() : city(""), street(""), houseNumber(0), apartmentNumber(0) {}

Address::Address(const std::string& c, const std::string& s, int h)
    : city(c), street(s), houseNumber(h), apartmentNumber(0) {}

Address::Address(const std::string& c, const std::string& s, int h, int a)
    : city(c), street(s), houseNumber(h), apartmentNumber(a) {}

Address::Address(const Address& other)
    : city(other.city), street(other.street),
      houseNumber(other.houseNumber), apartmentNumber(other.apartmentNumber) {}

Address& Address::operator=(const Address& other) {
    if (this != &other) {
        city = other.city;
        street = other.street;
        houseNumber = other.houseNumber;
        apartmentNumber = other.apartmentNumber;
    }
    return *this;
}

std::string Address::getCity() const { return city; }
std::string Address::getStreet() const { return street; }
int Address::getHouseNumber() const { return houseNumber; }
int Address::getApartmentNumber() const { return apartmentNumber; }

std::string Address::getFullAddress() const {
    std::string result = city + ", " + street + ", House " + std::to_string(houseNumber);
    if (apartmentNumber > 0) {
        result += ", Apt " + std::to_string(apartmentNumber);
    }
    return result;
}

void Address::setCity(const std::string& c) { city = c; }
void Address::setStreet(const std::string& s) { street = s; }
void Address::setHouseNumber(int h) { houseNumber = h; }
void Address::setApartmentNumber(int a) { apartmentNumber = a; }

void Address::inputAddress() {
    std::cout << "Enter city: ";
    std::getline(std::cin, city);

    std::cout << "Enter street: ";
    std::getline(std::cin, street);

    std::cout << "Enter house number: ";
    std::cin >> houseNumber;
    std::cin.ignore();

    std::cout << "Enter apartment number (0 if none): ";
    std::cin >> apartmentNumber;
    std::cin.ignore();
}
