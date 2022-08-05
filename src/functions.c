#include "functions.h"

bool getInteger(int* num, char character) {
    if (isdigit(character)) {
        *num = character - '0';
        return true;
    }

    if (character == '*') {
        *num = 10;
        return true;
    }

    if (character == '#') {
        *num = 11;
        return true;
    }

    return false;
}

bool checkNum(char const *num) {
    for (size_t i = 0; num[i] != 0; i++) {
        if (!isdigit(num[i]) && num[i] != '*' && num[i] != '#')
            return false;
    }

    return true;
}

void copyNumber(char* numCopy, char const *num) {
    for (size_t i = 0; num[i] != 0; i++) {
        numCopy[i] = num[i];
    }
}
