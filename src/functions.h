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

/** @brief Zmienia znak na cyfrę.
 * @param[in,out] num     – wskaźnik na indeks;
 * @param[in] character   – wskaźnik na znak;
 * @return Wartość @p true, jeśli można zmienić znak na cyfrę.
 *         Wartość @p false, jeśli nie można zmienić znaku na cyfrę.
 */
bool getInteger(int* num, char character);

#endif //PHONE_NUMBERS_FUNCTIONS_H
