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

void getNumberFromTrie(Trie tr, char* number) {
    for (int i=tr->depth-1; i>=0; --i) { // tu jest int bo nie działa z size_t
        number[i] = tr->upIndex;

        if (tr->depth > 0) {
            tr = tr->up;
        }
    }
}

Trie goToNumberEndTrie(Trie tr, char const* num) {
    int index;

//    printf("%s\n", num);


    Trie* arr = tr->arrayOfTries;
    for (size_t i = 0; i < strlen(num); ++i){
//        printf("%zd\n", i);
        if (!getInteger(&index, num[i])) { return NULL; }
        if (arr[index] == NULL) {
//            printf("ssd\n");
            return NULL; }

        tr = arr[index];
        arr = tr->arrayOfTries;
    }
    return tr;
}

void findForwardedNumPrefInTrie(Trie* forwardedNumPrefs, size_t* freeIndex, Trie tr, char const* num, size_t* forwardCounter) {
    int index;

    Trie* arr = tr->arrayOfTries;

    for (size_t i = 0; i < strlen(num); ++i){
        if (!getInteger(&index, num[i])) { return; } // addNumber zapewnił wcześniej ze num zawiera tylko ok wartości
        if (arr[index] == NULL) { return; }

        tr = arr[index];

        if (tr->forwardCounter > 0) { // czy jesli przekierowanie jest na piewrszym to zadziała
//            char* tree = calloc(tr->depth+1, sizeof(char));
//            getNumberFromTrie(tr, tree, tr->depth-1);
//            printf("%s\n", tree);
//            printf("%s\n", num);
//            printf("forcounter %zd\n", tr->forwardCounter);
            *forwardCounter += tr->forwardCounter;

            forwardedNumPrefs[*freeIndex] = tr;
            ++(*freeIndex);
        }

        arr = tr->arrayOfTries;
    }
}

void searchTrie(Trie tr, Trie phoneTrie, void (*searchFunc)(Trie, Trie, Trie*, size_t*), Trie* forwardedNumPrefs, size_t* nForwarded) { // tr to korzeń
    searchFunc(tr, phoneTrie, forwardedNumPrefs, nForwarded);
    Trie* arr = tr->arrayOfTries;

    for (int i=0; i<10; i++) {
        if (arr[i] != NULL) {
            searchTrie(arr[i], phoneTrie, searchFunc, forwardedNumPrefs, nForwarded);
        }
    }

}
