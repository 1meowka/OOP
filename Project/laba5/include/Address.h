#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address {
private:
    std::string city;
    std::string street;
    int houseNumber;
    int apartmentNumber;

public:
    Address();
    Address(const std::string& c, const std::string& s, int h);
    Address(const std::string& c, const std::string& s, int h, int a);
    Address(const Address& other);

    Address& operator=(const Address& other);

    std::string getCity() const;
    std::string getStreet() const;
    int getHouseNumber() const;
    int getApartmentNumber() const;

    std::string getFullAddress() const;

    void setCity(const std::string& c);
    void setStreet(const std::string& s);
    void setHouseNumber(int h);
    void setApartmentNumber(int a);

    void inputAddress();
};

#endif // ADDRESS_H
