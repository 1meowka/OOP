#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include "Friend.h"
const int MAX_FRIENDS = 100;
class FriendList {
private:
    Friend friends[MAX_FRIENDS];
    int count;

public:
    FriendList();

    // Конструктор копирования
    FriendList(const FriendList& other);

    // Оператор присваивания
    FriendList& operator=(const FriendList& other);

    // Перегрузка оператора - (возвращает количество друзей нужного пола)
    int operator-(char gender) const;

    // Добавить друга
    void addFriend(const Friend& newFriend);

    // Удалить друга
    void deleteFriend(int index);

    bool isEmpty() const;
    int  getCount() const;

    // Доступ к друзьям (для чтения/записи)
    Friend& getFriend(int index);
    const Friend& getFriend(int index) const;

    // Печать всех друзей
    void printFriends() const;

    // Печать друзей, у которых месяц рождения = month
    void printFriendsByMonth(int month) const;
};

#endif // FRIENDLIST_H
