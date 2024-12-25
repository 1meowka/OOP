#include "FriendInspector.h"
#include <iostream>

void FriendInspector::inspect(const Friend& f) {
    std::cout << "[FriendInspector]: Inspecting Friend: "
              << f.getLastName() << " " << f.getFirstName()
              << ", Phone: " << f.getPhone() << std::endl;
}
