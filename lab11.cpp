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
        cout << "You can't add a friend, because the limit is 100 friends\n";
    }
}

void delete_friend(int index) {
    if (index >= 0 && index < get_friend_count()) {
        for (int i = index; i < friend_count - 1; ++i) {
            friends[i] = friends[i + 1];
        }
        friend_count--;
    } else {
        cout << "Error: Invalid index\n";
    }
}

void print_friends() {
    if (get_friend_count() == 0) {
        cout << "The friends list is empty\n";
        return;
    }

    cout << "| " << setw(COLUMN_WIDTH) << left << "Lastname"
         << "| " << setw(COLUMN_WIDTH) << left << "Name"
         << "| " << setw(COLUMN_WIDTH) << left << "Middle name"
         << "| " << setw(COLUMN_WIDTH) << left << "Date of birth"
         << "| " << setw(COLUMN_WIDTH) << left << "City"
         << "| " << setw(COLUMN_WIDTH) << left << "Phone number" << " |" << endl;
    cout << string(100, '-') << endl;

    for (int i = 0; i < get_friend_count(); ++i) {
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
        cout << "4. Search by month of birth\n";
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
            cout << "Enter city: ";
            getline(cin, new_friend.address);
            cout << "Enter phone number: ";
            getline(cin, new_friend.phone);

            add_friend(new_friend);
            cout << "Friend added!\n\n";

        } else if (choice == 2) {
            int index;
            cout << "Enter index of the friend to delete: ";
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
