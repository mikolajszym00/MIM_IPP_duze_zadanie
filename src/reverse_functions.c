#include "reverse_functions.h"

Trie preparePhoneTrie(char const* num, Trie* numberEnd) {
    Trie phoneTrie = trieNew(NULL, NULL, 0, 'r');
    if (phoneTrie == NULL)
        return NULL;

    Trie numEnd = addNumber(phoneTrie, num);

    if (numEnd == NULL)
        return NULL;

    numEnd->forwardCounter = strlen(num);
    *numberEnd = numEnd;

    return phoneTrie;
}

Trie* findForwardedNumPrefInPF(Trie trieOfForwards, char const *num, size_t* freeIndex, size_t* forwardCounter) {
    Trie* forwardedNumPrefs = calloc(strlen(num), sizeof(Trie));

    findForwardedNumPrefInTrie(trieOfForwards, forwardedNumPrefs, freeIndex, num, forwardCounter);

    return forwardedNumPrefs;
}

void checkPrefs(Trie tr, Trie phoneTrie, Trie* forwardedNumPrefs, size_t* nForwarded) {
    if (tr->forward == NULL)
        return;

    for (size_t i = 0; i < *nForwarded; i++) {
        if (tr->forward == forwardedNumPrefs[i]) {
            char* newNum = calloc(tr->depth + 1, sizeof(char));

            getNumberFromTrie(tr, newNum, tr->depth);

            Trie numEnd = addNumber(phoneTrie, newNum);
            free(newNum);

            if (numEnd == NULL)
                return;
            numEnd->forwardCounter = tr->forward->depth;
        }
    }
}

void addForwardsFromPFToPhoneTrie(Trie trieOfForwards, Trie phoneTrie, Trie* forwardedNumPrefs, size_t* nForwarded) {
    searchTrie(trieOfForwards, phoneTrie, checkPrefs, forwardedNumPrefs, nForwarded);
}

bool checkBelow(Trie tr, Trie numberEnd) {
    Trie* arr = tr->arrayOfTries;
    if (arr == NULL || numberEnd->depth == tr->forwardCounter)
        return true;

    char* restOfNum = calloc(numberEnd->depth - tr->forwardCounter + 1, sizeof(char));
    if (restOfNum == NULL)
        return true;

    getNumberFromTrie(numberEnd, restOfNum, numberEnd->depth - tr->forwardCounter);

    int restOfNumValue;
    getInteger(&restOfNumValue, restOfNum[0]);

    for (int i = 0; i <= restOfNumValue; i++) {
        if (arr[i] != NULL) {
            Trie newEnd = addNumber(tr, restOfNum);
            newEnd->forwardCounter = numberEnd->depth;
            tr->forwardCounter = 0;

            free(restOfNum);
            return false;
        }
    }

    free(restOfNum);
    return true;
}

void findNumEnds(Trie tr, Trie numberEnd, Trie* arrayOfNumbersEnd, size_t* index) {
    if (tr->forwardCounter != 0) {
        if (checkBelow(tr, numberEnd)) {
            arrayOfNumbersEnd[*index] = tr;
            ++(*index);
        }
    }
}

Trie* createArrNumbersLexSorted(Trie phoneTrie, Trie numberEnd, size_t forwardCounter) {
    Trie* arrayOfNumbersEnd = calloc(forwardCounter, sizeof(Trie));

    size_t index = 0;
    searchTrie(phoneTrie, numberEnd, findNumEnds, arrayOfNumbersEnd, &index);

    return arrayOfNumbersEnd;
}
