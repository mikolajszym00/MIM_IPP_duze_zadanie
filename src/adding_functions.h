/** @file
 * Interfejs klasy zawierającej metody dodające numery do drzewa
 *
 * @author Mikołaj Szymański
 * @copyright Uniwersytet Warszawski
 * @date 2022
 */

#ifndef PHONE_NUMBERS_ADDING_FUNCTIONS_H
#define PHONE_NUMBERS_ADDING_FUNCTIONS_H

#include "trie.h"
#include "deleting_trie.h"

/** @brief Dodaje numer do drzewa.
 * Dodaje kolejne wartości @p num1 jako indeksy tablicy zawartej w kolejnych
 * węzłach @p tr.
 * @param[in] tr     – wskaźnik na strukturę drzewa przechowującą numery;
 * @param[in] num1   – wskaźnik na napis reprezentujący prefiks numerów
 *                     przekierowywanych.
 * @return Wskaźnik na węzeł drzewa, w którym zakończył się numer lub NULL jeśli @p num1
 *         nie reprezentuje numeru, @p num1 ma długość 0 lub jeśli nie udało się zaalokować pamięci.
 */
Trie addNumber(Trie tr, char const *num1);

/** @brief Dodaje przekierowanie do drzewa.
 * Dodaje przekierowanie wszystkich numerów mających prefiks @p num1, na numery,
 * w których ten prefiks zamieniono odpowiednio na prefiks @p num2. Każdy numer
 * jest swoim własnym prefiksem. Jeśli wcześniej zostało dodane przekierowanie
 * z takim samym parametrem @p num1, to jest ono zastępowane. Relacja przekierowania
 * numerów nie jest przechodnia.
 * @param[in] numberEnd   – wskaźnik na węzeł drzewa, do którego ma zostać dołaczone
 *                          przekierowanie;
 * @param[in] tr          – wskaźnik na korzeń drzewa przechowującego numery i przekierowania;
 * @param[in] num2        – wskaźnik na napis reprezentujący przekierowanie numeru.
 * @return Wartość @p true, jeśli przekierowanie zostało dodane.
 *         Wartość @p false, jeśli wystąpił błąd, np. @p num2 nie został dodany do @p tr.
 */
bool addForwarding(Trie numberEnd, Trie tr, char const *num2);

#endif //PHONE_NUMBERS_ADDING_FUNCTIONS_H
