/** @file
 * Interfejs klasy zawierający metody związane ze strukturą drzewa
 *
 * @author Mikołaj Szymański
 * @copyright Uniwersytet Warszawski
 * @date 2022
 */

#ifndef PHONE_NUMBERS_TRIE_H
#define PHONE_NUMBERS_TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "functions.h"

/**
 * Struktura przechowująca numery.
 */
typedef struct Node* Trie;
struct Node {
    Trie* arrayOfTries; ///< wskaźnik na tablice poddrzew
    size_t forwardCounter; ///< ilość numerów, które zostały przekierowane na dany numer
    Trie forward; ///< wskaźnik na węzeł drzewa, na który został przekierowany numer
    Trie up; ///< wskaźnik do węzła opisującego poprzedni element numeru
    size_t depth; ///< głębokość węzła
    char upIndex; ///< znak opisujący poprzedni element numeru
};

/** @brief Tworzy nową strukturę.
 * Tworzy strukturę reprezentującą węzeł drzewa
 * Wyznacza przekierowanie podanego numeru. Szuka najdłuższego pasującego
 * prefiksu. Wynikiem jest ciąg zawierający co najwyżej jeden numer. Jeśli dany
 * numer nie został przekierowany, to wynikiem jest ciąg zawierający ten numer.
 * Jeśli podany napis nie reprezentuje numeru, wynikiem jest pusty ciąg.
 * Alokuje strukturę @p PhoneNumbers, która musi być zwolniona za pomocą
 * funkcji @ref phnumDelete.
 * @param[in] forward  – wskaźnik na przekierowany numer;
 * @param[in] up       – wskaźnik na naddrzewo;
 * @param[in] depth    – wartość głębokości dzewa;
 * @param[in] upIndex  – znak określający indeks naddrzewa na liście.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *         alokować pamięci.
 */
Trie trieNew(Trie forward, Trie up, size_t depth, char upIndex);

/** @brief Przypisuje numerowi wartosci z drzewa.
 * Przypisuje kolejne wartości @p i numerowi @p num na podstawie kolejnych
 * wartości @p tr.
 * @param[in] tr         – wskaźnik na korzeń drzewa;
 * @param[in, out] num   – wskaźnik na napis reprezentujący numer
 *                         telefonu;
 * @param[in] i          – indeks numeru telefonu.
 */
void getNumberFromTrie(Trie tr, char* number, size_t i);

/** @brief Wyszukuje węzeł @p tr, w którym kończy sie @p num.
 * @param[in] tr     – wskaźnik na korzeń drzewa;
 * @param[in] num    – wskaźnik na napis reprezentujący kolejne poziomy
 *                     drzewa.
 * @return Wskaźnik na drzewo lub jeśli którejś z kolejnych wartości @p num
 * nie ma w węzłach @p tr lub @p num zawiera niedozwolony znak zwraca NULL.
 */
Trie goToNumberEndTrie(Trie tr, char const* num);

void findForwardedNumPrefInTrie(Trie* forwardedNumPrefs, size_t* freeIndex, Trie tr, char const* num, size_t* forwardCounter);

void searchTrie(Trie tr, void (*searchFunc)(Trie, Trie*, size_t*), Trie* forwardedNumPrefs, size_t* nForwarded);

#endif //PHONE_NUMBERS_TRIE_H
