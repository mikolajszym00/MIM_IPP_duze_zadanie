#include "phone_forward.h"

PhoneForward* phfwdNew() {
    Trie tr = trieNew(NULL, NULL, 0, 'q');
    if (tr == NULL)
        return NULL;

    PhoneForward* pf = malloc(sizeof(struct PhoneForward));
    if (pf == NULL)
        return NULL;

    pf->trieOfForwards = tr;
    return pf;
}

bool phfwdAdd(PhoneForward *pf, char const *num1, char const *num2) {
    if (pf == NULL || num1 == NULL || num2 == NULL || strcmp(num1, num2) == 0)
        return false;

    Trie tr = pf->trieOfForwards;

    Trie numberEnd = addNumber(tr, num1);
    if (numberEnd == NULL)
        return false;

    return addForwarding(numberEnd, tr, num2);
}

PhoneNumbers* phfwdGet(PhoneForward const *pf, char const *num) {
    if (num == NULL && pf != NULL)
        return phnumNew(0, NULL, NULL, NULL);
    if (num == NULL || pf == NULL)
        return NULL;

    if (num[0] == 0 || !checkNum(num))
        return phnumNew(0, NULL, NULL, NULL);

    Trie trieOfNumbers = trieNew(NULL, NULL, 0, 'e');
    if (trieOfNumbers == NULL || trieOfNumbers->arrayOfTries == NULL)
        return NULL;

    char* numCopy = calloc(strlen(num) + 1, sizeof(char));
    if (numCopy == NULL)
        return NULL;

    copyNumber(numCopy, num);

    return createPhoneNumbersGet(pf->trieOfForwards, trieOfNumbers, numCopy);
}

char const *phnumGet(PhoneNumbers const *pnum, size_t idx) {
    if (pnum == NULL || idx >= pnum->numberOfTries)
        return NULL;

    Trie* arr = pnum->arrayOfNumbersEnd;
    if (arr == NULL)
        return NULL;

    Trie tr = arr[idx];
    if (tr == NULL)
        return NULL;

    return getNumber(pnum, tr, idx);
}

void phfwdRemove(PhoneForward *pf, char const *num) {
    if (pf == NULL || num == NULL)
        return;

    Trie tr = pf->trieOfForwards;

    tr = goToNumberEndTrie(tr, num);

    removeForwards(tr);
}

PhoneNumbers* phfwdReverse(PhoneForward const *pf, char const *num) {
    if (pf != NULL && num == NULL )
        return phnumNew(0, NULL, NULL, NULL);
    if (pf == NULL || num == NULL)
        return NULL;

    if (num[0] == 0 || !checkNum(num))
        return phnumNew(0, NULL, NULL, NULL);

    char* numCopy = calloc(strlen(num) + 1, sizeof(char));
    if (numCopy == NULL)
        return NULL;

    copyNumber(numCopy, num);

    Trie numberEnd;
    Trie phoneTrie = preparePhoneTrie(num, &numberEnd);
    if (phoneTrie == NULL)
        return NULL;

    size_t nForwarded = 0;
    size_t forwardCounter = 1;

    Trie* forwardedNumPrefs = findForwardedNumPrefInPF(pf->trieOfForwards, num, &nForwarded, &forwardCounter);
    addForwardsFromPFToPhoneTrie(pf->trieOfForwards, phoneTrie, forwardedNumPrefs, &nForwarded);
    free(forwardedNumPrefs);

    Trie* arrayOfNumbersEnd = createArrNumbersLexSorted(phoneTrie, numberEnd, forwardCounter);

    return phnumNew(forwardCounter, phoneTrie, arrayOfNumbersEnd, numCopy);
}

PhoneNumbers * phfwdGetReverse(PhoneForward const *pf, char const *num) {
    PhoneNumbers* pnumRev = phfwdReverse(pf, num);
    if (pnumRev == NULL)
        return NULL;

    Trie* trieArray = pnumRev->arrayOfNumbersEnd;
    size_t next = 0;

    Trie* newTrieArray = calloc(pnumRev->numberOfTries+1, sizeof(Trie));

    for (size_t i = 0; i < pnumRev->numberOfTries; i++) {
        PhoneNumbers* t = phfwdGet(pf, phnumGet(pnumRev, i));

        char const* nullCheck = phnumGet(t, 0);

        if (nullCheck != NULL && strcmp(nullCheck, num) == 0) {
            newTrieArray[next] = trieArray[i];
            ++next;
        }

        phnumDelete(t);
    }

    for (size_t i = 0; i < pnumRev->numberOfTries; i++) {
        if ((pnumRev->arrayOfNumbers)[i] != NULL) {
            free((pnumRev->arrayOfNumbers)[i]);
            (pnumRev->arrayOfNumbers)[i] = NULL;
        }
    }

    free(pnumRev->arrayOfNumbersEnd);

    pnumRev->arrayOfNumbersEnd = newTrieArray;

    return pnumRev;
}

void phfwdDelete(PhoneForward *pf){
    if (pf == NULL)
        return;

    deleteTrie(pf->trieOfForwards);
    free(pf);
}

void phnumDelete(PhoneNumbers *pnum){
    if (pnum == NULL)
        return;

    deleteTrie(pnum->trieOfNumbers);
    if (pnum->arrayOfNumbersEnd != NULL && (pnum->arrayOfNumbersEnd)[0] != NULL) {
        for (size_t i = 0; i < pnum->numberOfTries; i++) {
            free((pnum->arrayOfNumbers)[i]);
        }
    }

    free(pnum->initNumber);
    free(pnum->arrayOfNumbers);
    free(pnum->arrayOfNumbersEnd);

    free(pnum);
}
