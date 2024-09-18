#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <vector>

using namespace std;

string strstrip(string str) // Удаляет начальные и конечные пробелы из строки
{
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    size_t end = str.find_last_not_of(" \t\n\r\f\v");

    if (start == string::npos) return ""; // пустая строка
    return str.substr(start, end - start + 1);
}

string strcut(string str, int len) // Обрезает строку до заданной длины
{
    if (len < str.length()) {
        return str.substr(0, len);
    }
    return str;
}

int countdigits(const string &str) // Считает число цифр в строке
{
    int count = 0;
    for (char c : str) {
        if (isdigit(c)) {
            ++count;
        }
    }
    return count;
}

int maxInt(int a, int b) // Находит максимальное из двух цифр
{
    return (a > b) ? a : b;
}

struct Audio { // Структура аудиозаписи
    string title;
    string group;
    string album;
    string genre;
    int year;
};

void correctInputAudioParametr(const string &parametr, string &str) // Для строковых - не может быть пустой и длина будет обрезаться на 40
{
    string buffer;
    do {
        cout << "  * " << parametr << " -> ";
        getline(cin, buffer);
        buffer = strstrip(buffer);
    } while (buffer.empty());
    str = strcut(buffer, 40);
}

void correctInputAudioYear(int &year) // Для года - число больше нуля и не больше 9999
{
    string buffer;
    int ndigits;
    year = -1;
    do {
        cout << "  * year -> ";
        getline(cin, buffer);
        buffer = strstrip(buffer);
        ndigits = countdigits(buffer);
        if (ndigits <= 4 && ndigits == buffer.length()) {
            year = atoi(buffer.c_str());
        }
    } while (year < 0);
}

void inputAudio(Audio &audio) // Ввод аудиозаписи с клавиатуры
{
    cout << "\nEnter information about audio\n";
    correctInputAudioParametr("title", audio.title);
    correctInputAudioParametr("group", audio.group);
    correctInputAudioParametr("album", audio.album);
    correctInputAudioParametr("genre", audio.genre);
    correctInputAudioYear(audio.year);
}

void formFromStrAudio(Audio &audio, const string &str) // Формирование аудиозаписи из строки
{
    size_t pos = 0, prev_pos = 0;
    string fields[5];
    int i = 0;
    while ((pos = str.find('|', prev_pos)) != string::npos) {
        fields[i++] = str.substr(prev_pos, pos - prev_pos);
        prev_pos = pos + 1;
    }
    fields[i] = str.substr(prev_pos);
    
    audio.title = fields[0];
    audio.group = fields[1];
    audio.album = fields[2];
    audio.genre = fields[3];
    audio.year = atoi(fields[4].c_str());
}

void saveToStrAudio(const Audio &audio, string &str) // Сохраняет аудиозапись в строку
{
    str = audio.title + "|" + audio.group + "|" + audio.album + "|" + audio.genre + "|" + to_string(audio.year);
}

struct PlayList {
    vector<Audio> audios;
};

void addAudioPlayList(PlayList &list, const Audio &audio) // Добавляем аудиозапись в плейлист
{
    list.audios.push_back(audio);
}

void inputAudioPlayList(PlayList &list) // Вводим аудиозапись с клавиатуры и добавляем в список
{
    Audio audio;
    inputAudio(audio);
    addAudioPlayList(list, audio);
}

void readFromFilePlayList(PlayList &list, const string &filename) // Считываем аудиозаписи из файла
{
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    string buffer;
    while (getline(file, buffer)) {
        Audio audio;
        formFromStrAudio(audio, buffer);
        addAudioPlayList(list, audio);
    }
    file.close();
}

void saveToFilePlayList(const PlayList &list, const string &filename) // Сохранение списка записей в файл
{
    ofstream file(filename);
    if (!file.is_open()) {
        return;
    }

    string buffer;
    for (const auto &audio : list.audios) {
        saveToStrAudio(audio, buffer);
        file << buffer << endl;
    }
    file.close();
}

void removeAtPlayList(PlayList &list, int index) // Удаляет аудиозапись по индексу
{
    if (index >= 0 && index < list.audios.size()) {
        list.audios.erase(list.audios.begin() + index);
    }
}

void printPlayList(const PlayList &list) // Печать списка аудиозаписей в виде таблицы
{
    if (list.audios.empty()) {
        cout << "[INFO] Play list is empty\n";
        return;
    }

    cout << "| #  | Title                             | Group                             | Album                             | Genre                             | Year |\n";
    cout << "--------------------------------------------------------------------------------------------------------------\n";
    for (size_t i = 0; i < list.audios.size(); ++i) {
        const Audio &audio = list.audios[i];
        cout << "| " << (i + 1) << "  | " << strcut(audio.title, 30) << " | " 
             << strcut(audio.group, 30) << " | " 
             << strcut(audio.album, 30) << " | " 
             << strcut(audio.genre, 30) << " | " 
             << audio.year << " |\n";
    }
}

int main()
{
    PlayList playlist;
    string filename = "playlist.txt";

    readFromFilePlayList(playlist, filename);

    int command;
    do {
        cout << "[1] Add audio\n[2] Remove audio\n[3] Print all audios\n[0] Exit\n -> ";
        cin >> command;
        cin.ignore();

        switch (command) {
        case 1:
            inputAudioPlayList(playlist);
            cout << "[INFO] Audio has been added\n";
            break;
        case 2:
            int index;
            cout << "Enter the number of audio to remove -> ";
            cin >> index;
            if (index > 0 && index <= playlist.audios.size()) {
                removeAtPlayList(playlist, index - 1);
                cout << "[INFO] Audio has been removed\n";
            } else {
                cout << "[ERROR] Invalid number\n";
            }
            break;
        case 3:
            printPlayList(playlist);
            break;
        }

    } while (command != 0);

    saveToFilePlayList(playlist, filename);

    return 0;
}