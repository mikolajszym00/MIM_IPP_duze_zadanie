#include "deleting_trie.h"

bool IsTrieDeeper(Trie tr) {
    Trie *arr = tr->arrayOfTries;

    for (int i = 0; i < NUM; ++i) {
        if (arr[i] != NULL) { return true; }
    }
    return false;
}

Trie findUnusedTrie(Trie tr) {
    if (IsTrieDeeper(tr)) { return NULL; }

    Trie* arr;

    char value;
    char prevValue = '1';

    while (true) {
        value = tr->upIndex;
        if (tr->up == NULL) { return tr; } else { tr = tr->up; }

        arr = tr->arrayOfTries;

        if (arr[value - '0']->forward != NULL || arr[value - '0']->forwardCounter > 0) {
            Trie tr2 = arr[value - '0'];
            Trie* arr2 = tr2->arrayOfTries;

            Trie temp = arr2[prevValue - '0'];
            arr2[prevValue - '0'] = NULL;

            return temp;
        }

        for (int i = 0; i < NUM; ++i) {
            if (arr[i] != NULL && value - '0' != i) {
                Trie temp =  arr[value - '0'];
                arr[value - '0'] = NULL;

                return temp;
            }
        }

        prevValue = value;
    }
}

void deleteTrie(Trie tr) {
    if (tr != NULL) {
        Trie *arr = tr->arrayOfTries;
        for (int i = 0; i < NUM; ++i) {
            deleteTrie(arr[i]);
        }
        free(arr);
        free(tr);
    }
}

void deleteForwardTrie(Trie oldForwardingEnd) {
    if (oldForwardingEnd != NULL) {
        --oldForwardingEnd->forwardCounter;

        Trie unusedTrie = findUnusedTrie(oldForwardingEnd);
        deleteTrie(unusedTrie);
    }
}
