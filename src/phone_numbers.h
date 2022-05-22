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

/**
 * Struktura przechowująca ciąg numerów telefonów.
 */
struct PhoneNumbers {
    Trie trieOfNumbers; ///< korzeń drzewa zawierający przekierowane numery telefonów
    Trie* arrayOfNumbersEnd; ///< tablica węzłów zawierających ostatnie elementy numerów
    char** arrayOfNumbers; ///< tablica zawierająca wskaźniki na ciągi numerów telefonów
};
typedef struct PhoneNumbers PhoneNumbers;

/** @brief Tworzy nową strukturę.
 * Tworzy nową pustą strukturę.
 * @param[in] trieOfNumbers       – wskaźnik na korzeń drzewa zawierający przekierowane numery telefonów;
 * @param[in] arrayOfNumbersEnd   – wskaźnik na tablię węzłów zawierających ostatnie elementy numerów.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *         alokować pamięci.
 */
PhoneNumbers* phnumNew(Trie trieOfNumbers, Trie* arrayOfNumbersEnd);

/** @brief Dodaje do tablicy wskaźnik na przekierowany numer.
 * @param[in] pnum     – wskaźnik na strukturę przechowującą numery telefonów;
 * @param[in] number   – wskaźnik na napis opisujący numer.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *         alokować pamięci.
 */
void addNumbersPtrToArray(PhoneNumbers const *pnum, char* number);

#endif //PHONE_NUMBERS_PHONE_NUMBERS_H
