/*
 * serviceRS485.h
 *
 *  Created on: Jun 15, 2026
 *      Author: ilyes
 */

#ifndef SERVICE_SERVICERS485_H_
#define SERVICE_SERVICERS485_H_

#include <stdint.h>
#include "main.h"

#ifndef SERVICERS485_REUSSI
#define SERVICERS485_REUSSI 0
#endif

#ifndef SERVICERS485_ERREUR
#define SERVICERS485_ERREUR 1
#endif

typedef struct
{
    uint8_t slave;
    uint8_t cmd;
    uint8_t nbByte;
    uint8_t data[SERVICERS485_TAILLE_MAX_DATA];
    uint16_t checksum;
} SERVICERS485_TRAME;

/**
 * @brief Initialise le service RS485.
 *
 * Initialise le pilote RS485, les outils de synchronisation,
 * la FIFO RX et démarre le thread de réception.
 */
void serviceRS485_initialise(void);

/**
 * @brief Demande au service RS485 de transmettre une trame.
 *
 * La trame est construite par le service puis transmise par le pilote RS485.
 * Cette version est bloquante pendant la transmission.
 *
 * @param slave Adresse du destinataire.
 * @param cmd Commande à transmettre.
 * @param nbByte Nombre d'octets contenus dans data.
 * @param data Données à transmettre.
 */
void serviceRS485_write(
    uint8_t slave,
    uint8_t cmd,
    uint8_t nbByte,
    const uint8_t *data
);

/**
 * @brief Cherche une commande reçue dans la FIFO RX.
 *
 * Retire seulement une trame dont la commande est présente dans cmdArray.
 * Les autres trames restent disponibles pour les autres processus.
 *
 * @param cmdArray Tableau des commandes attendues.
 * @param nbCommand Nombre de commandes dans cmdArray.
 * @param dataBuffer Buffer recevant les données.
 *
 * @return Nombre d'octets copiés dans dataBuffer.
 * @note Retourne 0 si aucune commande attendue n'est disponible.
 */
uint8_t serviceRS485_read(
    const uint8_t *cmdArray,
    uint8_t nbCommand,
    uint8_t *dataBuffer
);

/**
 * @brief Cherche une commande reçue dans la FIFO RX avec l'adresse de l'émetteur.
 *
 * Retire seulement une trame dont la commande est présente dans cmdArray.
 * Les autres trames restent disponibles pour les autres processus.
 *
 * @param cmdArray Tableau des commandes attendues.
 * @param nbCommand Nombre de commandes dans cmdArray.
 * @param returnedSlave Adresse de l'émetteur.
 * @param dataBuffer Buffer recevant les données.
 *
 * @return Nombre d'octets copiés dans dataBuffer.
 * @note Retourne 0 si aucune commande attendue n'est disponible.
 */
uint8_t serviceRS485_readAvecSlave(
    const uint8_t *cmdArray,
    uint8_t nbCommand,
    uint8_t *returnedSlave,
    uint8_t *dataBuffer
);

/**
 * @brief Indique si une trame reçue est disponible dans la FIFO RX.
 *
 * @return 1 si au moins une trame est disponible.
 * @return 0 si aucune trame n'est disponible.
 */
uint8_t serviceRS485_trameDisponible(void);

/**
 * @brief Lit la prochaine trame reçue, peu importe sa commande.
 *
 * Retire la plus ancienne trame de la FIFO RX.
 * Cette fonction est surtout utile pour debug ou pour un processus générique.
 *
 * @param trame Structure qui recevra la trame lue.
 *
 * @return SERVICERS485_REUSSI si une trame a été lue.
 * @return SERVICERS485_ERREUR si aucune trame n'est disponible.
 */
uint8_t serviceRS485_litTrame(SERVICERS485_TRAME *trame);

#endif /* SERVICE_SERVICERS485_H_ */
