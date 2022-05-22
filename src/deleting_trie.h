/** @file
 * Interfejs klasy służącej do usuwania elementów z drzewa
 *
 * @author Mikołaj Szymański
 * @copyright Uniwersytet Warszawski
 * @date 2022
 */

#ifndef PHONE_NUMBERS_DELETING_TRIE_H
#define PHONE_NUMBERS_DELETING_TRIE_H

#include "trie.h"

/** @brief Sprawdza czy drzewo posiada poddrzewa.
 * @param[in] tr – wskaźnik na węzeł drzewa zwierający numery i przekierowania;
 * @return Wartość @p true, jeśli drzewo posiada poddrzewa.
 *         Wartość @p false, jeśli drzewo nie posiada poddrzewa.
 */
bool IsTrieDeeper(Trie tr);

/** @brief Wyznacza nieużywane drzewo.
 * Wyznacza drzewo, będące poddrzewem struktury przechowującej przekierowania
 * numerów i numery, którego wartości w skutek zmiany przekierowań stały stały
 * się bezużyteczne.
 * @param[in,out] tr – wskaźnik na węzeł drzewa.
 * @return Wskaźnik na drzewo, które ma zostać usunięte ze struktury.
 */
Trie findUnusedTrie(Trie tr);

/** @brief Zwalnia pamięć.
 * Zwalnia pamięć zajmowaną przez @p tr.
 * @param[in,out] tr – wskaźnik na węzeł drzewa.
 */
void deleteTrie(Trie tr);

/** @brief Nadzoruje usuwaniem drzewa.
 * @param[in,out] oldForwardingEnd – wskaźnik na węzeł drzewa.
 */
void deleteForwardTrie(Trie oldForwardingEnd);

#endif //PHONE_NUMBERS_DELETING_TRIE_H
