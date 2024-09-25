#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Структура для хранения информации о друге
struct Friend {
    string lastName;     // Фамилия
    string firstName;    // Имя
    string middleName;   // Отчество
    int day;             // День рождения
    int month;           // Месяц рождения
    int year;            // Год рождения
    string address;      // Адрес
    string phone;        // Телефон
};

// Функция для ввода данных о друге
void inputFriend(Friend &f) {
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
void printFriend(const Friend &f, int index) {
    cout << setw(6) << index << setw(12) << f.lastName << setw(12) << f.firstName << setw(15) << f.middleName
         << " | " << setw(2) << setfill('0') << f.day << "." << setw(2) << setfill('0') << f.month << "." << f.year 
         << " | " << setw(20) << f.address << " | " << setw(15) << f.phone << endl;
}

// Функция для печати всех друзей
void printAllFriends(const vector<Friend> &friends) {
    if (friends.empty()) {
        cout << "[INFO] Список друзей пуст.\n";
        return;
    }
    
    cout << left << setw(6) << "Индекс" << setw(12) << "Фамилия" << setw(12) << "Имя" << setw(15) << "Отчество"
         << " | Дата рождения | " << setw(20) << "Адрес" << " | " << setw(15) << "Телефон" << endl;
    cout << string(85, '-') << endl;
    for (size_t i = 0; i < friends.size(); ++i) {
        printFriend(friends[i], i + 1);
    }
}

// Функция для поиска и вывода друзей, родившихся в заданном месяце
void findFriendsByMonth(const vector<Friend> &friends, int month) {
    bool found = false;
    cout << "Друзья, родившиеся в месяце " << month << ":\n";
    for (size_t i = 0; i < friends.size(); ++i) {
        if (friends[i].month == month) {
            printFriend(friends[i], i + 1);
            found = true;
        }
    }
    if (!found) {
        cout << "[INFO] Нет друзей, родившихся в этом месяце.\n";
    }
}

// Функция для удаления друга по индексу
void removeFriend(vector<Friend> &friends, int index) {
    if (index < 0 || index >= friends.size()) {
        cout << "[ERROR] Неверный индекс.\n";
        return;
    }
    friends.erase(friends.begin() + index);
    cout << "[INFO] Друг удалён.\n";
}

// Печать меню
void printMenu() {
    cout << "[1] Добавить друга\n";
    cout << "[2] Удалить друга\n";
    cout << "[3] Показать всех друзей\n";
    cout << "[4] Найти друзей по месяцу рождения\n";
    cout << "[0] Выйти\n";
    cout << " -> ";
}

int main() {
    vector<Friend> friends;
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
                cout << "[INFO] Друг добавлен.\n";
                break;
            }
            case 2: {  // Удалить друга
                if (friends.empty()) {
                    cout << "[INFO] Список друзей пуст.\n";
                } else {
                    int index;
                    cout << "Введите индекс друга для удаления (1 - " << friends.size() << "): ";
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
                    cout << "[INFO] Список друзей пуст.\n";
                } else {
                    int month;
                    cout << "Введите месяц (1-12): ";
                    cin >> month;
                    findFriendsByMonth(friends, month);
                }
                break;
            }
            case 0:
                cout << "[INFO] Программа завершена.\n";
                break;
            default:
                cout << "[ERROR] Неверная команда.\n";
        }
    } while (command != 0);
    
    return 0;
}
