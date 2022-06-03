/** @file
 * Interfejs klasy zawierający funkcje pomocnicze
 *
 * @author Mikołaj Szymański
 * @copyright Uniwersytet Warszawski
 * @date 2022
 */

#ifndef PHONE_NUMBERS_FUNCTIONS_H
#define PHONE_NUMBERS_FUNCTIONS_H

#include "trie.h"

/**
 * Określa ilość znaków mogących być elementem numeru.
 */
#define NUM 12

/** @brief Zmienia znak na cyfrę.
 * @param[in,out] num     – wskaźnik na indeks;
 * @param[in] character   – wskaźnik na znak;
 * @return Wartość @p true, jeśli można zmienić znak na cyfrę.
 *         Wartość @p false, jeśli nie można zmienić znaku na cyfrę.
 */
bool getInteger(int* num, char character);

/** @brief Sprwadza czy numer składa się tylko z dopuszczalnych znaków.
 * @param[in,out] num     – wskaźnik na numer;
 * @return Wartość @p true, jeśli numer zawiera dopuszczalne znaki.
 *         Wartość @p false, eśli numer zawiera niedopuszczalne znaki.
 */
bool checkNum(char const *num);

/** @brief Kopiuje numer.
 * @param[in] numCopy – wskaźnik na kopię numeru;
 * @param[in] num     – wskaźnik na numer.
 */
void copyNumber(char* numCopy, char const *num);

#endif //PHONE_NUMBERS_FUNCTIONS_H
