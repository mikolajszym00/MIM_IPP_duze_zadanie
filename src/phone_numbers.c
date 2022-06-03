#include "phone_numbers.h"

PhoneNumbers* phnumNew(size_t numberOfTries, Trie trieOfNumbers, Trie* arrayOfNumbersEnd, char* initNumber) {
    PhoneNumbers* pn = malloc(sizeof(struct PhoneNumbers));
    if (pn == NULL) { return NULL; }

    pn->trieOfNumbers = trieOfNumbers;
    pn->arrayOfNumbersEnd = arrayOfNumbersEnd;
    pn->arrayOfNumbers = calloc(numberOfTries, sizeof(char*));
    pn->initNumber = initNumber;
    pn->numberOfTries = numberOfTries;
    return pn;
}

void addNumbersPtrToArray(PhoneNumbers const *pnum, char* number, size_t index) {
    char** arr = pnum->arrayOfNumbers;
    arr[index] = number;
}

void setRestOfNumber(char* forwardedNumber, char const *initialNum, size_t initialNumSize, size_t maxPrefSize, size_t forwardingSize) {
    for (size_t i=0; i < initialNumSize - maxPrefSize; ++i){
        forwardedNumber[forwardingSize + i] = initialNum[maxPrefSize + i];
    }
}

char* getNumber(PhoneNumbers const *pnum, Trie tr, size_t index) {
    char* initNumber = pnum->initNumber;
    size_t forwardingLen = tr->depth;
    size_t forwardedLen = tr->forwardCounter;

    char* number = calloc(forwardingLen + strlen(initNumber) - forwardedLen + 1, sizeof(char));
    if (number == NULL) { return NULL; }

    getNumberFromTrie(tr, number, tr->depth);
    setRestOfNumber(number, initNumber, strlen(initNumber), forwardedLen, forwardingLen);

    addNumbersPtrToArray(pnum, number, index);

    return number;
}
