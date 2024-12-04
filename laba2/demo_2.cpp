#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <regex>
#include <ctime>

using namespace std;

const int COLUMN_WIDTH = 15;
const int MAX_LINES = 5;
const int MAX_FRIENDS = 100; 

// Функция для разбиения строки на подстроки фиксированной длины
void splitString(const string& str, string parts[], int& count) {
    count = 0;
    int len = str.length();
    for (int i = 0; i < len; i += COLUMN_WIDTH) {
        if (count >= MAX_LINES) break; // Ограничение на макс количество строк
        parts[count++] = str.substr(i, COLUMN_WIDTH);
    }
}

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date() : day(1), month(1), year(1900) {}
    Date(int day, int month, int year) : day(day), month(month), year(year) {}
    Date(const string& dateStr) { 
        if (!parseDate(dateStr, day, month, year)) {
            day = 1;
            month = 1;
            year = 1900;
        }
    }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    void setDay(int newDay) { day = newDay; }
    void setMonth(int newMonth) { month = newMonth; }
    void setYear(int newYear) { year = newYear; }

    static bool isValid(int day, int month, int year) {
        if (year < 1900 || year > 2008) return false;
        if (month < 1 || month > 12) return false;

        // Количество дней в каждом месяце
        int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
        // Проверка на високосный год
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            daysInMonth[1] = 29;

        if (day < 1 || day > daysInMonth[month - 1]) return false;

        return true;
    }

    // Парсинг даты из строки
    static bool parseDate(const string& dateStr, int& day, int& month, int& year) {
        if (regex_match(dateStr, regex("^\\d{2}-\\d{2}-\\d{4}$"))) {
            day = stoi(dateStr.substr(0, 2));
            month = stoi(dateStr.substr(3, 2));
            year = stoi(dateStr.substr(6, 4));
            return isValid(day, month, year);
        }
        return false;
    }

    // Форматирование даты для вывода
    string toString() const {
        string formattedDate = to_string(day) + ".";
        if (month < 10) formattedDate += "0";
        formattedDate += to_string(month) + "." + to_string(year);
        return formattedDate;
    }
};

class Address {
private:
    string city;
    string street;
    int houseNumber;
    int apartmentNumber;

public:
    // Конструкторы
    Address() : city(""), street(""), houseNumber(0), apartmentNumber(0) {}
    Address(const string& city, const string& street, int houseNumber)
        : city(city), street(street), houseNumber(houseNumber), apartmentNumber(0) {}
    Address(const string& city, const string& street, int houseNumber, int apartmentNumber)
        : city(city), street(street), houseNumber(houseNumber), apartmentNumber(apartmentNumber) {}

    // Геттеры
    string getCity() const { return city; }
    string getStreet() const { return street; }
    int getHouseNumber() const { return houseNumber; }
    int getApartmentNumber() const { return apartmentNumber; }

    string getFullAddress() const {
        return city + ", " + street + ", House " + to_string(houseNumber) +
               (apartmentNumber > 0 ? ", Apt " + to_string(apartmentNumber) : "");
    }

    // Сеттеры
    void setCity(const string& newCity) { city = newCity; }
    void setStreet(const string& newStreet) { street = newStreet; }
    void setHouseNumber(int newHouseNumber) { houseNumber = newHouseNumber; }
    void setApartmentNumber(int newApartmentNumber) { apartmentNumber = newApartmentNumber; }

    // Функция для ввода адресных данных
    void inputAddress() {
        cout << "Enter city: ";
        getline(cin, city);

        cout << "Enter street: ";
        getline(cin, street);

        cout << "Enter house number: ";
        cin >> houseNumber;
        cin.ignore();

        cout << "Enter apartment number (0 if none): ";
        cin >> apartmentNumber;
        cin.ignore();
    }
};

class Friend {
private:
    string lastName;
    string firstName;
    string middleName;
    Date dateOfBirth;
    Address address;
    unsigned long long phone; // Изменено с string на unsigned long long
    char gender;

    // Функции валидации
    static bool isValidName(const string& name) {
        return regex_match(name, regex("^[A-Z][a-z]*$"));
    }

    static bool isValidPhoneNumber(unsigned long long phone) {
        // Проверка, что номер начинается с 89 и состоит из 11 цифр
        return (phone >= 89000000000ULL) && (phone <= 89999999999ULL);
    }

public:
    // Конструкторы
    Friend()
        : lastName(""), firstName(""), middleName(""), dateOfBirth(), address(), phone(0), gender('M') {}

    Friend(const string& lastName, const string& firstName)
        : lastName(lastName), firstName(firstName), middleName(""), dateOfBirth(), address(), phone(0), gender('M') {}

    Friend(const string& lastName, const string& firstName, const string& middleName,
           const Date& dateOfBirth, const Address& address, unsigned long long phone, char gender)
        : lastName(lastName), firstName(firstName), middleName(middleName),
          dateOfBirth(dateOfBirth), address(address), phone(phone), gender(gender) {}

    // Геттеры
    string getLastName() const { return lastName; }
    string getFirstName() const { return firstName; }
    string getMiddleName() const { return middleName; }
    Date getDateOfBirth() const { return dateOfBirth; }
    Address getAddress() const { return address; }
    unsigned long long getPhone() const { return phone; }
    char getGender() const { return gender; }

    // Расчет возраста
    int calculateAge() const {
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

    // Функция для ввода данных друга
    void inputFriend() {
        do {
            cout << "Enter last name: ";
            getline(cin, lastName);
            if (!isValidName(lastName)) {
                cout << "Invalid input. Please enter a valid name (first letter capitalized, no numbers).\n";
            }
        } while (!isValidName(lastName));

        do {
            cout << "Enter first name: ";
            getline(cin, firstName);
            if (!isValidName(firstName)) {
                cout << "Invalid input. Please enter a valid name (first letter capitalized, no numbers).\n";
            }
        } while (!isValidName(firstName));

        do {
            cout << "Enter middle name: ";
            getline(cin, middleName);
            if (!isValidName(middleName)) {
                cout << "Invalid input. Please enter a valid name (first letter capitalized, no numbers).\n";
            }
        } while (!isValidName(middleName));

        string dateStr;
        do {
            cout << "Enter date of birth (DD-MM-YYYY): ";
            getline(cin, dateStr);
            int day, month, year;
            if (Date::parseDate(dateStr, day, month, year)) {
                dateOfBirth.setDay(day);
                dateOfBirth.setMonth(month);
                dateOfBirth.setYear(year);
                break;
            } else {
                cout << "Invalid date or format. Please try again.\n";
            }
        } while (true);

        do {
            cout << "Enter gender (M/F): ";
            cin >> gender;
            cin.ignore();
            if (gender != 'M' && gender != 'F' && gender != 'm' && gender != 'f') {
                cout << "Invalid input. Please enter 'M' or 'F'.\n";
            } else {
                gender = toupper(gender);
                break;
            }
        } while (true);

        address.inputAddress();

        do {
            cout << "Enter phone number (89xxxxxxxxx): ";
            string phoneInput;
            getline(cin, phoneInput);
            try {
                unsigned long long phoneNum = stoull(phoneInput);
                if (isValidPhoneNumber(phoneNum)) {
                    phone = phoneNum;
                    break;
                } else {
                    cout << "Invalid phone number. Please enter a valid number starting with 89 and consisting of 11 digits.\n";
                }
            }
            catch (invalid_argument&) {
                cout << "Invalid input. Please enter numeric digits only.\n";
            }
        } while (true);
    }

    // Функция для вывода данных друга с переносом строк
    void printFriend(int id) const {
        // Разбиваем каждое поле на части
        string idParts[MAX_LINES];
        int idCount = 0;
        splitString(to_string(id), idParts, idCount);

        string lastNameParts[MAX_LINES];
        int lastNameCount = 0;
        splitString(lastName, lastNameParts, lastNameCount);

        string firstNameParts[MAX_LINES];
        int firstNameCount = 0;
        splitString(firstName, firstNameParts, firstNameCount);

        string middleNameParts[MAX_LINES];
        int middleNameCount = 0;
        splitString(middleName, middleNameParts, middleNameCount);

        string dob = dateOfBirth.toString();
        string dobParts[MAX_LINES];
        int dobCount = 0;
        splitString(dob, dobParts, dobCount);

        string ageStr = to_string(calculateAge());
        string ageParts[MAX_LINES];
        int ageCount = 0;
        splitString(ageStr, ageParts, ageCount);

        string genderStr(1, gender);
        string genderParts[MAX_LINES];
        int genderCount = 0;
        splitString(genderStr, genderParts, genderCount);

        string addressStr = address.getFullAddress();
        string addressParts[MAX_LINES];
        int addressCount = 0;
        splitString(addressStr, addressParts, addressCount);

        string phoneStr = to_string(phone);
        string phoneParts[MAX_LINES];
        int phoneCount = 0;
        splitString(phoneStr, phoneParts, phoneCount);

        int maxLines = max({idCount, lastNameCount, firstNameCount, middleNameCount,
                            dobCount, ageCount, genderCount, addressCount, phoneCount});

        for (int i = 0; i < maxLines; ++i) {
            cout << "| " << setw(3) << left << (i < idCount ? idParts[i] : "")
                 << "| " << setw(COLUMN_WIDTH) << left << (i < lastNameCount ? lastNameParts[i] : "")
                 << "| " << setw(COLUMN_WIDTH) << left << (i < firstNameCount ? firstNameParts[i] : "")
                 << "| " << setw(COLUMN_WIDTH) << left << (i < middleNameCount ? middleNameParts[i] : "")
                 << "| " << setw(COLUMN_WIDTH) << left << (i < dobCount ? dobParts[i] : "")
                 << "| " << setw(COLUMN_WIDTH) << left << (i < ageCount ? ageParts[i] : "")
                 << "| " << setw(COLUMN_WIDTH) << left << (i < genderCount ? genderParts[i] : "")
                 << "| " << setw(COLUMN_WIDTH) << left << (i < addressCount ? addressParts[i] : "")
                 << "| " << setw(COLUMN_WIDTH) << left << (i < phoneCount ? phoneParts[i] : "") << " |\n";
        }
    }
};

class FriendList {
private:
    Friend friends[MAX_FRIENDS]; // Статический массив друзей
    int count; // Текущее количество друзей

public:
    FriendList() : count(0) {}

    // Добавить друга
    void addFriend(const Friend& newFriend) {
        if (count >= MAX_FRIENDS) {
            cout << "Cannot add more friends. The list is full.\n";
            return;
        }
        friends[count++] = newFriend;
        cout << "Friend added successfully!\n";
    }

    // Удалить друга по индексу
    void deleteFriend(int index) {
        if (index < 0 || index >= count) {
            cout << "Invalid index.\n";
            return;
        }
        // Сдвигаем все элементы после удаляемого на одну позицию влево
        for (int i = index; i < count - 1; ++i) {
            friends[i] = friends[i + 1];
        }
        count--;
        cout << "Friend deleted.\n";
    }

    bool isEmpty() const {
        return count == 0;
    }

    // Вывод всех друзей 
    void printFriends() const {
        if (isEmpty()) {
            cout << "The friends list is empty.\n";
            return;
        }

        // Вывод заголовка таблицы
        cout << "| " << setw(3) << left << "ID"
             << "| " << setw(COLUMN_WIDTH) << left << "Last Name"
             << "| " << setw(COLUMN_WIDTH) << left << "First Name"
             << "| " << setw(COLUMN_WIDTH) << left << "Middle Name"
             << "| " << setw(COLUMN_WIDTH) << left << "Date of Birth"
             << "| " << setw(COLUMN_WIDTH) << left << "Age"
             << "| " << setw(COLUMN_WIDTH) << left << "Gender"
             << "| " << setw(COLUMN_WIDTH) << left << "Address"
             << "| " << setw(COLUMN_WIDTH) << left << "Phone" << " |\n";
        cout << string(8 + COLUMN_WIDTH * 8 + 3, '-') << endl;

        // Вывод каждого друга
        for (int i = 0; i < count; ++i) {
            friends[i].printFriend(i + 1);
            cout << string(8 + COLUMN_WIDTH * 8 + 3, '-') << endl;
        }
    }

    // Вывод друзей по месяцу рождения
    void printFriendsByMonth(int month) const {
        if (month < 1 || month > 12) {
            cout << "Invalid month. Please enter a number between 1 and 12.\n";
            return;
        }

        bool found = false;
        // Вывод заголовка таблицы
        cout << "| " << setw(3) << left << "ID"
             << "| " << setw(COLUMN_WIDTH) << left << "Last Name"
             << "| " << setw(COLUMN_WIDTH) << left << "First Name"
             << "| " << setw(COLUMN_WIDTH) << left << "Middle Name"
             << "| " << setw(COLUMN_WIDTH) << left << "Date of Birth"
             << "| " << setw(COLUMN_WIDTH) << left << "Age"
             << "| " << setw(COLUMN_WIDTH) << left << "Gender"
             << "| " << setw(COLUMN_WIDTH) << left << "Address"
             << "| " << setw(COLUMN_WIDTH) << left << "Phone" << " |\n";
        cout << string(8 + COLUMN_WIDTH * 8 + 3, '-') << endl;

        for (int i = 0; i < count; ++i) {
            if (friends[i].getDateOfBirth().getMonth() == month) {
                friends[i].printFriend(i + 1);
                cout << string(8 + COLUMN_WIDTH * 8 + 3, '-') << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No friends found with birthday in this month.\n";
        }
    }
};

class Application {
private:
    FriendList friendList;

    void showMenu() const {
        cout << "\nMenu:\n";
        cout << "1. Add a friend\n";
        cout << "2. Delete a friend\n";
        cout << "3. Print all friends\n";
        cout << "4. Print friends by birth month\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
    }

public:
    void run() {
        int choice;

        do {
            showMenu();
            cin >> choice;
            cin.ignore();  

            switch (choice) {
                case 1: { 
                    Friend f;
                    f.inputFriend();
                    friendList.addFriend(f);
                    break;
                }

                case 2: {
                    if (friendList.isEmpty()) { // Проверка пуст ли список
                        cout << "The friends list is empty. Nothing to delete.\n";
                        break;
                    }
                    friendList.printFriends();
                    int index;
                    cout << "Enter the ID of the friend to delete: ";
                    cin >> index;
                    cin.ignore();
                    friendList.deleteFriend(index - 1); 
                    break;
                }

                case 3: {
                    friendList.printFriends();
                    break;
                }

                case 4: {
                    int month;
                    cout << "Enter month number: ";
                    cin >> month;
                    cin.ignore();
                    friendList.printFriendsByMonth(month);
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
    }
};

int main() {
    Application app;
    app.run();
    return 0;
}

//3 лаба +\-(инкр\дикремент, сравнение, индексация массива) или *\ перегрузка - просто показать что есть перегрузка и что она работает

//Можно мне сделать вычитание: 
//1.Общее кол-во друзей -> кол-во друзей пола Ж = кол-во друзей М пола


//2 ариф операции 1 унарную и 1-2 операции сравнения использовать (8:50)
//операторы копирования и присваивания






//4 - наследование - абстракный класс как мин 2 .... 9:57 - uml диаграмму
//5 - 
//6 -


//секолько им обоим лет и какая разница в возрасте ()
//+ увел дату рождения - умене
//сравнение кто кого старше функция
// функция копирования чтобы просто вызывались наши версии