#ifndef PHONE_NUMBERS_REVERSE_FUNCTIONS_H
#define PHONE_NUMBERS_REVERSE_FUNCTIONS_H

#include "trie.h"
#include "functions.h"
#include "adding_functions.h"

// przygotowuje nowe drzewo
Trie preparePhoneTrie(char const* num, Trie* numberEnd);

// zwraca tablice tych co przekierowują
Trie* findForwardedNumPrefInPF(Trie trieOfForwards, char const *num, size_t* nForwarded, size_t* forwardCounter);

void checkPrefs(Trie tr, Trie phoneTrie, Trie* forwardedNumPrefs, size_t* nForwarded);

void findNumEnds(Trie tr, Trie numberEnd, Trie* arrayOfNumbersEnd, size_t* index);

// przelatuje drzewo w pf, dodaje elementy do phone trie
void addForwardsFromPFToPhoneTrie(Trie trieOfForwards, Trie phoneTrie, Trie* forwardedNumPrefs, size_t* nForwarded);
// tworzy leksykograficzną talbicę końców
Trie* createArrNumbersLexSorted(Trie phoneTrie, Trie numberEnd, size_t forwardCounter);

#endif //PHONE_NUMBERS_REVERSE_FUNCTIONS_H
