/** @file
 * Interfejs klasy obsługującej metody związane z przekierowyywaniem
 *
 * @author Mikołaj Szymański
 * @copyright Uniwersytet Warszawski
 * @date 2022
 */

#ifndef PHONE_NUMBERS_FORWARD_H
#define PHONE_NUMBERS_FORWARD_H

#include "trie.h"
#include "deleting_trie.h"

/** @brief Znajduje najdłuższe przekierowanie dla numeru.
 * @param[in] arr            – wskaźnik na tablice poddrzew;
 * @param[in] i              – indeks numeru telefonu;
 * @param[in] numToFind      – wskaźnik na napis reprezentujący numer, dla którego
 *                             ma zostać znalezione najdłuższe przekierownaie;
 * @param[in, out] arr       – wskaźnik na węzeł drzewa opisujący najdłuższe
 *                             znalezione przekierowanie;
 * @param[in] isNumCorrect   – wskaźnik na bool opisujący poprawność znaków w numerze.
 * @return Wskaźnik na węzeł zawierający koniec numeru dla którego istnieje najdłuższe przekierowanie
 * dla @p numToFind w drzewie zawierającym @p arr. Zwraca NULL, gdy nie się alokować
 * pamięci, @p numToFind nie reprezentuje numeru lub jeśli przekierowanie nie istnieje.
 */
Trie findMaxForward(Trie* arr, size_t i, char const *numToFind, Trie maxPref, bool* isNumCorrect);

/** @brief Określa przekierowanie numeru, długość prefiksu i przekierowania.
 * Sprawdza czy maxPref ma wartość NULL, jeśli tak ustawia wartości numer nie ma przekierowania, więc
 * zwracane są wartości pozwalające stworzyć numer idetyczny do wejściowego.
 * @param[in] maxPref                – wskaźnik na węzeł drzwa zawierający ostatni element
 *                                     prefiksu;
 * @param[in, out] numberSplitIndex       – długość prefiksu;
 * @param[in, out] forwardingSize    – długość przekierowania.
 * @return Wskaźnik na węzeł zawierający koniec numeru będzącego najdłuższym przekierowaniem dla
 * numeru wejściowego. Zwraca NULL, gdy @p maxPref jest NULL.
 */
Trie setForwardingEndAndSizes(Trie maxPref, size_t* numberSplitIndex); // zmianaaaaa

/** @brief Przepisuje przekierowanie do @p forwardedNumber.
 * @param[in] forwardElement       – wskaźnik na węzeł drzwa zawierający ostatni element
 *                                   przekierowania numeru;
 * @param[in, out] forwardedNumber – wskaźnik na napis reprezentujący przkierowany numer;
 * @param[in] forwardingSize       – długość numeru po przekierowaniu.
 */
void setForwardingInNumber(Trie forwardElement, char* forwardedNumber, size_t forwardingSize);

/** @brief Wyznacza przekierowany numer.
 * @param[in] tr             – wskaźnik na korzeń drzewa przechowywującego numery i przekierowania;
 * @param[in] initialNum     – wskaźnik na napis reprezentujący wejściowy numer;
 * @param[in] initialNumSize – długość wejściowego numeru.
 * @return wskaźnik na napis reprezentujący przekierowany numer lub NULL, gdy nie
 *         udało się alokować pamięci lub @p initialNum nie reprezentuje numeru.
 */
char* getForwardedNumber(Trie tr, char const *initialNum, size_t* numberSplitIndex);

/** @brief Usuwa przekierowania ze struktury opisującej numery i ich przekierowania.
 * Usuwa wszystkie przekierowania znajdujące się w poddrzewach ścieżki do przekierowywań,
 * jeśli nie są one elementem numerów.
 * @param[in] tr  – wskaźnik na węzeł drzwa zawierający numery i ich przekierowania.
 */
void removeForwards(Trie tr);

#endif //PHONE_NUMBERS_FORWARD_H
