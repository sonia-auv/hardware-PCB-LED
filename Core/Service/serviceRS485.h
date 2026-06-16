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
#include "../Interface/interfaceRS485.h"


#ifndef SERVICERS485_TAILLE_FIFO_RX
#define SERVICERS485_TAILLE_FIFO_RX 4
#endif

/**
 * @brief Initialise le service RS485.
 *
 * Initialise les pilotes nécessaires, l'interface RS485 et les
 * structures internes du service.
 */
void serviceRS485_initialise(void);

/**
 * @brief Demande la transmission d'une trame RS485.
 *
 * @param slave Adresse du destinataire.
 * @param cmd Commande à transmettre.
 * @param nbByte Nombre d'octets contenus dans data.
 * @param data Données à transmettre.
 *
 * @return SERVICERS485_REUSSI si la demande est acceptée.
 * @return SERVICERS485_ERREUR si le service est occupé.
 */
uint8_t serviceRS485_demandeTransmission(
    uint8_t slave,
    uint8_t cmd,
    uint8_t nbByte,
    uint8_t *data
);

/**
 * @brief Indique si une trame reçue est disponible.
 *
 * @return 1 si une trame est disponible dans la FIFO RX.
 * @return 0 sinon.
 */
uint8_t serviceRS485_trameDisponible(void);

/**
 * @brief Lit la prochaine trame reçue.
 *
 * Retire la plus vieille trame de la FIFO RX.
 *
 * @param trame Structure qui recevra la trame lue.
 *
 * @return SERVICERS485_REUSSI si une trame a été lue.
 * @return SERVICERS485_ERREUR si la FIFO RX est vide.
 */
uint8_t serviceRS485_litTrame(
    INTERFACERS485_TRAME *trame
);

/**
 * @brief Indique si le service RS485 est disponible pour une demande.
 *
 * @return SERVICERS485_DISPONIBLE si le service est libre.
 * @return SERVICERS485_OCCUPE si le service est occupé.
 */
uint8_t serviceRS485_obtientEtat(void);


/**
 * @brief Exécute une itération du service RS485.
 *
 * Cette fonction vérifie s'il y a une demande de transmission.
 * Sinon, elle peut effectuer une réception et placer la trame reçue
 * dans la FIFO RX.
 *
 * Elle est prévue pour être appelée par le thread du service.
 */
void serviceRS485_execute(void);

#endif /* SERVICE_SERVICERS485_H_ */
