#include "trie.h"

Trie trieNew(Trie forward, Trie up, size_t depth, char upIndex) {
    Trie tr = malloc(sizeof(struct Node));
    if (tr == NULL) { return NULL; }

    tr->arrayOfTries = calloc(NUM, sizeof(Trie));
    tr->forwardCounter = 0;
    tr->forward = forward;
    tr->up = up;
    tr->depth = depth;
    tr->upIndex = upIndex;

    return tr;
}

void getNumberFromTrie(Trie tr, char* number, size_t stop) {
    for (size_t i=0; i<stop; ++i) {
        number[stop - 1 - i] = tr->upIndex;

        if (tr->depth > 0) {
            tr = tr->up;
        }
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

void findForwardedNumPrefInTrie(Trie tr, Trie* forwardedNumPrefs, size_t* freeIndex, char const* num, size_t* forwardCounter) {
    int index;

    Trie* arr = tr->arrayOfTries;

    for (size_t i = 0; i < strlen(num); ++i){
        if (!getInteger(&index, num[i])) { return; }
        if (arr[index] == NULL) { return; }

        tr = arr[index];

        if (tr->forwardCounter > 0) {
            *forwardCounter += tr->forwardCounter;

            forwardedNumPrefs[*freeIndex] = tr;
            ++(*freeIndex);
        }

        arr = tr->arrayOfTries;
    }
}

void searchTrie(Trie tr, Trie phoneTrie, void (*searchFunc)(Trie, Trie, Trie*, size_t*), Trie* trieArray, size_t* value) {
    searchFunc(tr, phoneTrie, trieArray, value);
    Trie* arr = tr->arrayOfTries;

    for (int i=0; i<NUM; i++) {
        if (arr[i] != NULL) {
            searchTrie(arr[i], phoneTrie, searchFunc, trieArray, value);
        }
    }

}
