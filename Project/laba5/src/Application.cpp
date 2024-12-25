#include "Application.h"
#include "Utils.h"
#include "BestFriend.h"
#include "Colleague.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

// Конструктор
Application::Application() 
    : bestFriendsCount(0), colleaguesCount(0) {}

// Вывод меню
void Application::showMenu() const {
    std::cout << "\n     Menu:\n";
    std::cout << "1. Add a Friend\n";
    std::cout << "2. Delete a Friend\n";
    std::cout << "3. Print All Friends\n";
    std::cout << "4. Print Friends by Birth Month\n";
    std::cout << "5. Calculate Number of Friends by Gender\n";
    std::cout << "6. Add Days to a Friend's Birthday (+ operator)\n";
    std::cout << "7. Increase Birthday by One Day (postfix increment++)\n";
    std::cout << "8. Decrease Friend's Age by One Year (prefix decrement--)\n";
    std::cout << "9. Compare Two Friends by Age\n";
    std::cout << "10. Copy a Friend\n";
    std::cout << "11. Assign Data from One Friend to Another\n";
    std::cout << "12. Add a BestFriend\n";
    std::cout << "13. Add a Colleague\n";
    std::cout << "14. Show Roles of All (in One Table)\n";
    std::cout << "15. Exit\n";
    std::cout << "Choose an option: ";
}

// Печать всех людей (Friend, BestFriend, Colleague) «в одной таблице»
void Application::printAllPersons() const {
    // Собираем всех в массив const Person*
    const Person* allPersons[MAX_FRIENDS + MAX_BEST_FRIENDS + MAX_COLLEAGUES];
    int totalCount = 0;

    // 1) Friends из friendList
    for (int i = 0; i < friendList.getCount(); i++) {
        allPersons[totalCount++] = &friendList.getFriend(i);
    }

    // 2) BestFriends
    for (int i = 0; i < bestFriendsCount; i++) {
        allPersons[totalCount++] = &bestFriendsArr[i];
    }

    // 3) Colleagues
    for (int i = 0; i < colleaguesCount; i++) {
        allPersons[totalCount++] = &colleaguesArr[i];
    }

    if (totalCount == 0) {
        std::cout << "No persons to display.\n";
        return;
    }

    // Заголовок
    std::cout << "| " << std::setw(3) << std::left << "ID"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Last Name"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "First Name"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Middle Name"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Date of Birth"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Age"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Gender"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Address"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Phone"
              << "| " << std::setw(COLUMN_WIDTH) << std::left << "Role"
              << " |\n";
    std::cout << std::string(8 + COLUMN_WIDTH * 9 + 3, '-') << std::endl;

    // Построчно выводим данные
    for (int i = 0; i < totalCount; i++) {
        const Person* p = allPersons[i];

        // Данные
        std::string idStr       = std::to_string(i + 1);
        std::string ln          = p->getLastName();
        std::string fn          = p->getFirstName();
        std::string mn          = p->getMiddleName();
        std::string dob         = p->getDateOfBirth().toString();
        std::string ageStr      = std::to_string(p->calculateAge());
        std::string genStr(1, p->getGender());
        std::string addrStr     = p->getAddress().getFullAddress();
        std::string phoneStr    = std::to_string(p->getPhone());

        // Определяем «роль»
        std::string roleOut;
        if (dynamic_cast<const BestFriend*>(p)) {
            roleOut = "BestFriend";
        } else if (dynamic_cast<const Friend*>(p)) {
            roleOut = "Friend";
        } else if (dynamic_cast<const Colleague*>(p)) {
            roleOut = "Colleague";
        } else {
            roleOut = "Unknown";
        }

        // Разбиваем на подстроки
        std::string idParts[MAX_LINES];      int idCount=0;   splitString(idStr,     idParts,    idCount);
        std::string lnParts[MAX_LINES];      int lnCount=0;   splitString(ln,        lnParts,    lnCount);
        std::string fnParts[MAX_LINES];      int fnCount=0;   splitString(fn,        fnParts,    fnCount);
        std::string mnParts[MAX_LINES];      int mnCount=0;   splitString(mn,        mnParts,    mnCount);
        std::string dobParts[MAX_LINES];     int dobCount=0;  splitString(dob,       dobParts,   dobCount);
        std::string ageParts[MAX_LINES];     int ageCount=0;  splitString(ageStr,    ageParts,   ageCount);
        std::string genParts[MAX_LINES];     int genCount=0;  splitString(genStr,    genParts,   genCount);
        std::string addrParts[MAX_LINES];    int addrCount=0; splitString(addrStr,   addrParts,  addrCount);
        std::string phoneParts[MAX_LINES];   int phoneCount=0;splitString(phoneStr,  phoneParts, phoneCount);
        std::string roleParts[MAX_LINES];    int roleCount=0; splitString(roleOut,   roleParts,  roleCount);

        int maxRows = std::max({
            idCount, lnCount, fnCount, mnCount,
            dobCount, ageCount, genCount,
            addrCount, phoneCount, roleCount
        });

        for (int row = 0; row < maxRows; row++) {
            std::cout << "| " << std::setw(3) << std::left 
                      << (row < idCount    ? idParts[row]    : "")
                      << "| " << std::setw(COLUMN_WIDTH) << std::left
                      << (row < lnCount    ? lnParts[row]    : "")
                      << "| " << std::setw(COLUMN_WIDTH) << std::left
                      << (row < fnCount    ? fnParts[row]    : "")
                      << "| " << std::setw(COLUMN_WIDTH) << std::left
                      << (row < mnCount    ? mnParts[row]    : "")
                      << "| " << std::setw(COLUMN_WIDTH) << std::left
                      << (row < dobCount   ? dobParts[row]   : "")
                      << "| " << std::setw(COLUMN_WIDTH) << std::left
                      << (row < ageCount   ? ageParts[row]   : "")
                      << "| " << std::setw(COLUMN_WIDTH) << std::left
                      << (row < genCount   ? genParts[row]   : "")
                      << "| " << std::setw(COLUMN_WIDTH) << std::left
                      << (row < addrCount  ? addrParts[row]  : "")
                      << "| " << std::setw(COLUMN_WIDTH) << std::left
                      << (row < phoneCount ? phoneParts[row] : "")
                      << "| " << std::setw(COLUMN_WIDTH) << std::left
                      << (row < roleCount  ? roleParts[row]  : "")
                      << " |\n";
        }
        std::cout << std::string(8 + COLUMN_WIDTH * 9 + 3, '-') << std::endl;
    }
} // Добавлена закрывающая фигурная скобка метода printAllPersons

// Главный цикл приложения
void Application::run() {
    int choice;
    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            Friend f;
            f.inputFriend();
            friendList.addFriend(f);
            break;
        }
        case 2: {
            if (friendList.isEmpty()) {
                std::cout << "The friends list is empty. Nothing to delete.\n";
                break;
            }
            friendList.printFriends();
            std::cout << "Enter the friend's ID to delete: ";
            int index; std::cin >> index; std::cin.ignore();
            friendList.deleteFriend(index - 1);
            break;
        }
        case 3:
            printAllPersons();
            break;
        case 15:
            std::cout << "Exiting the program.\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 15);
}
