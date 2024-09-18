#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *strstrip(char *str) //  Удаляет начальные и конечные пробелы из строки
{
    int start = 0, end = strlen(str) - 1, i, j;
    while (str[start] != '\0' && isspace(str[start]))
    {
        ++start;
    }
    while (end >= 0 && isspace(str[end]))
    {
        --end;
    }
    for (i = start, j = 0; i <= end; ++i, ++j)
    {
        str[j] = str[i];
    }
    str[end + 1] = '\0';
    return str;
}

char *strcut(char *str, int len)  //  Обрезает строку до заданной длины
{
    if (len < strlen(str))
    {
        str[len] = '\0';
    }
    return str;
}

int countdigits(char *str) //  Считает число цифр в строке
{
    int count = 0, i;
    for (i = 0; str[i] != '\0'; ++i)
    {
        if (isdigit(str[i]))
        {
            ++count;
        }
    }
    return count;
}

int maxInt(int a, int b) //  Находит максимальное из двух цифр
{
    return a > b ? a : b;
}

typedef struct Audio_  //  Структура аудиозаписи
{
    char title[41];
    char group[41];
    char album[41];
    char genre[41];
    int year;
} Audio;

void correctInputAudioParametr(char *parametr, char *str)  //  Для строковых - не может быть пустой и длина будет обрезаться на 40
{
    char buffer[1024];

    do
    {
        printf("  * %-6s-> ", parametr);
        fgets(buffer, 1024, stdin);
        strstrip(buffer);
    } while (strlen(buffer) < 1);
    strcut(buffer, 40);
    strcpy(str, buffer);
}

void correctInputAudioYear(int *year) //  Для года - число больше нуля и небольше 9999 
{
    char buffer[1024];
    int ndigits = 0;
    *year = -1;
    do
    {
        printf("  * %-6s-> ", "year");
        fgets(buffer, 1024, stdin);
        strstrip(buffer);
        ndigits = countdigits(buffer);
        if (ndigits <= 4 && ndigits == strlen(buffer))
        {
            *year = atoi(buffer);
        }
    } while (*year < 0);
}

void inputAudio(Audio *audio) //  Ввод аудиозаписи с клавиатуры
{
    printf("\nEnter information about audio\n");
    correctInputAudioParametr("title", audio->title);
    correctInputAudioParametr("group", audio->group);
    correctInputAudioParametr("album", audio->album);
    correctInputAudioParametr("genre", audio->genre);
    correctInputAudioYear(&audio->year);
}

void formFromStrAudio(Audio *audio, char *str) //  Формирование аудиозаписи из строки 
{   
    char *p = strtok(str, "|");
    strcpy(audio->title, p);
    p = strtok(NULL, "|");
    strcpy(audio->group, p);
    p = strtok(NULL, "|");
    strcpy(audio->album, p);
    p = strtok(NULL, "|");
    strcpy(audio->genre, p);
    p = strtok(NULL, "|");
    audio->year = atoi(p);
    p = strtok(NULL, "|");
}

void saveToStrAudio(Audio *audio, char *str) //  Сохраняет аудиозапись в строку 
{
    sprintf(str, "%s|%s|%s|%s|%d",
            audio->title, audio->group, audio->album, audio->genre, audio->year);
}

typedef struct PlayList_
{
    int count;
    int capacity;
    Audio **audios;
} PlayList;

void createPlayList(PlayList *list) //  Создание списка аудиозаписей (инициализация)
{
    list->count = 0;
    list->capacity = 0;
    list->audios = NULL;
}

//  Удаление списка аудиозаписей
void deletePlayList(PlayList *list)
{
    int i;
    if (list->audios != NULL)
    {
        //  Сначала удаляем сами аудиозаписи
        for (i = 0; i < list->count; ++i)
        {
            free(list->audios[i]);
        }
        //  Затем массив
        free(list->audios);
    }
    list->count = 0;
    list->capacity = 0;
    list->audios = NULL;
}

//  Увеличивает размер массива аудиозаписей
//  (когда массив заполнен и мы добавляем ещё запись)
void increasePlayList(PlayList *list)
{
    Audio **old_audios = list->audios;
    int i;

    list->capacity = (list->capacity != 0) ? list->capacity * 2 : 2;
    list->audios = (Audio **)malloc(list->capacity * sizeof(Audio *));
    for (i = 0; i < list->count; ++i)
    {
        list->audios[i] = old_audios[i];
    }
    if (old_audios != NULL)
    {
        free(old_audios);
    }
}

//  Добаляем аудиозапись в плейлист
void addAudioPlayList(PlayList *list, Audio *audio)
{
    if (list->count == list->capacity)
    {
        increasePlayList(list);
    }
    list->audios[list->count] = audio;
    ++list->count;
}

//  Вводим аудиозапись с клавиатуры и добавляем в список
void inputAudioPlayList(PlayList *list)
{
    Audio *audio = (Audio *)malloc(sizeof(Audio));
    inputAudio(audio);
    addAudioPlayList(list, audio);
}

//  Считываем аудиозаписи из файла
void readFromFilePlayList(PlayList *list, char *filename)
{
    FILE *fp;
    Audio *audio;
    char buffer[128];

    if ((fp = fopen(filename, "r")) == NULL)
    {
        return;
    }
    //  Пока в файле есть информация об аудиозаписи
    //  считываем её, формируем из неё аудиозапись
    //  и добавляем в список
    while (fgets(buffer, 128, fp) != NULL)
    {
        audio = (Audio *)malloc(sizeof(Audio));
        formFromStrAudio(audio, buffer);
        addAudioPlayList(list, audio);
    }
    fclose(fp);
}

//  Сохранение списка записей в файл
void saveToFilePlayList(PlayList *list, char *filename)
{
    char buffer[128];
    FILE *fp = fopen(filename, "w");
    int i;

    //  Для каждой аудиозаписи
    //  формируем из неё строку и записываем в файл
    for (i = 0; i < list->count; ++i)
    {
        saveToStrAudio(list->audios[i], buffer);
        fprintf(fp, "%s\n", buffer);
    }
    fclose(fp);
}

//  Удаляет аудиозапись по индексу
void removeAtPlayList(PlayList *list, int index)
{
    int i;
    Audio *removal = list->audios[index];
    for (i = index; i < list->count; ++i)
    {
        list->audios[i] = list->audios[i + 1];
    }
    free(removal);
    --list->count;
    list->audios[list->count] = NULL;
}

//  Дополнительная функция для печати таблицы
//  Формирует строку из одного пробела и len знаков минус
//  Возвращает указатель на конец строки
char *formLine(char *line, int len)
{
    *line = ' ';
    ++line;
    for (; len > 0; --len)
    {
        *line = '-';
        ++line;
    }
    *line = '\0';
    return line;
}

//  Печать списка аудиозаписей в виде таблицы
void printPlayList(PlayList *list)
{
    //  Высчитваем ширину каждого столбца
    int max_title_len = 5, i;
    int max_group_len = 5;
    int max_album_len = 5;
    int max_genre_len = 5;
    for (i = 0; i < list->count; ++i)
    {
        max_title_len = maxInt(max_title_len, strlen(list->audios[i]->title));
        max_group_len = maxInt(max_group_len, strlen(list->audios[i]->group));
        max_album_len = maxInt(max_album_len, strlen(list->audios[i]->album));
        max_genre_len = maxInt(max_genre_len, strlen(list->audios[i]->genre));
    }

    //  Формируем линию (для красоты)
    char line[512] = {0}, *it = line;
    it = formLine(it, 4);
    it = formLine(it, max_title_len + 2);
    it = formLine(it, max_group_len + 2);
    it = formLine(it, max_album_len + 2);
    it = formLine(it, max_genre_len + 2);
    it = formLine(it, 6);

    //  Печатаем шапку
    printf("%s\n", line);
    printf("| %2s | %*s | %*s | %*s | %*s | %4s |\n",
           "#",
           max_title_len, "Title",
           max_group_len, "Group",
           max_album_len, "Album",
           max_genre_len, "Genre",
           "Year");
    printf("%s\n", line);
    //  Печатаем аудиозаписи
    for (i = 0; i < list->count; ++i)
    {
        printf("| %2d | %*s | %*s | %*s | %*s | %4d |\n",
               i + 1,
               max_title_len, list->audios[i]->title,
               max_group_len, list->audios[i]->group,
               max_album_len, list->audios[i]->album,
               max_genre_len, list->audios[i]->genre,
               list->audios[i]->year);
    }
    printf("%s\n", line);
}

//  Поиск аудиозаписи по группе
//  Возращает индекс первой аудиозаписи или -1, если не найдена
char findGroupPlayList(PlayList *list, char *group)
{
    int i;
    for (i = 0; i < list->count; ++i)
    {
        if (strcmp(group, list->audios[i]->group) == 0)
        {
            return i;
        }
    }
    return -1;
}

//  Печатает альбомы заданной группы
void printAlbumByGroupPlayList(PlayList *list, char *group)
{
    int count = 0, index = findGroupPlayList(list, group), i, j;
    char album[41] = {0}, exist;
    if (index == -1)
    {
        return;
    }

    for (i = index; i < list->count; ++i)
    {
        if (strcmp(group, list->audios[i]->group) == 0)
        {
            strcpy(album, list->audios[i]->album);
            //  Здесь проверяем, что данный альбом ещё не печатался
            exist = 0;
            for (j = index; j < i && !exist; ++j)
            {
                if (strcmp(album, list->audios[j]->album) == 0)
                {
                    exist = 1;
                }
            }
            if (!exist)
            {
                ++count;
                printf(" * %-3d%s\n", count, album);
            }
        }
    }
}

//  Проверка на пустоту списка
char isEmptyPlayList(PlayList *list)
{
    return list->count == 0;
}

//  Количество записей в списке
int lengthPlayList(PlayList *list)
{
    return list->count;
}

//  Интерфейсные функции

//  Вывод пользовательского меню
void printMenu()
{
    printf("%s\n%s\n%s\n%s\n%s\n\n -> ",
           "[1] Add audio",
           "[2] Remove audio",
           "[3] Print all audios",
           "[4] Print albums by group",
           "[0] Exit");
}

//  Корректный ввод номера группы (не может быть отрицательным или строкой)
char correctIntScanf(int *value)
{
    char buffer[128];
    fgets(buffer, 128, stdin);
    strstrip(buffer);
    if (countdigits(buffer) != strlen(buffer) || strlen(buffer) == 0)
    {
        return 0;
    }
    sscanf(buffer, "%d", value);
    return 1;
}

//  Основная функция
int main()
{
    char filename[] = "playlist.txt";

    //  Создаём плейлист и считываем аудиозаписи из файла
    PlayList playlist;
    createPlayList(&playlist);
    readFromFilePlayList(&playlist, filename);

    char command[128] = {0}, group[128] = {0};
    int number;

    //  Выполняем цикл команд
    do
    {
        printMenu();
        fgets(command, 128, stdin);
        strstrip(command);

        //  Если команда неверная
        if (strlen(command) > 1 || command[0] < '0' || command[0] > '4')
        {
            printf("\n[ERROR] Wrong command!\n\n");
            //  Добавление аудиозаписи
        }
        else if (command[0] == '1')
        {
            inputAudioPlayList(&playlist);
            printf("\n[INFO] Audio has been added\n\n");
            //  Удаление по номеру
        }
        else if (command[0] == '2')
        {
            if (isEmptyPlayList(&playlist))
            {
                printf("\n[INFO] Play list is empty\n\n");
                continue;
            }
            printf("\nEnter number of audio -> ");
            if (!correctIntScanf(&number))
            {
                printf("\n[ERROR] Incorect input!\n\n");
                continue;
            }
            if (number > lengthPlayList(&playlist) || number == 0)
            {
                printf("\n[ERROR] No audio with such number!\n\n");
            }
            else
            {
                removeAtPlayList(&playlist, number - 1);
                printf("\n[INFO] Remove was succesfull\n\n");
            }
            //  Вывод всех аудиозаписей
        }
        else if (command[0] == '3')
        {
            if (isEmptyPlayList(&playlist))
            {
                printf("\n[INFO] Play list is empty\n\n");
            }
            else
            {
                printf("\n[INFO] Play list\n\n");
                printPlayList(&playlist);
                printf("\n");
            }
            //  Вывод альбомов заданной группы 
        }
        else if (command[0] == '4')
        {
            if (isEmptyPlayList(&playlist))
            {
                printf("\n[INFO] Play list is empty\n\n");
                continue;
            }
            printf("\n");
            correctInputAudioParametr("group", group);
            if (findGroupPlayList(&playlist, group) != -1)
            {
                printf("\n[INFO] Albums by group %s\n\n", group);
                printAlbumByGroupPlayList(&playlist, group);
                printf("\n\n");
            }
            else
            {
                printf("\n[INFO] Not found such group\n\n");
            }
            //  Прощаемся с пользователем перед выходом
        }
        else
        {
            printf("\n[INFO] Bye\n");
        }
        //  Выходим когда введена команда "0"
    } while (strlen(command) != 1 || command[0] != '0');

    //  Перед выходом сохраняем список аудиозаписей в файл и удаляем список
    saveToFilePlayList(&playlist, filename);
    deletePlayList(&playlist);
    return 0;
}


//DAY - ne pishet 01, 02 etc
//MONTH - pishet 01, 02, 03 etc