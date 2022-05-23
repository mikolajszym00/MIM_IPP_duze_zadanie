#ifndef PHONE_NUMBERS_REVERSE_FUNTIONS_H
#define PHONE_NUMBERS_REVERSE_FUNTIONS_H

#include "trie.h"
#include "phone_forward.h"

// przygotowuje nowe drzewo
Trie preparePhoneTrie(char const* num);

// zwraca tablice tych co przekierowują
Trie* findForwardedNumPrefInPF(PhoneForward const *pf, char const *num);

// przelatuje drzewo w pf, dodaje elementy do phone trie
void addForwardsFromPFToPhoneTrie(PhoneForward const *pf, Trie phoneTrie, Trie* forwardedNumPrefs);

// tworzy leksykograficzną talbicę końców
Trie* createArrNumbersLexSorted(Trie phoneTrie)

#endif //PHONE_NUMBERS_REVERSE_FUNTIONS_H
