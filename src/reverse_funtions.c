#include "reverse_funtions.h"

char* reverseNum(char const* num) {
    size_t n = strlen(num);

    char* reversedNum = malloc(sizeof(char)*(1+n));

    for (size_t i = 0; i<n; i++) {
        reversedNum[n-1-i] = num[i];
    }

    return reversedNum;
}

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

Trie* findForwardedNumPrefInPF(PhoneForward const *pf, char const *num) {
    Trie* forwardedNumPrefs = malloc(sizeof(Trie)*(strlen(num)+1)); // czy działa jeśli kazdy element ma przekierowanie

    findForwardedNumPrefInTrie(forwardedNumPrefs, pf->trieOfForwards, num);

    return forwardedNumPrefs;
}

void addForwardsFromPFToPhoneTrie(PhoneForward const *pf, Trie phoneTrie, Trie* forwardedNumPrefs) {

}

Trie* createArrNumbersLexSorted(Trie phoneTrie) {


}
