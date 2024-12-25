#include "showFriendDetails.h"
#include <iostream>

void showFriendDetails(const Friend& f) {
    std::cout << "[Friend Details - via friend function]: "
              << f.getLastName() << " " << f.getFirstName() << " " << f.getMiddleName()
              << ", Gender: " << f.getGender()
              << ", Age: " << f.calculateAge()
              << ", Phone: " << f.getPhone() << std::endl;
}
