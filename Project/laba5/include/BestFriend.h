#ifndef BESTFRIEND_H
#define BESTFRIEND_H

#include "Friend.h"

class BestFriend : public Friend {
public:
    using Friend::Friend; // Наследуем конструкторы

    void printRole() const override;
};

#endif // BESTFRIEND_H
