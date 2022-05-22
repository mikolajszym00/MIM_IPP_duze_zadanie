#include "adding_functions.h"
#include "stdint.h"

Trie addNumber(Trie tr, char const *num1){
    Trie* arr = tr->arrayOfTries;

    size_t n = strlen(num1);
    if (n == 0) { return NULL; }

    int num;
    for (size_t i = 0; i < n; ++i) {
        if (!getInteger(&num, num1[i])) { return NULL; }

        if (arr[num] == NULL) {
            arr[num] = trieNew(NULL, tr, 1+(tr->depth), num1[i]);
        }

        tr = arr[num];
        if (tr == NULL || arr == NULL) { return NULL; }
        arr = tr->arrayOfTries;
    }
    return tr;
}

bool addForwarding(Trie numberEnd, Trie tr, char const *num2) {
    Trie forwardingEnd = addNumber(tr, num2);
    if (forwardingEnd == NULL) { return false; }

    deleteForwardTrie(numberEnd->forward);

    numberEnd->forward = forwardingEnd;
    ++forwardingEnd->forwardCounter;

    return true;
}
