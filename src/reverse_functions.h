/** @file
 * Interfejs klasy zawierający metody związane z metodą phfwdReverse
 *
 * @author Mikołaj Szymański
 * @copyright Uniwersytet Warszawski
 * @date 2022
 */

#ifndef PHONE_NUMBERS_REVERSE_FUNCTIONS_H
#define PHONE_NUMBERS_REVERSE_FUNCTIONS_H

#include "trie.h"
#include "functions.h"
#include "adding_functions.h"

/** @brief Przygotowuje nowe drzewo.
 * Tworzy nową strukturę drzewa i dodaje do niego @p num.
 * @param[in,out] num     – ciąg znaków reprezentujący numeru telefonu;
 * @param[in] numberEnd   – wskaźnik na węzeł drzwa zawierający ostatni element
 *                          numeru.
 * @return Wskaźnik na korzeń drzewa zawierającego przekierowania numerów lub NULL
 *         jeśli nie udało się zaalokować pamięci.
 */
Trie preparePhoneTrie(char const* num, Trie* numberEnd);

/** @brief Znajduje prefiksy zawierające przekierowania.
 * Znajduje prefiksy @p num zawierające przekierowania. Umieszcza je w tablicy.
 * @param[in,out] trieOfForwards - wskaźnik na korzeń drzwa zawierający wszystkie
 *                                 przekierowania numerów;
 * @param[in,out] num            – ciąg znaków reprezentujący numeru telefonu;
 * @param[in] freeIndex          – wartość najbliżego wolnego indeksu w tablicy;
 * @param[in] forwardCounter     - licznik przekierowanych numerów.
 * @return Wskaźnik na tablicę drzew, będących prefiksami @p num zawierającymi
 *         przekierowanie lub NULL jeśli nie udało się zaalokować pamięci.
 */
Trie* findForwardedNumPrefInPF(Trie trieOfForwards, char const *num, size_t* freeIndex, size_t* forwardCounter);

/** @brief Dodaje przekierowania numerów do drzewa numerów.
 * Przeszukuje drzewo w poszukiwaniu węzła, którego przekierowaniem jest
 * element @p forwardedNumPrefs. Następnie dodaje przekierowywany numer
 * do @p phoneTrie.
 * @param[in,out] trieOfForwards      - wskaźnik na korzeń drzwa zawierający wszystkie
 *                                      przekierowania numerów;
 * @param[in] phoneTrie               - wskaźnik na korzeń drzwa zawierający prefiksy
 *                                      numerów przekierowanych;
 * @param[in,out] forwardedNumPrefs   – tablica prefiksów przekierowań;
 * @param[in,out] nForwarded          - łączna ilość przekrierowanych numerów na
 *                                      prefiksy @p forwardedNumPrefs.
 */
void addForwardsFromPFToPhoneTrie(Trie trieOfForwards, Trie phoneTrie, Trie* forwardedNumPrefs, size_t* nForwarded);

/** @brief Sortuje leksykograficznie numery.
 * @param[in] phoneTrie           - wskaźnik na korzeń drzwa zawierający prefiksy
 *                                  numerów przekierowanych;
 * @param[in,out] numberEnd       – wskaźnik na węzeł drzwa zawierający ostatni
 *                                  element numeru;
 * @param[in,out] forwardCounter  - łączna ilość numerów w @p phoneTrie.
 */
Trie* createArrNumbersLexSorted(Trie phoneTrie, Trie numberEnd, size_t forwardCounter);

#endif //PHONE_NUMBERS_REVERSE_FUNCTIONS_H
