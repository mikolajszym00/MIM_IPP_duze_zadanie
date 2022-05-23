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
    if (num == NULL) { return phnumNew(NULL, NULL);}
    if (num == NULL || pf == NULL) { return NULL;}

    Trie trieOfNumbers = trieNew(NULL, NULL, 0, 'e');
    if (trieOfNumbers == NULL || trieOfNumbers->arrayOfTries == NULL) { return NULL; } // problemy z alokacja

    Trie* arrayOfNumbersEnd = calloc(1, sizeof(Trie));

    char* forwardedNumber = getForwardedNumber(pf->trieOfForwards, num, strlen(num));

    Trie numberPtr = addNumber(trieOfNumbers, forwardedNumber);
    arrayOfNumbersEnd[0] = numberPtr;

    free(forwardedNumber);

    PhoneNumbers* pn = phnumNew(trieOfNumbers, arrayOfNumbersEnd);
    if (pn->arrayOfNumbers == NULL) { return NULL; }

    return pn;
}

char const *phnumGet(PhoneNumbers const *pnum, size_t idx) {
    if (pnum == NULL || idx != 0) { return NULL; }

    Trie* arr = pnum->arrayOfNumbersEnd;
    if (arr == NULL) { return NULL; }

    Trie tr = arr[idx];
    if (tr == NULL) { return NULL; }

    char* number = calloc(tr->depth+1, sizeof(char));

    getNumberFromTrie(tr, number, (tr->depth) - 1);

    addNumbersPtrToArray(pnum, number);

    return number;
}

void phfwdRemove(PhoneForward *pf, char const *num) {
    if (pf == NULL || num == NULL) { return; }

    Trie tr = pf->trieOfForwards;

    tr = goToNumberEndTrie(tr, num);

    removeForwards(tr);
}

PhoneNumbers* phfwdReverse(PhoneForward const *pf, char const *num) {
    if (pf == NULL || num == NULL) { return NULL; }

    Trie phoneTrie = preparePhoneTrie(num); // przygotowuje nowe drzewo
    Trie* forwardedNumPrefs = findForwardedNumPrefInPF(pf, num); // zwraca tablice tych co przekierowują
    addForwardsFromPFToPhoneTrie(pf, phoneTrie, forwardedNumPrefs); // przelatuje drzewo w pf, dodaje elementy do phone trie

    Trie* arrayOfNumbersEnd = createArrNumbersLexSorted(phoneTrie); // tworzy leksykograficzną talbicę końców

    // trzeba jeszcze get poprawić

    return phnumNew(phoneTrie, arrayOfNumbersEnd);
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
