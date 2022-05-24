#include "reverse_functions.h"

Trie preparePhoneTrie(char const* num) {
    Trie phoneTrie = trieNew(NULL, NULL, 0, 'r');

    char* reversedNum = reverseNum(num);

    if (phoneTrie == NULL) { return NULL; }
    Trie numBegin = addNumber(phoneTrie, reversedNum);
    free(reversedNum);

    if (numBegin == NULL) { return NULL; }
    numBegin->forwardCounter = 1;

    return phoneTrie;
}

Trie* findForwardedNumPrefInPF(Trie trieOfForwards, char const *num, size_t* nForwarded, size_t* forwardCounter) {
    Trie* forwardedNumPrefs = malloc(sizeof(Trie)*(strlen(num)+1)); // czy działa jeśli kazdy element ma przekierowanie

    findForwardedNumPrefInTrie(forwardedNumPrefs, nForwarded, trieOfForwards, num, forwardCounter);

//    realloc() // !!

    return forwardedNumPrefs;
}

void checkPrefs(Trie tr, Trie* forwardedNumPrefs, size_t* nForwarded) {
    if (tr->forward == NULL) { return; }

    for (size_t i=0; i<*nForwarded; i++) {
        if (tr->forward == forwardedNumPrefs[i]) {
            char* newNum = calloc(tr->depth+1, sizeof(char));

            getNumberFromTrie(tr, newNum, tr->depth-1); // całkiem podobne do prepare phone trie

            Trie numEnd = addNumber(forwardedNumPrefs[i], newNum);

            free(newNum);

            if (numEnd == NULL) { return; }
            numEnd->forwardCounter = 1;
        }
    }

}

void addForwardsFromPFToPhoneTrie(Trie trieOfForwards, Trie phoneTrie, Trie* forwardedNumPrefs, size_t* nForwarded) {
    searchTrie(trieOfForwards, checkPrefs, forwardedNumPrefs, nForwarded);
}

void findNumEnds(Trie tr, Trie* arrayOfNumbersEnd, size_t* index) {
    if (tr->forwardCounter == 1) {
        arrayOfNumbersEnd[*index] = tr;
        ++(*index);
    }
}

Trie* createArrNumbersLexSorted(Trie phoneTrie, size_t forwardCounter) {
    Trie* arrayOfNumbersEnd = calloc(forwardCounter, sizeof(Trie));

    size_t index = 0;
    searchTrie(phoneTrie, findNumEnds, arrayOfNumbersEnd, &index);

    return arrayOfNumbersEnd;
}
