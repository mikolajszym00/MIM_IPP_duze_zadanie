#include "phone_forward.h"

PhoneForward* phfwdNew() {
    Trie tr = trieNew(NULL, NULL, 0, 'q');
    if (tr == NULL) { return NULL; }

    PhoneForward* pf = malloc(sizeof(struct PhoneForward));
    if (pf == NULL) { return NULL; }

    pf->trieOfForwards = tr;
    return pf;
}

bool phfwdAdd(PhoneForward *pf, char const *num1, char const *num2) {
    if (pf == NULL || num1 == NULL || num2 == NULL || strcmp(num1, num2) == 0) { return false; }

    Trie tr = pf->trieOfForwards;

    Trie numberEnd = addNumber(tr, num1);
    if (numberEnd == NULL) { return false; }

    return addForwarding(numberEnd, tr, num2);
}

PhoneNumbers* phfwdGet(PhoneForward const *pf, char const *num) {
    if (num == NULL && pf != NULL) { return phnumNew(0, NULL, NULL, NULL); } // || (num == NULL && pf == NULL)
    if (num == NULL || pf == NULL) { return NULL; }

    if (strlen(num) == 0 || !checkNum(num)) { return phnumNew(0, NULL, NULL, NULL); }

    Trie trieOfNumbers = trieNew(NULL, NULL, 0, 'e');
    if (trieOfNumbers == NULL || trieOfNumbers->arrayOfTries == NULL) { return NULL; } // problemy z alokacja

    char* numCopy = calloc(strlen(num)+1, sizeof(char));
    if (numCopy == NULL) { return NULL; }
    copyNumber(numCopy, num);

//    printf("copy %zd\n", strlen(numCopy));
//    printf("num %zd\n", strlen(num));

    Trie* arrayOfNumbersEnd = calloc(1, sizeof(Trie));

    size_t numberSplitIndex;
    char* forwardPref = getForwardedNumber(pf->trieOfForwards, num, strlen(num), &numberSplitIndex);
    if (forwardPref == NULL) { return NULL; }

    Trie numberPtr;

    if (strlen(forwardPref) == 0) { numberPtr = trieOfNumbers; }
    else { numberPtr = addNumber(trieOfNumbers, forwardPref); }

    if (numberPtr == NULL) { return NULL; }

    arrayOfNumbersEnd[0] = numberPtr;
    numberPtr->forwardCounter = numberSplitIndex;

    free(forwardPref);

    PhoneNumbers* pn = phnumNew(1, trieOfNumbers, arrayOfNumbersEnd, numCopy); // może nie robić numCopy
    if (pn->arrayOfNumbers == NULL) { return NULL; }

    return pn;
}

char const *phnumGet(PhoneNumbers const *pnum, size_t idx) {
    if (pnum == NULL || idx >= pnum->numberOfTries) { return NULL; }

    Trie* arr = pnum->arrayOfNumbersEnd;
    if (arr == NULL) { return NULL; }

    Trie tr = arr[idx];
    if (tr == NULL) { return NULL; }
//    printf("nTreis %zd\n", pnum->numberOfTries);

    return getNumber(pnum, tr);
}

void phfwdRemove(PhoneForward *pf, char const *num) {
    if (pf == NULL || num == NULL) { return; }

    Trie tr = pf->trieOfForwards;

    tr = goToNumberEndTrie(tr, num);

    removeForwards(tr);
}

PhoneNumbers* phfwdReverse(PhoneForward const *pf, char const *num) {
    if (pf != NULL && num == NULL ) { return phnumNew(0, NULL, NULL, NULL); }
    if (pf == NULL || num == NULL) { return NULL; }

    if (strlen(num) == 0 || !checkNum(num)) { return phnumNew(0, NULL, NULL, NULL); }

    char* numCopy = calloc(strlen(num)+1, sizeof(char));
    if (numCopy == NULL) { return NULL; }
    copyNumber(numCopy, num);

//    printf("numCopy %zd\n", strlen(numCopy));
//    printf("num %zd\n",strlen(num));

//    Trie phoneTrie = trieNew(NULL, NULL, 0, 'r');
//    if (phoneTrie == NULL) { return NULL; }

    Trie numberEnd;
    Trie phoneTrie = preparePhoneTrie(num, &numberEnd); // przygotowuje nowe drzewo
    if (phoneTrie == NULL) { return NULL; }

    size_t nForwarded = 0;
    size_t forwardCounter = 1;

    Trie* forwardedNumPrefs = findForwardedNumPrefInPF(pf->trieOfForwards, num, &nForwarded, &forwardCounter); // zwraca tablice tych co przekierowują
    addForwardsFromPFToPhoneTrie(pf->trieOfForwards, phoneTrie, forwardedNumPrefs, &nForwarded); // przelatuje drzewo w pf, dodaje elementy do phone trie

    free(forwardedNumPrefs);

    Trie* arrayOfNumbersEnd = createArrNumbersLexSorted(phoneTrie, numberEnd, forwardCounter); // tworzy leksykograficzną talbicę końców

//    printf("%c\n", arrayOfNumbersEnd[0]->up->up->upIndex);
//    printf("%c\n", arrayOfNumbersEnd[1]->up->up->upIndex);

//    printf("%zd\n", forwardCounter);
    return phnumNew(forwardCounter, phoneTrie, arrayOfNumbersEnd, numCopy);
}

void phfwdDelete(PhoneForward *pf){
    if (pf == NULL) { return; }

    deleteTrie(pf->trieOfForwards);
    free(pf);
}

void phnumDelete(PhoneNumbers *pnum){
    if (pnum == NULL) { return; }

    deleteTrie(pnum->trieOfNumbers);
    if (pnum->arrayOfNumbersEnd != NULL && (pnum->arrayOfNumbersEnd)[0] != NULL) {
        free((pnum->arrayOfNumbers)[0]);
    }

    free(pnum->arrayOfNumbers);
    free(pnum->arrayOfNumbersEnd);

    free(pnum);
}
