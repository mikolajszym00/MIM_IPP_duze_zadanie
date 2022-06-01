#include "reverse_functions.h"

Trie preparePhoneTrie(char const* num, Trie* numberEnd) {
    Trie phoneTrie = trieNew(NULL, NULL, 0, 'r');
    if (phoneTrie == NULL) { return NULL; }

    Trie numEnd = addNumber(phoneTrie, num);

    if (numEnd == NULL) { return NULL; }
    numEnd->forwardCounter = strlen(num);
    *numberEnd = numEnd;

    return phoneTrie;
}

Trie* findForwardedNumPrefInPF(Trie trieOfForwards, char const *num, size_t* nForwarded, size_t* forwardCounter) {
    Trie* forwardedNumPrefs = calloc(strlen(num), sizeof(Trie)); // czy działa jeśli kazdy element ma przekierowanie

    findForwardedNumPrefInTrie(forwardedNumPrefs, nForwarded, trieOfForwards, num, forwardCounter);

//    printf("%zd\n", forwardedNumPrefs[0]->forwardCounter);
//    printf("%c\n", forwardedNumPrefs[0]->up->up->upIndex);
//    realloc() // !!

    return forwardedNumPrefs;
}

void checkPrefs(Trie tr, Trie phoneTrie, Trie* forwardedNumPrefs, size_t* nForwarded) {
    if (tr->forward == NULL) { return; }

    for (size_t i=0; i<*nForwarded; i++) {
        if (tr->forward == forwardedNumPrefs[i]) {
            char* newNum = calloc(tr->depth+1, sizeof(char));

            getNumberFromTrie(tr, newNum); // , tr->depth-1// całkiem podobne do prepare phone trie

//            printf("%s\n", newNum);

//            Trie phoneTrieEnd = goToNumberEndTrie(tr, newNum);

//            if (phoneTrieEnd == NULL) {printf("erer");}
//            printf("%zd", phoneTrieEnd->forwardCounter);

            Trie numEnd = addNumber(phoneTrie, newNum);

            free(newNum);

            if (numEnd == NULL) { return; }

            numEnd->forwardCounter = tr->forward->depth;

//            if (tr->forward->depth == 0) { numEnd->forwardCounter = 100; }
//            else { numEnd->forwardCounter = tr->forward->depth; }
        }
    }
}

void addForwardsFromPFToPhoneTrie(Trie trieOfForwards, Trie phoneTrie, Trie* forwardedNumPrefs, size_t* nForwarded) {
    searchTrie(trieOfForwards, phoneTrie, checkPrefs, forwardedNumPrefs, nForwarded);
}

bool checkBelow(Trie tr, Trie numberEnd) {
//     printf("1 ");

    Trie* arr = tr->arrayOfTries;
    if (arr == NULL || numberEnd->depth == tr->forwardCounter) {
//        printf("2 ");
        return true; }

    char* restOfNum = calloc(numberEnd->depth - tr->forwardCounter + 1, sizeof(char)); // +- 1
    if (restOfNum == NULL) {
//        printf("3 ");
        return true; } // troche nie prawda
//    char* newNum = calloc(tr->forwardCounter+1, sizeof(char));

//    getNumberFromTrie(tr, newNum); // , tr->depth-1// całkiem podobne do prepare phone trie

//    printf("------------------\n");
//    printf("number: %s\n", newNum);
//
//    printf("numend depth %zd\n", numberEnd->depth);
//    printf("tr depth %zd\n", tr->forwardCounter);

//    char* newnumberEnd = calloc(numberEnd->depth+1, sizeof(char));
//
//    getNumberFromTrie(numberEnd, newnumberEnd);
//
//    printf("---------aa--------\n");
//    printf("number: %s\n", newnumberEnd);


    getNumberFromTrieWithStop(numberEnd, numberEnd->depth - tr->forwardCounter, restOfNum);
//    printf("3.6 \n");
//


//    printf("rest number: %s\n", restOfNum);

//    char* newNum = calloc(tr->depth+1, sizeof(char));
//
//    getNumberFromTrie(tr, newNum); // , tr->depth-1// całkiem podobne do prepare phone trie

//    printf("number: %s\n", restOfNum);

//
//    printf("%c\n", restOfNum[0]);

    int restOfNumValue;
    getInteger(&restOfNumValue, restOfNum[0]);
//    printf("asddd");
//
//    printf("restof numb %d\n", restOfNumValue);
//    if (arr[3] != NULL) {printf("nie maaa!\n"); }
//    printf("------------------\n");
    for (int i=0; i<=restOfNumValue; i++) {
        if (arr[i] != NULL) {
            Trie newEnd = addNumber(tr, restOfNum);
            newEnd->forwardCounter = numberEnd->depth; // +- 1
            tr->forwardCounter = 0;

//            printf("4 ");
            free(restOfNum);
            return false;
        }
    }

//    printf("5 ");
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
