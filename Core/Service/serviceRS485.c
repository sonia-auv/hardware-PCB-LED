/*
 * serviceRS485.c
 *
 *  Created on: 15 juin 2026
 *      Author: ilyes
 */

#include "serviceRS485.h"
#include "../Interface/interfaceRS485.h"
#include "../Pilote/piloteEvenement.h"
#include "../Pilote/piloteMutex.h"
#include "../Pilote/pilote_thread.h"
#include "main.h"

#define SERVICERS485_AUCUNE_REQUETE_TX  0
#define SERVICERS485_REQUETE_TX_ACTIVE  1

static INTERFACERS485_TRAME serviceRS485_fifoRx[SERVICERS485_TAILLE_FIFO_RX];

static uint8_t serviceRS485_indexLecture = 0;
static uint8_t serviceRS485_indexEcriture = 0;
static uint8_t serviceRS485_nombreTrames = 0;

static uint8_t serviceRS485_etat = SERVICERS485_DISPONIBLE;

static uint8_t serviceRS485_requeteTx = SERVICERS485_AUCUNE_REQUETE_TX;
static INTERFACERS485_TRAME serviceRS485_trameTx;

static void serviceRS485_thread(void *parametre);
static uint8_t serviceRS485_ajouteTrameRx(INTERFACERS485_TRAME *trame);

/**
 * @brief Initialise le service RS485.
 *
 * Initialise l'interface RS485, les pilotes nécessaires au service,
 * les variables internes et démarre le thread du service RS485.
 */
void serviceRS485_initialise(void)
{
    serviceRS485_indexLecture = 0;
    serviceRS485_indexEcriture = 0;
    serviceRS485_nombreTrames = 0;

    serviceRS485_etat = SERVICERS485_DISPONIBLE;
    serviceRS485_requeteTx = SERVICERS485_AUCUNE_REQUETE_TX;

    interfaceRS485_initialise();
    piloteEvenement_initialise();
    piloteMutex_initialise();

    piloteThread_initialise(serviceRS485_thread, 0);
}

/**
 * @brief Demande la transmission d'une trame RS485.
 *
 * @param slave Adresse du destinataire.
 * @param cmd Commande à transmettre.
 * @param nbByte Nombre d'octets contenus dans data.
 * @param data Pointeur vers les données à transmettre.
 *
 * @return SERVICERS485_REUSSI si la demande est acceptée.
 * @return SERVICERS485_ERREUR si une transmission est déjà en attente.
 */
uint8_t serviceRS485_demandeTransmission(
    uint8_t slave,
    uint8_t cmd,
    uint8_t nbByte,
    uint8_t *data
)
{
    if(nbByte > INTERFACERS485_TAILLE_MAX_DATA)
    {
        return SERVICERS485_ERREUR;
    }

    piloteMutex_prendre();

    if(serviceRS485_requeteTx == SERVICERS485_REQUETE_TX_ACTIVE)
    {
        piloteMutex_relacher();
        return SERVICERS485_ERREUR;
    }

    serviceRS485_trameTx.slave = slave;
    serviceRS485_trameTx.cmd = cmd;
    serviceRS485_trameTx.nbByte = nbByte;

    for(uint8_t i = 0; i < nbByte; i++)
    {
        serviceRS485_trameTx.data[i] = data[i];
    }

    serviceRS485_requeteTx = SERVICERS485_REQUETE_TX_ACTIVE;

    piloteMutex_relacher();

    return SERVICERS485_REUSSI;
}

/**
 * @brief Indique si une trame reçue est disponible.
 *
 * @return 1 si une trame est disponible.
 * @return 0 si aucune trame n'est disponible.
 */
uint8_t serviceRS485_trameDisponible(void)
{
    return serviceRS485_nombreTrames > 0;
}

/**
 * @brief Lit la prochaine trame reçue dans la FIFO RX.
 *
 * @param trame Pointeur vers la structure qui recevra la trame.
 *
 * @return SERVICERS485_REUSSI si une trame a été lue.
 * @return SERVICERS485_ERREUR si la FIFO est vide.
 */
uint8_t serviceRS485_litTrame(INTERFACERS485_TRAME *trame)
{
    piloteMutex_prendre();

    if(serviceRS485_nombreTrames == 0)
    {
        piloteMutex_relacher();
        return SERVICERS485_ERREUR;
    }

    *trame = serviceRS485_fifoRx[serviceRS485_indexLecture];

    serviceRS485_indexLecture++;

    if(serviceRS485_indexLecture >= SERVICERS485_TAILLE_FIFO_RX)
    {
        serviceRS485_indexLecture = 0;
    }

    serviceRS485_nombreTrames--;

    piloteMutex_relacher();

    return SERVICERS485_REUSSI;
}
