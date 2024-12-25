#include "FriendList.h"
#include "Utils.h" 
#include <iostream>
#include <iomanip>
#include <algorithm>


FriendList::FriendList() : count(0) {}

// Конструктор копирования
FriendList::FriendList(const FriendList& other) : count(other.count) {
    for (int i = 0; i < other.count; ++i) {
        friends[i] = other.friends[i];
    }
}

// Оператор присваивания
FriendList& FriendList::operator=(const FriendList& other) {
    if (this != &other) {
        count = other.count;
        for (int i = 0; i < count; ++i) {
            friends[i] = other.friends[i];
        }
    }
    return *this;
}

// Перегрузка оператора - для подсчета количества друзей по полу
int FriendList::operator-(char gender) const {
    int countGender = 0;
    for (int i = 0; i < count; ++i) {
        if (friends[i].getGender() == gender) {
            countGender++;
        }
    }
    return countGender;
}

// Добавить друга
void FriendList::addFriend(const Friend& newFriend) {
    if (count >= MAX_FRIENDS) {
        std::cout << "Cannot add more friends. The list is full.\n";
        return;
    }
    friends[count++] = newFriend;
    std::cout << "Friend added successfully!\n";
}

// Удалить друга
void FriendList::deleteFriend(int index) {
    if (index < 0 || index >= count) {
        std::cout << "Invalid index.\n";
        return;
    }
    for (int i = index; i < count - 1; ++i) {
        friends[i] = friends[i + 1];
    }
    count--;
    std::cout << "Friend deleted.\n";
}

bool FriendList::isEmpty() const { return count == 0; }
int FriendList::getCount() const { return count; }

// Доступ к друзьям
Friend& FriendList::getFriend(int index) { return friends[index]; }
const Friend& FriendList::getFriend(int index) const { return friends[index]; }

// Печать всех друзей
void FriendList::printFriends() const {
    if (isEmpty()) {
        std::cout << "The friends list is empty.\n";
        return;
    }
    std::cout << "| " << std::setw(3) << std::left << "ID"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Last Name"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "First Name"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Middle Name"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Date of Birth"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Age"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Gender"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Address"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Phone"
              << " |\n";
    std::cout << std::string(8 + COLUMN_WIDTH * 8 + 3, '-') << std::endl;

    for (int i = 0; i < count; ++i) {
        friends[i].printFriend(i + 1);
        std::cout << std::string(8 + COLUMN_WIDTH * 8 + 3, '-') << std::endl;
    }
}

// Печать друзей по месяцу рождения
void FriendList::printFriendsByMonth(int month) const {
    if (month < 1 || month > 12) {
        std::cout << "Invalid month. Please enter a number between 1 and 12.\n";
        return;
    }
    bool found = false;

    std::cout << "| " << std::setw(3) << std::left << "ID"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Last Name"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "First Name"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Middle Name"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Date of Birth"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Age"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Gender"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Address"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Phone"
              << " |\n";
    std::cout << std::string(8 + COLUMN_WIDTH * 8 + 3, '-') << std::endl;

    for (int i = 0; i < count; ++i) {
        if (friends[i].getDateOfBirth().getMonth() == month) {
            friends[i].printFriend(i + 1);
            std::cout << std::string(8 + COLUMN_WIDTH * 8 + 3, '-') << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No friends found with birthday in this month.\n";
    }
}
