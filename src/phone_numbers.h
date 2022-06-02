/** @file
 * Interfejs klasy zawierający metody związane ze strukturą przechowującą numery telefonów
 *
 * @author Mikołaj Szymański
 * @copyright Uniwersytet Warszawski
 * @date 2022
 */

#ifndef PHONE_NUMBERS_PHONE_NUMBERS_H
#define PHONE_NUMBERS_PHONE_NUMBERS_H

#include "trie.h"
#include "functions.h"

/**
 * Struktura przechowująca ciąg numerów telefonów.
 */
struct PhoneNumbers {
    Trie trieOfNumbers; ///< korzeń drzewa zawierający przekierowane numery telefonów
    Trie* arrayOfNumbersEnd; ///< tablica węzłów zawierających ostatnie elementy numerów
    char** arrayOfNumbers; ///< tablica zawierająca wskaźniki na ciągi numerów telefonów
    char* initNumber;
    size_t numberOfTries; ///< nowe!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    char type;
};
typedef struct PhoneNumbers PhoneNumbers;

/** @brief Tworzy nową strukturę.
 * Tworzy nową pustą strukturę.
 * @param[in] trieOfNumbers       – wskaźnik na korzeń drzewa zawierający przekierowane numery telefonów;
 * @param[in] arrayOfNumbersEnd   – wskaźnik na tablię węzłów zawierających ostatnie elementy numerów.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *         alokować pamięci.
 */
PhoneNumbers* phnumNew(size_t numberOfTries, Trie trieOfNumbers, Trie* arrayOfNumbersEnd, char* initNumber); // !!! nowe parametry

/** @brief Dodaje do tablicy wskaźnik na przekierowany numer.
 * @param[in] pnum     – wskaźnik na strukturę przechowującą numery telefonów;
 * @param[in] number   – wskaźnik na napis opisujący numer.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *         alokować pamięci.
 */
void addNumbersPtrToArray(PhoneNumbers const *pnum, char* number, size_t index); // zmiana !!!!

/** @brief Przepisuje nieprzekierowaną część @p initialNum do @p forwardedNumber.
 * @param[in, out] forwardedNumber – wskaźnik na napis reprezentujący przkierowany numer;
 * @param[in] initialNum           – wskaźnik na napis reprezentujący wejściowy numer;
 * @param[in] initialNumSize       – długość wejściowego numeru;
 * @param[in] maxPrefSize          – długość prefiksu wejściowego numeru;
 * @param[in] forwardingSize       – długość przekierowania.
 *
 */
void setRestOfNumber(char* forwardedNumber, char const *initialNum, size_t initialNumSize, size_t maxPrefSize, size_t forwardingSize);


char* getNumber(PhoneNumbers const *pnum, Trie tr, size_t index);

#endif //PHONE_NUMBERS_PHONE_NUMBERS_H
