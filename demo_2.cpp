#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <regex>
#include <ctime> // для того чтобы получить тек дату

using namespace std;

const int MAX_FRIENDS = 100;
const int COLUMN_WIDTH = 15;

class Friend {
    string lastName;
    string firstName;
    string middleName;
    int day;
    int month;
    int year;
    string address;
    string phone;
    char gender;

    class Address {
        string city;
        string street;
        int houseNumber;
        int apartmentNumber;

    public:
        Address(const string& city = "", const string& street = "", int houseNumber = 0, int apartmentNumber = 0)
            : city(city), street(street), houseNumber(houseNumber), apartmentNumber(apartmentNumber) {}

        string getFullAddress() const {
            return city + ", " + street + ", House " + to_string(houseNumber) +
                   (apartmentNumber > 0 ? ", Apt " + to_string(apartmentNumber) : "");
        }

        // Геттеры и сеттеры для вложенного класса
        void setCity(const string& newCity) { city = newCity; }
        void setStreet(const string& newStreet) { street = newStreet; }
        void setHouseNumber(int newHouseNumber) { houseNumber = newHouseNumber; }
        void setApartmentNumber(int newApartmentNumber) { apartmentNumber = newApartmentNumber; }
    };

public:
    // Конструктор по умолчанию
    Friend() : lastName(""), firstName(""), middleName(""), day(1), month(1), year(1900), address(""), phone(""), gender('M') {}

    // Конструктор с минимальным набором параметров
    Friend(const string& lastName, const string& firstName) 
        : lastName(lastName), firstName(firstName), middleName(""), day(1), month(1), year(1900), address(""), phone(""), gender('M') {}

    // Полный конструктор
    Friend(const string& lastName, const string& firstName, const string& middleName,
           int day, int month, int year, const string& address, const string& phone, char gender)
        : lastName(lastName), firstName(firstName), middleName(middleName), day(day), month(month), year(year), 
          address(address), phone(phone), gender(gender) {}

    // Геттеры
    string getLastName() const { return lastName; }
    string getFirstName() const { return firstName; }
    string getMiddleName() const { return middleName; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    string getAddress() const { return address; }
    string getPhone() const { return phone; }
    char getGender() const { return gender; }

    // Метод для расчета возраста
    int calculateAge() const {
        time_t t = time(nullptr);
        tm* now = localtime(&t);

        int currentYear = now->tm_year + 1900;
        int currentMonth = now->tm_mon + 1;
        int currentDay = now->tm_mday;

        int age = currentYear - year;
        if (month > currentMonth || (month == currentMonth && day > currentDay)) {
            age--;  // Уменьшить возраст, если день рождения еще не наступил
        }
        return age;
    }

    // Проверка корректности даты рождения
    bool isValidDate() const {
        if (year < 1900 || year > 2008) return false;
        if (month < 1 || month > 12) return false;

        // Проверка количества дней в месяце
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            daysInMonth[1] = 29; // Високосный год
        }
        return day > 0 && day <= daysInMonth[month - 1];
    }

    static string formatPhoneNumber(const string& phone) {
        return "8(" + phone.substr(1, 3) + ") " + phone.substr(4, 3) + "-" + phone.substr(7, 2) + "-" + phone.substr(9, 2);
    }

    static bool isValidPhoneNumber(const string& phone) {
        return regex_match(phone, regex("^89\\d{9}$"));
    }

    static bool parseDate(const string& dateStr, int& day, int& month, int& year) {
        if (regex_match(dateStr, regex("^\\d{2}-\\d{2}-\\d{4}$"))) {
            day = stoi(dateStr.substr(0, 2));
            month = stoi(dateStr.substr(3, 2));
            year = stoi(dateStr.substr(6, 4));
            return true;
        }
        return false;
    }

    static bool isValidName(const string& name) {
        return regex_match(name, regex("^[A-Z][a-z]*$")); // Первая буква заглавная, остальные - строчные
    }
};

class FriendList {
    Friend friends[MAX_FRIENDS];
    int friend_count;

public:
    FriendList() : friend_count(0) {}

    // Добавление друга
    void addFriend(const Friend& newFriend) {
        if (friend_count < MAX_FRIENDS) {
            friends[friend_count++] = newFriend;
            cout << "Friend added successfully!\n";
        } else {
            cout << "Maximum friends reached!\n";
        }
    }

    // Удаление друга
    void deleteFriend(int index) {
        if (index >= 0 && index < friend_count) {
            for (int i = index; i < friend_count - 1; ++i) {
                friends[i] = friends[i + 1];
            }
            friend_count--;
            cout << "Friend deleted.\n";
        } else {
            cout << "Invalid index.\n";
        }
    }

    // Печать всех друзей
    void printFriends() const {
        if (friend_count == 0) {
            cout << "The friends list is empty.\n";
            return;
        }

        cout << "| " << setw(COLUMN_WIDTH) << left << "Lastname"
             << "| " << setw(COLUMN_WIDTH) << left << "Name"
             << "| " << setw(COLUMN_WIDTH) << left << "Middle name"
             << "| " << setw(COLUMN_WIDTH) << left << "Date of birth"
             << "| " << setw(COLUMN_WIDTH) << left << "Age"
             << "| " << setw(COLUMN_WIDTH) << left << "Gender"
             << "| " << setw(COLUMN_WIDTH) << left << "City"
             << "| " << setw(COLUMN_WIDTH) << left << "Phone number" << " |\n";
        cout << string(130, '-') << endl;

        for (int i = 0; i < friend_count; ++i) {
            const Friend& f = friends[i];
            cout << "| " << setw(COLUMN_WIDTH) << left << f.getLastName()
                 << "| " << setw(COLUMN_WIDTH) << left << f.getFirstName()
                 << "| " << setw(COLUMN_WIDTH) << left << f.getMiddleName()
                 << "| " << setw(COLUMN_WIDTH) << left
                 << (to_string(f.getDay()) + "." + (f.getMonth() < 10 ? "0" : "") + to_string(f.getMonth()) + "." + to_string(f.getYear()))
                 << "| " << setw(COLUMN_WIDTH) << left << f.calculateAge()
                 << "| " << setw(COLUMN_WIDTH) << left << f.getGender()
                 << "| " << setw(COLUMN_WIDTH) << left << f.getAddress()
                 << "| " << setw(COLUMN_WIDTH) << left << f.getPhone() << " |\n";
            cout << string(130, '-') << endl;
        }
    }

    // Поиск друзей по месяцу рождения
    void printFriendsByMonth(int month) const {
        if (month < 1 || month > 12) {
            cout << "Invalid month. Please enter a number between 1 and 12.\n";
            return;
        }

        bool found = false;
        for (int i = 0; i < friend_count; ++i) {
            if (friends[i].getMonth() == month) {
                if (!found) {
                    found = true;
                    cout << "| " << setw(COLUMN_WIDTH) << left << "Lastname"
                         << "| " << setw(COLUMN_WIDTH) << left << "Name"
                         << "| " << setw(COLUMN_WIDTH) << left << "Middle name"
                         << "| " << setw(COLUMN_WIDTH) << left << "Date of birth"
                         << "| " << setw(COLUMN_WIDTH) << left << "Age"
                         << "| " << setw(COLUMN_WIDTH) << left << "Gender"
                         << "| " << setw(COLUMN_WIDTH) << left << "City"
                         << "| " << setw(COLUMN_WIDTH) << left << "Phone number" << " |\n";
                    cout << string(130, '-') << endl;
                }
                cout << "| " << setw(COLUMN_WIDTH) << left << friends[i].getLastName()
                     << "| " << setw(COLUMN_WIDTH) << left << friends[i].getFirstName()
                     << "| " << setw(COLUMN_WIDTH) << left << friends[i].getMiddleName()
                     << "| " << setw(COLUMN_WIDTH) << left
                     << (to_string(friends[i].getDay()) + "." + (friends[i].getMonth() < 10 ? "0" : "") + to_string(friends[i].getMonth()) + "." + to_string(friends[i].getYear()))
                     << "| " << setw(COLUMN_WIDTH) << left << friends[i].calculateAge()
                     << "| " << setw(COLUMN_WIDTH) << left << friends[i].getGender()
                     << "| " << setw(COLUMN_WIDTH) << left << friends[i].getAddress()
                     << "| " << setw(COLUMN_WIDTH) << left << friends[i].getPhone() << " |\n";
                cout << string(130, '-') << endl;
            }
        }
        if (!found) {
            cout << "No friends found with birthday in this month.\n";
        }
    }
};

// Функция для ввода данных с проверкой
void inputValidName(string& name, const string& fieldName) {
    do {
        cout << "Enter " << fieldName << ": ";
        getline(cin, name);
        if (!Friend::isValidName(name)) {
            cout << "Invalid input. Please enter a valid name (first letter capitalized and no numbers).\n";
        }
    } while (!Friend::isValidName(name));
}

void inputAddress(string& city, string& street, int& houseNumber, int& apartmentNumber) {
    cout << "Enter city: ";
    getline(cin, city);

    cout << "Enter street: ";
    getline(cin, street);

    cout << "Enter house number: ";
    cin >> houseNumber;
    cin.ignore(); // очищаем буфер после ввода числа

    cout << "Enter apartment number (only integer): ";
    cin >> apartmentNumber;
    cin.ignore(); // очищаем буфер после ввода числа
}

void inputValidDate(int& day, int& month, int& year) {
    string dateStr;
    do {
        cout << "Enter date of birth (DD-MM-YYYY): ";
        getline(cin, dateStr);
        if (Friend::parseDate(dateStr, day, month, year)) {
            Friend temp("", "", "", day, month, year, "", "", 'M');
            if (!temp.isValidDate()) {
                cout << "Invalid date. Please try again.\n";
            } else {
                break;
            }
        } else {
            cout << "Invalid format. Please use DD-MM-YYYY.\n";
        }
    } while (true);
}

void inputValidPhone(string& phone) {
    do {
        cout << "Enter phone number (89xxxxxxxxx): ";
        getline(cin, phone);
        if (!Friend::isValidPhoneNumber(phone)) {
            cout << "Invalid phone number. Please enter a valid phone number starting with 89 and 11 digits.\n";
        }
    } while (!Friend::isValidPhoneNumber(phone));
}

void showMenu() {
    cout << "\nMenu:\n";
    cout << "1. Add a friend\n";
    cout << "2. Delete a friend\n";
    cout << "3. Print all friends\n";
    cout << "4. Print friends by birth month\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    FriendList list;
    int choice;
    string lastName, firstName, middleName, city, street, phone, address;
    int day, month, year, houseNumber, apartmentNumber;
    char gender;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();  // Очистка буфера после ввода числа

        switch (choice) {
            case 1: { // Добавить друга
                inputValidName(lastName, "last name");
                inputValidName(firstName, "first name");
                inputValidName(middleName, "middle name");
                inputValidDate(day, month, year);
                
                cout << "Enter gender (M/F): ";
                cin >> gender;
                cin.ignore();  // Очистка буфера после ввода символа

                inputAddress(city, street, houseNumber, apartmentNumber);

                inputValidPhone(phone);

                // Формирование адреса
                address = city + ", " + street + ", " + to_string(houseNumber) + ", Apt. " + to_string(apartmentNumber);

                // Создание объекта Friend и добавление в список
                Friend f(lastName, firstName, middleName, day, month, year, address, phone, gender);
                list.addFriend(f);

                break;
            }

            case 2: {
                list.printFriends();
                int index;
                cout << "Enter index of friend to delete: ";
                cin >> index;
                list.deleteFriend(index - 1); // Индексы начинаются с 1
                break;
            }

            case 3: {
                list.printFriends();
                break;
            }

            case 4: {
                cout << "Enter month number: ";
                cin >> month;
                list.printFriendsByMonth(month);
                break;
            }

            case 5: {
                cout << "Exiting the program.\n";
                break;
            }

            default: {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    } while (choice != 5);
    return 0;
}


//добавить вложенный класс с Адресом - страна, город, улица\мкр, дом, кв., для того чтобы код был в стиле ООП
//форматирование таблицы чтоб не было смещения