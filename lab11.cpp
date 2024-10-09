#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Структура для хранения информации о друге
struct Friend 
{
    string lastName;     
    string firstName;    
    string middleName;   
    int day;             
    int month;           
    int year;            
    string address;      
    string phone;       
};

// Функция для ввода данных о друге
void inputFriend(Friend &f) 
{
    cout << "Введите данные о друге:\n";
    cout << "  Фамилия: ";
    getline(cin, f.lastName);
    cout << "  Имя: ";
    getline(cin, f.firstName);
    cout << "  Отчество: ";
    getline(cin, f.middleName);
    cout << "  День рождения (число): ";
    cin >> f.day;
    cout << "  Месяц рождения (число): ";
    cin >> f.month;
    cout << "  Год рождения: ";
    cin >> f.year;
    cin.ignore();  // Очищаем буфер
    cout << "  Адрес(Sity): ";
    getline(cin, f.address);
    cout << "  Телефон: ";
    getline(cin, f.phone);
}

// Функция для печати информации о друге
void printFriend(const Friend &f) {
    cout << setw(10) << f.lastName << " | " << setw(10) << f.firstName << " | " << setw(10) << f.middleName 
         << " | " << setw(2) << f.day << "." << setw(2) << f.month << "." << f.year 
         << " | " << setw(15) << f.address << " | " << f.phone << endl;
}

// Функция для печати всех друзей
void printAllFriends(const list<Friend> &friends) {
    if (friends.empty()) {
        cout << "[INFORMATION] --- Список друзей пуст.\n";
        return;
    }
    
    cout << left << setw(10) << "Фамилия" << setw(10) << " | Имя" << setw(10) << " | Отчество"
         << " | Дата рождения | " << setw(15) << "Адрес" << " | Телефон" << endl;
    cout << string(80, '-') << endl;
    for (const auto &f : friends) {
        printFriend(f);
    }
}

// Функция для поиска и вывода друзей, родившихся в заданном месяце
void findFriendsByMonth(const list<Friend> &friends, int month) 
{
    bool found = false;
    cout << "Друзья, родившиеся в месяце " << month << ":\n";
    for (const auto &f : friends) {
        if (f.month == month) {
            printFriend(f);
            found = true;
        }
    }
    if (!found) {
        cout << "[INFORMATION] --- Нет друзей, родившихся в этом месяце.\n";
    }
}

// Функция для удаления друга по индексу
void removeFriend(list<Friend> &friends, int index) {
    if (index < 0 || index >= friends.size()) {
        cout << "[ERROR] Неверный индекс.\n";
        return;
    }
    auto it = friends.begin();
    advance(it, index);  // Переходим на нужный индекс
    friends.erase(it);
    cout << "[INFORMATION] --- Друг удалён.\n";
}

// Печатаем менюшку
void printMenu() {
    cout << "[1] Добавить друга\n";
    cout << "[2] Удалить друга\n";
    cout << "[3] Показать всех друзей\n";
    cout << "[4] Найти друзей по месяцу рождения\n";
    cout << "[0] Выйти\n";
    cout << " Введите-> ";
}

int main() {
    list<Friend> friends;
    int command;
    
    do {
        printMenu();
        cin >> command;
        cin.ignore();  // Очищаем буфер
        
        switch (command) {
            case 1: {  // Добавить друга
                Friend newFriend;
                inputFriend(newFriend);
                friends.push_back(newFriend);
                cout << "[INFORMATION] --- Друг добавлен.\n";
                break;
            }
            case 2: {  // Удалить друга
                if (friends.empty()) {
                    cout << "[INFORMATION] --- Список друзей пуст.\n";
                } else {
                    int index;
                    cout << "Введите номер друга для удаления (1 - " << friends.size() << "): ";
                    cin >> index;
                    removeFriend(friends, index - 1);
                }
                break;
            }
            case 3: {  // Показать всех друзей
                printAllFriends(friends);
                break;
            }
            case 4: {  // Найти друзей по месяцу рождения
                if (friends.empty()) {
                    cout << "[INFORMATION] --- Список друзей пуст.\n";
                } else {
                    int month;
                    cout << "Введите месяц (1-12): ";
                    cin >> month;
                    findFriendsByMonth(friends, month);
                }
                break;
            }
            case 0:
                cout << "[INFORMATION] --- Программа завершена.\n";
                break;
            default:
                cout << "[ERROR] Неверная команда.\n";
        }
    } while (command != 0);
    return 0;
}






#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Структура для хранения данных о друге
struct Friend 
{
    string lastName;     
    string firstName;    
    string middleName;   
    int day;             
    int month;           
    int year;            
    string address;      
    string phone;       
};

// Функция для ввода данных о друге
void inputFriend(Friend &f) 
{
    cout << "Введите данные о друге:\n";
    cout << "  Фамилия: ";
    getline(cin, f.lastName);
    cout << "  Имя: ";
    getline(cin, f.firstName);
    cout << "  Отчество: ";
    getline(cin, f.middleName);
    cout << "  День рождения (число): ";
    cin >> f.day;
    cout << "  Месяц рождения (число): ";
    cin >> f.month;
    cout << "  Год рождения: ";
    cin >> f.year;
    cin.ignore();  // Очищаем буфер
    cout << "  Адрес (Город): ";
    getline(cin, f.address);
    cout << "  Телефон: ";
    getline(cin, f.phone);
}

// Функция для печати информации о друге
void printFriend(const Friend &f) 
{
    cout << setw(12) << left << f.lastName << " | " 
         << setw(12) << left << f.firstName << " | " 
         << setw(12) << left << f.middleName << " | " 
         << setfill('0') << setw(2) << right << f.day << "."
         << setw(2) << f.month << "." << f.year 
         << setfill(' ') << " | " << setw(20) << left << f.address 
         << " | " << f.phone << endl;
}

// Функция для печати всех друзей
void printAllFriends(const list<Friend> &friends) 
{
    if (friends.empty()) 
    {
        cout << "[INFORMATION] --- Список друзей пуст.\n";
        return;
    }

    cout << left << setw(12) << "Фамилия" << " | " 
         << setw(12) << "Имя" << " | " 
         << setw(12) << "Отчество" << " | " 
         << "Дата рождения  | " 
         << setw(20) << "Адрес" << " | Телефон" << endl;
    cout << string(80, '-') << endl;

    for (const auto &f : friends) 
    {
        printFriend(f);
    }
}

// Функция для поиска и вывода друзей, родившихся в заданном месяце
void findFriendsByMonth(const list<Friend> &friends, int month) 
{
    bool found = false;
    cout << "Друзья, родившиеся в месяце " << month << ":\n";

    for (const auto &f : friends) 
    {
        if (f.month == month) 
        {
            printFriend(f);
            found = true;
        }
    }

    if (!found) 
    {
        cout << "[INFORMATION] --- Нет друзей, которые родились в этом месяце.\n";
    }
}

// Функция для удаления друга по индексу
void removeFriend(list<Friend> &friends, int index) 
{
    if (index < 0 || index >= friends.size()) 
    {
        cout << "[ERROR] Неверный индекс. Пожалуйста, введите корректное значение.\n";
        return;
    }

    auto it = friends.begin();
    advance(it, index);  // Переходим на нужный индекс
    friends.erase(it);
    cout << "[INFORMATION] --- Друг удалён :(\n";
}

// Функция для печати меню
void printMenu() 
{
    cout << "[1] Добавить друга\n";
    cout << "[2] Удалить друга\n";
    cout << "[3] Показать всех друзей\n";
    cout << "[4] Найти друзей по месяцу рождения\n";
    cout << "[0] Выйти\n";
    cout << "Введите -> ";
}

int main() 
{
    list<Friend> friends;
    int command;
    
    do 
    {
        printMenu();
        cin >> command;
        cin.ignore();  // Очищаем буфер

        switch (command) 
        {
            case 1: 
            {  // Добавить друга
                Friend newFriend;
                inputFriend(newFriend);
                friends.push_back(newFriend);
                cout << "[INFORMATION] --- Друг добавлен :)\n";
                break;
            }
            case 2: 
            {  // Удалить друга
                if (friends.empty()) 
                {
                    cout << "[INFORMATION] --- Список друзей пуст.\n";
                } 
                else 
                {
                    int index;
                    cout << "Введите номер друга для удаления (1 - " << friends.size() << "): ";
                    cin >> index;
