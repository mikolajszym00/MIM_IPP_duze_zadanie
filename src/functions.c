#include "functions.h"

bool getInteger(int* num, char character) {
    if (isdigit(character)){
        *num = character - '0';
        return true;
    }
    else { return false; }
}
