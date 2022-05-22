#include "phone_numbers.h"

PhoneNumbers* phnumNew(Trie trieOfNumbers, Trie* arrayOfNumbersEnd) {
    PhoneNumbers* pn = malloc(sizeof(struct PhoneNumbers));
    if (pn == NULL) { return NULL; }

    pn->trieOfNumbers = trieOfNumbers;
    pn->arrayOfNumbersEnd = arrayOfNumbersEnd;
    pn->arrayOfNumbers = malloc(sizeof(char*));
    return pn;
}

void addNumbersPtrToArray(PhoneNumbers const *pnum, char* number) {
    char** arr = pnum->arrayOfNumbers;
    arr[0] = number;
}
