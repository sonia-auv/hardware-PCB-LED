/*
 * piloteMutex.h
 *
 * Pilote generique de mutex.
 * L'implementation STM32/CMSIS est dans piloteMutex.c.
 */

#ifndef PILOTE_PILOTEMUTEX_H_
#define PILOTE_PILOTEMUTEX_H_

typedef void *PILOTEMUTEX_ID;

/**
 * @brief Cree un mutex.
 *
 * @return Identifiant du mutex cree.
 */
PILOTEMUTEX_ID piloteMutex_cree(void);

/**
 * @brief Detruit un mutex.
 *
 * @param mutex Identifiant du mutex.
 */
void piloteMutex_detruit(PILOTEMUTEX_ID mutex);

/**
 * @brief Prend un mutex.
 *
 * @param mutex Identifiant du mutex.
 */
void piloteMutex_prendre(PILOTEMUTEX_ID mutex);

/**
 * @brief Relache un mutex.
 *
 * @param mutex Identifiant du mutex.
 */
void piloteMutex_relacher(PILOTEMUTEX_ID mutex);

#endif /* PILOTE_PILOTEMUTEX_H_ */