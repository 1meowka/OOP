#ifndef FRIEND_H
#define FRIEND_H

#include "Person.h"

// Прототипы для дружественных функций и классов
class FriendInspector;
void showFriendDetails(const class Friend& f);

class Friend : public Person {
private:
    // Дружественная функция
    friend void showFriendDetails(const Friend& f);

    // Дружественный класс
    friend class FriendInspector;

public:
    // Конструкторы
    Friend();
    Friend(const std::string& ln, const std::string& fn);
    Friend(const std::string& ln, const std::string& fn, const std::string& mn,
           const Date& dob, const Address& addr,
           unsigned long long ph, char g);
    Friend(const Friend& other);

    // Оператор присваивания
    Friend& operator=(const Friend& other);

    // Реализация чисто виртуальной функции из Person
    void printRole() const override;

    // Перегрузка оператора < для сравнения по возрасту
    bool operator<(const Friend& other) const;

    // Перегрузка префиксного оператора --
    Friend& operator--();

    // Метод для ввода данных друга
    void inputFriend();

    // Вывод информации о друге
    void printFriend(int id) const;
};

#endif // FRIEND_H
