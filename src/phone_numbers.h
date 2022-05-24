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
PhoneNumbers* phnumNew(size_t numberOfTries, Trie trieOfNumbers, Trie* arrayOfNumbersEnd, char type); // !!! nowe parametry

/** @brief Dodaje do tablicy wskaźnik na przekierowany numer.
 * @param[in] pnum     – wskaźnik na strukturę przechowującą numery telefonów;
 * @param[in] number   – wskaźnik na napis opisujący numer.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *         alokować pamięci.
 */
void addNumbersPtrToArray(PhoneNumbers const *pnum, char* number);

char* getNumber(PhoneNumbers const *pnum, Trie tr);

#endif //PHONE_NUMBERS_PHONE_NUMBERS_H
