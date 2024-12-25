#ifndef COLLEAGUE_H
#define COLLEAGUE_H

#include "Person.h"

class Colleague : public Person {
public:
    Colleague();

    void printRole() const override;

    void inputColleague();
};

#endif // COLLEAGUE_H
