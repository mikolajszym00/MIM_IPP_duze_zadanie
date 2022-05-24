#include "phone_numbers.h"

PhoneNumbers* phnumNew(size_t numberOfTries, Trie trieOfNumbers, Trie* arrayOfNumbersEnd, char type) {
    PhoneNumbers* pn = malloc(sizeof(struct PhoneNumbers));
    if (pn == NULL) { return NULL; }

    pn->trieOfNumbers = trieOfNumbers;
    pn->arrayOfNumbersEnd = arrayOfNumbersEnd;
    pn->arrayOfNumbers = calloc(numberOfTries, sizeof(char*));
    pn->numberOfTries = numberOfTries;
    pn->type = type;
    return pn;
}

void addNumbersPtrToArray(PhoneNumbers const *pnum, char* number) {
    char** arr = pnum->arrayOfNumbers;
    arr[0] = number;
}

char* getNumber(PhoneNumbers const *pnum, Trie tr) {
    char* number = calloc(tr->depth+1, sizeof(char));

    getNumberFromTrie(tr, number, (tr->depth) - 1);

    if (pnum->type == 'r') {
        char* reversedNumber = reverseNum(number);

        free(number);

        addNumbersPtrToArray(pnum, reversedNumber);
        return reversedNumber;
    }

    addNumbersPtrToArray(pnum, number);

    return number;
}
