// Функция для печати информации о друге
void printFriend(const Friend &f) {
    cout << left << setw(15) << f.lastName 
         << setw(15) << f.firstName 
         << setw(15) << f.middleName 
         << setw(2) << setfill('0') << f.day << "." << setw(2) << setfill('0') << f.month << "." << f.year 
         << "   " << setw(20) << f.address 
         << setw(15) << f.phone << endl;
}

// Функция для печати всех друзей
void printAllFriends(const list<Friend> &friends) {
    if (friends.empty()) { 
        cout << "[INFORMATION] --- Список друзей пуст.\n";
        return;
    }
    
    cout << left << setw(15) << "Фамилия" 
         << setw(15) << "Имя" 
         << setw(15) << "Отчество"
         << "Дата рождения   " << setw(20) << "Адрес" 
         << setw(15) << "Телефон" << endl;
    cout << string(80, '-') << endl;

    for (const auto &f : friends) {
        printFriend(f);
    }
}
