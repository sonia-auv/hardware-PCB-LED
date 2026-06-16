#ifndef INTERFACERS485_H
#define INTERFACERS485_H
/**
 * @brief Transmet une trame RS485.
 *
 * Responsabilité :
 * - Construire une trame valide.
 * - Calculer le checksum.
 * - Demander la transmission au pilote RS485.
 *
 * Ne doit pas :
 * - Gérer les threads.
 * - Gérer les événements.
 * - Gérer les décisions applicatives.
 */
#include <stdint.h>
#include "main.h"


/**
 * @brief Structure représentant une trame RS485.
 *
 * Contient tous les éléments d'une trame RS485, y compris le checksum.
 */
typedef struct
{
    uint8_t slave;
    uint8_t cmd;
    uint8_t nbByte;
    uint8_t data[INTERFACERS485_TAILLE_MAX_DATA];
    uint16_t checksum;
} INTERFACERS485_TRAME;

/**
 * @brief Initialise l'interface RS485.
 *
 * Initialise les variables internes utilisées par l'interface RS485.
 * Cette fonction ne doit pas accéder directement au matériel.
 */
void interfaceRS485_initialise(void);

uint16_t interfaceRS485_calculChecksum(
    uint8_t slave,
    uint8_t cmd,
    uint8_t nbByte,
    uint8_t *data
);

/**
 * @brief Transmet une trame RS485.
 *
 * Construit une trame RS485 complète à partir des paramètres fournis
 * puis la transmet à l'aide du pilote RS485.
 *
 * @param slave Adresse du destinataire.
 * @param cmd Commande à transmettre.
 * @param nbByte Nombre d'octets contenus dans data.
 * @param data Pointeur vers les données à transmettre.
 */
void interfaceRS485_transmet(
    uint8_t slave,
    uint8_t cmd,
    uint8_t nbByte,
    uint8_t *data
);

/**
 * @brief Reçoit une trame RS485.
 *
 * Lit une trame complète à partir du pilote RS485, valide son
 * checksum et remplit la structure fournie.
 *
 * @param trame Structure qui recevra les informations de la trame.
 *
 * @return INTERFACERS485_TRAME_VALIDE si la trame est valide.
 * @return INTERFACERS485_TRAME_INVALIDE si la trame est invalide.
 */
uint8_t interfaceRS485_recoitTrame(
    INTERFACERS485_TRAME *trame
);

#endif
