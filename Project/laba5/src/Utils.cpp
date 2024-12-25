#include "Utils.h"
#include <string>

void splitString(const std::string& str, std::string parts[], int& count) {
    count = 0;
    int len = static_cast<int>(str.length());
    for (int i = 0; i < len; i += COLUMN_WIDTH) {
        if (count >= MAX_LINES) break;
        parts[count++] = str.substr(i, COLUMN_WIDTH);
    }
}
