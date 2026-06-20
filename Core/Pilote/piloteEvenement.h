/*
 * piloteEvenement.h
 *
 * Pilote generique d'evenements.
 * L'implementation STM32/CMSIS est dans piloteEvenement.c.
 */

#ifndef PILOTE_PILOTEEVENEMENT_H_
#define PILOTE_PILOTEEVENEMENT_H_

#include <stdint.h>

typedef void *PILOTEEVENEMENT_ID;

typedef enum
{
    PILOTEEVENEMENT_ATTEND_UN = 0,
    PILOTEEVENEMENT_ATTEND_TOUS
} PILOTEEVENEMENT_MODE_ATTENTE;

typedef enum
{
    PILOTEEVENEMENT_EFFACE = 0,
    PILOTEEVENEMENT_NE_PAS_EFFACER
} PILOTEEVENEMENT_MODE_EFFACEMENT;

#define PILOTEEVENEMENT_ATTENTE_INFINIE  0xFFFFFFFFu

/**
 * @brief Cree un groupe d'evenements.
 *
 * @return Identifiant du groupe d'evenements cree.
 */
PILOTEEVENEMENT_ID piloteEvenement_cree(void);

/**
 * @brief Detruit un groupe d'evenements.
 *
 * @param evenement Identifiant du groupe d'evenements.
 */
void piloteEvenement_detruit(PILOTEEVENEMENT_ID evenement);

/**
 * @brief Active des flags d'evenement.
 *
 * @param evenement Identifiant du groupe d'evenements.
 * @param flags Flags a activer.
 */
void piloteEvenement_metFlags(
    PILOTEEVENEMENT_ID evenement,
    uint32_t flags
);

/**
 * @brief Efface des flags d'evenement.
 *
 * @param evenement Identifiant du groupe d'evenements.
 * @param flags Flags a effacer.
 */
void piloteEvenement_effaceFlags(
    PILOTEEVENEMENT_ID evenement,
    uint32_t flags
);
 
/**
 * @brief Attend des flags d'evenement.
 *
 * @param evenement Identifiant du groupe d'evenements.
 * @param flags Flags attendus.
 * @param modeAttente Attend un flag ou tous les flags.
 * @param modeEffacement Efface ou garde les flags apres l'attente.
 * @param timeoutMs Temps d'attente en ms. Utiliser PILOTEEVENEMENT_ATTENTE_INFINIE pour attendre sans limite.
 *
 * @return Flags obtenus ou code d'erreur CMSIS.
 */
uint32_t piloteEvenement_attendFlags(
    PILOTEEVENEMENT_ID evenement,
    uint32_t flags,
    PILOTEEVENEMENT_MODE_ATTENTE modeAttente,
    PILOTEEVENEMENT_MODE_EFFACEMENT modeEffacement,
    uint32_t timeoutMs
);

/**
 * @brief Lit les flags actuellement actifs.
 *
 * @param evenement Identifiant du groupe d'evenements.
 *
 * @return Flags actuellement actifs ou code d'erreur CMSIS.
 */
uint32_t piloteEvenement_litFlags(PILOTEEVENEMENT_ID evenement);

#endif /* PILOTE_PILOTEEVENEMENT_H_ */
