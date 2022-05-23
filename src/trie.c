#include "trie.h"

Trie trieNew(Trie forward, Trie up, size_t depth, char upIndex) {
    Trie tr = malloc(sizeof(struct Node));
    if (tr == NULL) { return NULL; }

    tr->arrayOfTries = calloc(10, sizeof(Trie));
    tr->forwardCounter = 0;
    tr->forward = forward;
    tr->up = up;
    tr->depth = depth;
    tr->upIndex = upIndex;

    return tr;
}

void getNumberFromTrie(Trie tr, char* number, size_t i) {
    if (tr->depth > 0){
        number[i] = tr->upIndex;

        --i;
        getNumberFromTrie(tr->up, number, i);
    }
}

Trie goToNumberEndTrie(Trie tr, char const* num) {
    int index;

    Trie* arr = tr->arrayOfTries;
    for (size_t i = 0; i < strlen(num); ++i){
        if (!getInteger(&index, num[i])) { return NULL; }
        if (arr[index] == NULL) { return NULL; }

        tr = arr[index];
        arr = tr->arrayOfTries;
    }
    return tr;
}

void findForwardedNumPrefInTrie(Trie* forwardedNumPrefs, Trie tr, char const* num) {
    size_t freeIndex = 0;
    int index;

    Trie* arr = tr->arrayOfTries;

    for (size_t i = 0; i < strlen(num); ++i){
        if (!getInteger(&index, num[i])) { return; } // addNumber zapewnił wcześniej ze num zawiera tylko ok wartości
        if (arr[index] == NULL) { return; }

        tr = arr[index];

        if (tr->forwardCounter > 0) { // czy jesli przekierowanie jest na piewrszym to zadziała
            forwardedNumPrefs[freeIndex] = tr;
            ++freeIndex;
        }

        arr = tr->arrayOfTries;
    }
}
