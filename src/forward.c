#include "forward.h"

Trie findMaxForward(Trie* arr, size_t i, char const *numToFind, Trie maxPref, bool* isNumCorrect){
    Trie forward;

    if (strlen(numToFind) <= i) { return maxPref; }

    int index;
    *isNumCorrect = getInteger(&index, numToFind[i]);
    if (!(*isNumCorrect)) { return NULL; }

    if (arr[index]){
        forward = arr[index] -> forward;

        if (forward) { maxPref = arr[index]; }

        arr = arr[index]->arrayOfTries;
        ++i;

        maxPref = findMaxForward(arr, i, numToFind, maxPref, isNumCorrect);
    }
    return maxPref;
}

Trie setForwardingEndAndSizes(Trie maxPref, size_t* forwardingSize) {
    Trie forwardingEnd;
    if (maxPref == NULL) {
        forwardingEnd = NULL;
        *forwardingSize = 100;
//        *forwardingSize = 0;
    } else {
        forwardingEnd = maxPref->forward;
        *forwardingSize = maxPref->depth;
//        if (maxPref->depth == 0) { *forwardingSize = 100; }
//        else { *forwardingSize = maxPref->depth; }
//        printf("fsize %zd\n", maxPref->depth);
    }

    return forwardingEnd;
}

void setForwardingInNumber(Trie forwardElement, char* forwardedNumber, size_t forwardingSize) {
    if (forwardElement == NULL) {return;}

    for (size_t i=1; i <= forwardingSize; ++i){
        forwardedNumber[forwardingSize - i] = forwardElement->upIndex;
        forwardElement = forwardElement->up;
    }
}

void setRestOfNumber(char* forwardedNumber, char const *initialNum, size_t initialNumSize, size_t maxPrefSize, size_t forwardingSize) {
    for (size_t i=0; i < initialNumSize - maxPrefSize; ++i){
        forwardedNumber[forwardingSize + i] = initialNum[maxPrefSize + i];
    }
}

char* getForwardedNumber(Trie tr, char const *initialNum, size_t initialNumSize, size_t* numberSplitIndex) {
    Trie *arr = tr->arrayOfTries;

    bool isNumCorrect;
    Trie maxPref = findMaxForward(arr, 0, initialNum, NULL, &isNumCorrect);

    if (!isNumCorrect) { return NULL; }

    Trie forwardedPart = setForwardingEndAndSizes(maxPref, numberSplitIndex);
    if (forwardedPart == NULL) { return calloc(1, sizeof(char)); }

    char *maxPrefChar = calloc(*numberSplitIndex + 1, sizeof(char)); //maxPref->depth
    if (maxPrefChar == NULL) { return NULL; }

    getNumberFromTrie(forwardedPart, maxPrefChar, forwardedPart->depth - 1);

    return maxPrefChar;
}

//    size_t maxPrefSize, numberSplitIndex;
//    size_t solNumberSize = numberSplitIndex + initialNumSize - maxPrefSize;
//
//    char* forwardedNumber = calloc(solNumberSize+1, sizeof(char));
//    if (forwardedNumber == NULL) { return NULL; }
//
//    setForwardingInNumber(forwardingEnd, forwardedNumber, numberSplitIndex);
//    setRestOfNumber(forwardedNumber, initialNum, initialNumSize, maxPrefSize, numberSplitIndex);
//
//    return forwardedNumber;


void removeForwards(Trie tr){
    if (tr != NULL) {
        if (tr->forward) {
            deleteForwardTrie(tr->forward);
            tr->forward = NULL;
        }

        Trie* arr = tr->arrayOfTries;
        for (int i = 0; i < 10; ++i) {
            removeForwards(arr[i]);
        }
    }
}
