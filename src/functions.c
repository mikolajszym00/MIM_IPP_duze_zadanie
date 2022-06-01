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
    for (size_t i=0; i < strlen(num); i++) {
        if (!isdigit(num[i]) && num[i] != '*' && num[i] != '#') { return false; }
    }

    return true;
}

void copyNumber(char* numCopy, char const *num) {
    for (size_t i=0; i<strlen(num); i++) {
        numCopy[i] = num[i];
    }
}

char* reverseNum(char const* num) {
    size_t n = strlen(num);

    char* reversedNum = malloc(sizeof(char)*(1+n));

    for (size_t i = 0; i<n; i++) {
        reversedNum[n-1-i] = num[i];
    }

    return reversedNum;
}
