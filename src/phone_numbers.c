#include "phone_numbers.h"
#include "forward.h" // nieeee

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

void addNumbersPtrToArray(PhoneNumbers const *pnum, char* number) {
    char** arr = pnum->arrayOfNumbers;
    arr[0] = number;
}

//void setRestOfNumber(char* forwardedNumber, char const *initialNum, size_t initialNumSize, size_t maxPrefSize, size_t forwardingSize) {
//    for (size_t i=0; i < initialNumSize - maxPrefSize; ++i){
//        forwardedNumber[forwardingSize + i] = initialNum[maxPrefSize + i];
//    }
//}

char* getNumber(PhoneNumbers const *pnum, Trie tr) {
    char* initNumber = pnum->initNumber;
    size_t forwardingLen = tr->depth;
    size_t forwardedLen = tr->forwardCounter;

//    if (tr->forwardCounter == 100) { maxPrefSize = 0; }
//    else { maxPrefSize = tr->forwardCounter; }


    char* number = calloc(forwardingLen + strlen(initNumber) - forwardedLen, sizeof(char));
    if (number == NULL) { return NULL; } // moze tak

//    printf("len %zd\n", forwardingLen + strlen(initNumber) - forwardedLen);
    getNumberFromTrie(tr, number, forwardingLen - 1);

//    printf("strlen %zd\n", strlen(initNumber));
//    printf("tr %zd\n", forwardedLen);
//    printf("for %zd\n", forwardingLen);

    setRestOfNumber(number, initNumber, strlen(initNumber), forwardedLen, forwardingLen);

//    printf("num %zd\n", strlen(number));
//    for (size_t i=tr->forwardCounter; i<initNumberRestLen+tr->forwardCounter; i++) {
//        number[i] = initNumber[i-tr->forwardCounter];
//    }

    addNumbersPtrToArray(pnum, number); // źle!!!

    return number;
}
