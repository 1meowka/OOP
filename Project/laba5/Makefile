# Настройки компилятора и сборки
CC      = g++
CFLAGS  = -Wall -Wextra -std=c++17 -Iinclude
LDFLAGS = -mconsole

# Папки проекта
OBJ_DIR = obj
BIN_DIR = bin
SRC_DIR = src

# Целевой (исполняемый) файл
TARGET = $(BIN_DIR)/app.exe

# Исходники и объектные файлы
SOURCES = main.cpp $(wildcard $(SRC_DIR)/*.cpp)

# Преобразуем имена .cpp в имена .o 
# (например, src/Address.cpp -> obj/Address.o)
OBJECTS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SOURCES)))

# Основные цели
all: prepare_dirs $(TARGET)

# Создание необходимых директорий (если их нет)
prepare_dirs:
	cmd /C "if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)"
	cmd /C "if not exist $(BIN_DIR) mkdir $(BIN_DIR)"

# Линковка (создание исполняемого файла)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

# Правила компиляции:
# Скомпилировать main.cpp -> obj/main.o
$(OBJ_DIR)/main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o $@
	
# Скомпилировать каждый .cpp из папки src -> .o в папке obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Цель очистки проекта
clean:
	cmd /C "if exist $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR)"
	cmd /C "if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)"

