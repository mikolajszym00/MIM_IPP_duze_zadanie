#include "deleting_trie.h"

bool IsTrieDeeper(Trie tr) {
    Trie *arr = tr->arrayOfTries;

    for (int i = 0; i < NUM; ++i) {
        if (arr[i] != NULL)
            return true;
    }
    return false;
}

Trie findUnusedTrie(Trie tr) {
    if (IsTrieDeeper(tr))
        return NULL;

    Trie* arr;

    char value;
    int prevValue = 1;

    while (true) {
        value = tr->upIndex;

        if (tr->up == NULL)
            return tr;
        else
            tr = tr->up;

        arr = tr->arrayOfTries;

        int num;
        getInteger(&num, value);

        if (arr[num]->forward != NULL || arr[num]->forwardCounter > 0) {
            Trie tr2 = arr[num];
            Trie* arr2 = tr2->arrayOfTries;
            Trie temp = arr2[prevValue];
            arr2[prevValue] = NULL;

            return temp;
        }

        for (int i = 0; i < NUM; ++i) {
            if (arr[i] != NULL && num != i) {
                Trie temp = arr[num];
                arr[num] = NULL;

                return temp;
            }
        }

        prevValue = num;
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
        --(oldForwardingEnd->forwardCounter);

        Trie unusedTrie = findUnusedTrie(oldForwardingEnd);
        deleteTrie(unusedTrie);

        unusedTrie = NULL;
    }
}
