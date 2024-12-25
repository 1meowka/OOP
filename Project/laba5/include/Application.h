#ifndef APPLICATION_H
#define APPLICATION_H

#include "FriendList.h"
#include "BestFriend.h"
#include "Colleague.h"
const int MAX_BEST_FRIENDS = 50;
const int MAX_COLLEAGUES = 50;
class Application {
private:
    FriendList friendList;                   // Все обычные друзья
    BestFriend bestFriendsArr[MAX_BEST_FRIENDS]; 
    int bestFriendsCount;

    Colleague colleaguesArr[MAX_COLLEAGUES];
    int colleaguesCount;

    // Вывод меню
    void showMenu() const;

    // Печать всех людей (Friend, BestFriend, Colleague) «в одной таблице»
    void printAllPersons() const;

public:
    Application();
    void run();
};

#endif // APPLICATION_H
