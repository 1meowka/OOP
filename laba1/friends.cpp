#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_FRIENDS = 100; 
const int COLUMN_WIDTH = 15;

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
int friend_count = 0; 

int get_friend_count() {
    return friend_count;
}

void add_friend(const Friend& new_friend) {
    if (get_friend_count() < MAX_FRIENDS) {
        friends[friend_count] = new_friend;
        friend_count++;
    } else {
        cout << "You can't to add a friend, because max_friend=100\n";
    }
}

void delete_friend(int index) {
    if (index >= 0 && index < get_friend_count()) {
        for (int i = index; i < friend_count - 1; ++i) {
            friends[i] = friends[i + 1]; 
        }
        friend_count--; 
    } else {
        cout << "Error\n";
    }
}

// разбивает строку на подстроки фиксированной длины
int split_string(const string& str, string result[], int width) {
    int count = 0;
    for (size_t i = 0; i < str.size(); i += width) {
        result[count++] = str.substr(i, width);
    }
    return count;
}

// печатаем друзей
void print_friends() {
    if (get_friend_count() == 0) {
        cout << "The friends list is empty\n";
        return;
    }

    cout << "| " << setw(COLUMN_WIDTH) << left << "Lastname"
         << "| " << setw(COLUMN_WIDTH) << left << "Name"
         << "| " << setw(COLUMN_WIDTH) << left << "Middle name"
         << "| " << setw(COLUMN_WIDTH) << left << "Date of birth"
         << "| " << setw(COLUMN_WIDTH) << left << "Sity"
         << "| " << setw(COLUMN_WIDTH) << left << "Phone number" << " |" << endl;
    cout << string(100, '-') << endl;

    for (int i = 0; i < get_friend_count(); ++i) {
        string lastNameLines[10], firstNameLines[10], middleNameLines[10], addressLines[10], phoneLines[10];
        int lastNameLineCount = split_string(friends[i].lastName, lastNameLines, COLUMN_WIDTH);
        int firstNameLineCount = split_string(friends[i].firstName, firstNameLines, COLUMN_WIDTH);
        int middleNameLineCount = split_string(friends[i].middleName, middleNameLines, COLUMN_WIDTH);
        int addressLineCount = split_string(friends[i].address, addressLines, COLUMN_WIDTH);
        int phoneLineCount = split_string(friends[i].phone, phoneLines, COLUMN_WIDTH);

        //пишем максимальное количество строк для данного друга
        int max_lines = max(max(lastNameLineCount, firstNameLineCount), max(middleNameLineCount, max(addressLineCount, phoneLineCount)));

        for (int line = 0; line < max_lines; ++line) {
            cout << "| ";

            if (line < lastNameLineCount) {
                cout << setw(COLUMN_WIDTH) << left << lastNameLines[line];
            } else {
                cout << setw(COLUMN_WIDTH) << " ";
            }

            cout << "| ";

            if (line < firstNameLineCount) {
                cout << setw(COLUMN_WIDTH) << left << firstNameLines[line];
            } else {
                cout << setw(COLUMN_WIDTH) << " ";
            }

            cout << "| ";

            if (line < middleNameLineCount) {
                cout << setw(COLUMN_WIDTH) << left << middleNameLines[line];
            } else {
                cout << setw(COLUMN_WIDTH) << " ";
            }

            cout << "| ";
            if (line == 0) {
                // форматируем дату рождения строго в пределах колонки
                string birth_date = to_string(friends[i].day) + "." + 
                                    (friends[i].month < 10 ? "0" : "") + to_string(friends[i].month) + "." + 
                                    to_string(friends[i].year);
                cout << setw(COLUMN_WIDTH) << left << birth_date;
            } else {
                cout << setw(COLUMN_WIDTH) << " "; 
            }

            cout << "| ";

            if (line < addressLineCount) {
                cout << setw(COLUMN_WIDTH) << left << addressLines[line];
            } else {
                cout << setw(COLUMN_WIDTH) << " ";
            }

            cout << "| ";

            if (line < phoneLineCount) {
                cout << setw(COLUMN_WIDTH) << left << phoneLines[line];
            } else {
                cout << setw(COLUMN_WIDTH) << " ";
            }

            cout << " |" << endl;
        }

        cout << string(100, '-') << endl; 
    }
}

void print_friends_by_month(int month) {
    if (month < 1 || month > 12) {
        cout << "Invalid month. Please enter a number between 1 and 12.\n";
        return;
    }

    bool found = false;
    cout << "| " << setw(COLUMN_WIDTH) << left << "Lastname"
         << "| " << setw(COLUMN_WIDTH) << left << "Name"
         << "| " << setw(COLUMN_WIDTH) << left << "Middle name"
         << "| " << setw(COLUMN_WIDTH) << left << "Date of birth"
         << "| " << setw(COLUMN_WIDTH) << left << "City"
         << "| " << setw(COLUMN_WIDTH) << left << "Phone number" << " |" << endl;
    cout << string(100, '-') << endl;

    for (int i = 0; i < get_friend_count(); ++i) {
        if (friends[i].month == month) {
            found = true;
            cout << "| " << setw(COLUMN_WIDTH) << left << friends[i].lastName
                 << "| " << setw(COLUMN_WIDTH) << left << friends[i].firstName
                 << "| " << setw(COLUMN_WIDTH) << left << friends[i].middleName
                 << "| " << setw(COLUMN_WIDTH) << left << friends[i].day << "."
                 << (friends[i].month < 10 ? "0" : "") << friends[i].month << "."
                 << friends[i].year
                 << "| " << setw(COLUMN_WIDTH) << left << friends[i].address
                 << "| " << setw(COLUMN_WIDTH) << left << friends[i].phone << " |" << endl;
            cout << string(100, '-') << endl;
        }
    }

    if (!found) {
        cout << "No friends found for the specified month.\n";
    }
}

int main() {
    int choice;

    while (true) {
        cout << "1. Add a friend\n";
        cout << "2. Delete a friend\n";
        cout << "3. Print all friends\n";
        cout << "4. Seach by month of birth\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Friend new_friend;
            cout << "Enter lastname: ";
            cin.ignore();
            getline(cin, new_friend.lastName);
            cout << "Enter name: ";
            getline(cin, new_friend.firstName);
            cout << "Enter middle name: ";
            getline(cin, new_friend.middleName);
            cout << "Enter DAY of birth: ";
            cin >> new_friend.day;
            cout << "Enter MONTH of birth: ";
            cin >> new_friend.month;
            cout << "Enter YEAR of birth: ";
            cin >> new_friend.year;
            cin.ignore();
            cout << "Enter sity: ";
            getline(cin, new_friend.address);
            cout << "Enter phone number: ";
            getline(cin, new_friend.phone);

            add_friend(new_friend);
            cout << "Friend added!\n\n";

        } else if (choice == 2) {
            int index;
            cout << "Enter index for delete friend: ";
            cin >> index;
            delete_friend(index - 1);
        } else if (choice == 3) {
            print_friends();
        } else if (choice == 4) {
            int month;
            cout << "Enter MONTH (1-12): ";
            cin >> month;
            print_friends_by_month(month);
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}

// ДОРАБОТАТЬ!!
// 1. Переделать структуру на классы, функции в методы, и как минимум 3 конструктора должно быть
// 2. Чтобы дата рождения была реальной т.е. можно было добавить друга до 1900 до 2008(чтоб было как минимум 16 лет челу, т.к. делаем подобие вк аналог)


// ИДЕИ ДЛЯ КОТОРЫЕ МОЖНО ДОБАВИТЬ К КЛАССУ
//1. Возможность изменения информации о друге
//2. Поиск  ->. 1. по Фамилии 2. Имени 3. Отчеству 4. городу 5.номеру телефона
//3. Сортировать друзей -> 1. По фамилии -> 1.1. По убыванию 1.2. По возрастанию  
