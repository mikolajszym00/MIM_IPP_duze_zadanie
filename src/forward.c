#include "forward.h"

Trie findMaxForward(Trie* arr, size_t i, char const *numToFind, Trie maxPref, bool* isNumCorrect){
    Trie forward;

    if (strlen(numToFind) <= i)
        return maxPref;

    int index;
    *isNumCorrect = getInteger(&index, numToFind[i]);
    if (!(*isNumCorrect))
        return NULL;

    if (arr[index]){
        forward = arr[index] -> forward;

        if (forward)
            maxPref = arr[index];

        arr = arr[index]->arrayOfTries;
        ++i;

        maxPref = findMaxForward(arr, i, numToFind, maxPref, isNumCorrect);
    }
    return maxPref;
}

Trie setForwardingEndAndSizes(Trie maxPref, size_t* numberSplitIndex) {
    Trie forwardingEnd;
    if (maxPref == NULL) {
        forwardingEnd = NULL;
        *numberSplitIndex = 0;
    } else {
        forwardingEnd = maxPref->forward;
        *numberSplitIndex = maxPref->depth;
    }

    return forwardingEnd;
}

char* getForwardedNumber(Trie tr, char const *initialNum, size_t* numberSplitIndex) {
    Trie *arr = tr->arrayOfTries;

    bool isNumCorrect;
    Trie maxPref = findMaxForward(arr, 0, initialNum, NULL, &isNumCorrect);

    if (!isNumCorrect)
        return NULL;

    Trie forwardedPart = setForwardingEndAndSizes(maxPref, numberSplitIndex);
    if (forwardedPart == NULL)
        return calloc(1, sizeof(char));

    char *maxPrefChar = calloc(forwardedPart->depth + 1, sizeof(char));
    if (maxPrefChar == NULL)
        return NULL;

    getNumberFromTrie(forwardedPart, maxPrefChar, forwardedPart->depth);

    return maxPrefChar;
}

void removeForwards(Trie tr){
    if (tr != NULL) {
        if (tr->forward) {
            deleteForwardTrie(tr->forward);
            tr->forward = NULL;
        }

        Trie* arr = tr->arrayOfTries;
        for (int i = 0; i < NUM; ++i) {
            removeForwards(arr[i]);
        }
    }
}
