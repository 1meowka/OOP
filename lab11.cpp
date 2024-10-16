#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_FRIENDS = 100; // Максимальное количество друзей
const int COLUMN_WIDTH = 15; // Ширина колонки

struct Friend {
    string lastName;
    string firstName;
    string middleName;
    int day;
    int month;
    int year;
    string address;
    string phone;
};

Friend friends[MAX_FRIENDS];
int friend_count = 0; // Текущее количество друзей

int get_friend_count() {
    return friend_count;
}

void add_friend(const Friend& new_friend) {
    if (get_friend_count() < MAX_FRIENDS) {
        friends[friend_count] = new_friend;
        friend_count++;
    } else {
        cout << "Невозможно добавить больше друзей.\n";
    }
}

void delete_friend(int index) {
    if (index >= 0 && index < get_friend_count()) {
        for (int i = index; i < friend_count - 1; ++i) {
            friends[i] = friends[i + 1]; 
        }
        friend_count--; 
    } else {
        cout << "Неправильный ввод.\n";
    }
}

// Функция для печати таблицы друзей
void print_friends() {
    if (get_friend_count() == 0) {
        cout << "Список друзей пуст.\n";
        return;
    }

    // Заголовок таблицы
    cout << "| " << setw(COLUMN_WIDTH) << left << "fam"
         << "| " << setw(COLUMN_WIDTH) << left << "name"
         << "| " << setw(COLUMN_WIDTH) << left << "middlename"
         << "| " << setw(COLUMN_WIDTH) << left << "bithday"
         << "| " << setw(COLUMN_WIDTH) << left << "sity"
         << "| " << setw(COLUMN_WIDTH) << left << "number" << " |" << endl;
    cout << string(100, '-') << endl;

    for (int i = 0; i < get_friend_count(); ++i) {
        cout << "| " << setw(COLUMN_WIDTH) << left << friends[i].lastName
             << "| " << setw(COLUMN_WIDTH) << left << friends[i].firstName
             << "| " << setw(COLUMN_WIDTH) << left << friends[i].middleName
             << "| " << setw(COLUMN_WIDTH) << left << friends[i].day << "."
             << (friends[i].month < 10 ? "0" : "") << friends[i].month << "." << friends[i].year
             << "| " << setw(COLUMN_WIDTH) << left << friends[i].address
             << "| " << setw(COLUMN_WIDTH) << left << friends[i].phone << " |" << endl;
        cout << string(100, '-') << endl;
    }
}

// Функция для поиска друзей по месяцу рождения
void find_friends_by_month(int month) {
    bool found = false;

    // Заголовок таблицы (выводим только если есть совпадения)
    for (int i = 0; i < get_friend_count(); ++i) {
        if (friends[i].month == month) {
            if (!found) {
                cout << "| " << setw(COLUMN_WIDTH) << left << "fam"
                     << "| " << setw(COLUMN_WIDTH) << left << "name"
                     << "| " << setw(COLUMN_WIDTH) << left << "middlename"
                     << "| " << setw(COLUMN_WIDTH) << left << "bithday"
                     << "| " << setw(COLUMN_WIDTH) << left << "sity"
                     << "| " << setw(COLUMN_WIDTH) << left << "number" << " |" << endl;
                cout << string(100, '-') << endl;
                found = true;
            }

            // Выводим только тех друзей, у кого месяц рождения совпадает
            cout << "| " << setw(COLUMN_WIDTH) << left << friends[i].lastName
                 << "| " << setw(COLUMN_WIDTH) << left << friends[i].firstName
                 << "| " << setw(COLUMN_WIDTH) << left << friends[i].middleName
                 << "| " << setw(COLUMN_WIDTH) << left << friends[i].day << "."
                 << (friends[i].month < 10 ? "0" : "") << friends[i].month << "." << friends[i].year
                 << "| " << setw(COLUMN_WIDTH) << left << friends[i].address
                 << "| " << setw(COLUMN_WIDTH) << left << friends[i].phone << " |" << endl;
            cout << string(100, '-') << endl;
        }
    }

    if (!found) {
        cout << "Друзей с месяцем рождения " << month << " не найдено.\n";
    }
}

int main() {
    int choice;

    while (true) {
        cout << "1. Добавить друга\n";
        cout << "2. Удалить друга\n";
        cout << "3. Вывод всех друзей\n";
        cout << "4. Поиск по месяцу рождения\n";
        cout << "5. Выход\n";
        cout << "Введите свой выбор: ";
        cin >> choice;

        if (choice == 1) {
            Friend new_friend;
            cout << "Введите фамилию: ";
            cin.ignore();
            getline(cin, new_friend.lastName);
            cout << "Введите имя: ";
            getline(cin, new_friend.firstName);
            cout << "Введите отчество: ";
            getline(cin, new_friend.middleName);
            cout << "Введите день рождения: ";
            cin >> new_friend.day;
            cout << "Введите месяц рождения: ";
            cin >> new_friend.month;
            cout << "Введите год рождения: ";
            cin >> new_friend.year;
            cin.ignore();
            cout << "Введите город: ";
            getline(cin, new_friend.address);
            cout << "Введите телефон: ";
            getline(cin, new_friend.phone);

            add_friend(new_friend);
            cout << "Друг добавлен!\n\n";

        } else if (choice == 2) {
            int index;
            cout << "Для удаления введите номер друга: ";
            cin >> index;
            delete_friend(index - 1);
        } else if (choice == 3) {
            print_friends();
        } else if (choice == 4) {
            int month;
            cout << "Введите месяц (1-12): ";
            cin >> month;
            find_friends_by_month(month);
        } else if (choice == 5) {
            break;
        } else {
            cout << "Неправильный ввод, пожалуйста повторите.\n";
        }
    }

    return 0;
}
