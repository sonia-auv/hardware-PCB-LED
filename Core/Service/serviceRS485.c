/*
 * serviceRS485.c
 *
 *  Created on: 15 juin 2026
 *      Author: ilyes
 */

#include "main.h"
#include "serviceRS485.h"
#include "../Pilote/piloteRS485.h"
#include "../Pilote/piloteMutex.h"
#include "../Pilote/pilote_thread.h"

static SERVICERS485_TRAME serviceRS485_fifoRx[SERVICERS485_TAILLE_FIFO_RX];

static uint8_t serviceRS485_indexLecture = 0;
static uint8_t serviceRS485_indexEcriture = 0;
static uint8_t serviceRS485_nombreTrames = 0;

static void serviceRS485_threadReception(void *parametre);

static uint16_t serviceRS485_calculChecksum(
    uint8_t slave,
    uint8_t cmd,
    uint8_t nbByte,
    const uint8_t *data
);

static uint8_t serviceRS485_recoitTrame(
    SERVICERS485_TRAME *trame
);

static uint8_t serviceRS485_ajouteTrameRx(
    const SERVICERS485_TRAME *trame
);

static uint8_t serviceRS485_commandeEstAttendue(
    uint8_t cmd,
    const uint8_t *cmdArray,
    uint8_t nbCommand
);

static uint8_t serviceRS485_indexPhysique(
    uint8_t indexLogique
);

static void serviceRS485_retireTrameRx(
    uint8_t indexLogique
);

/**
 * @brief Initialise le service RS485.
 *
 * Initialise le pilote RS485, le mutex du service, la FIFO RX
 * et démarre le thread de réception RS485.
 */
void serviceRS485_initialise(void)
{
    serviceRS485_indexLecture = 0;
    serviceRS485_indexEcriture = 0;
    serviceRS485_nombreTrames = 0;

    piloteRS485_initialise();
    piloteMutex_initialise();

    piloteThread_initialise(serviceRS485_threadReception, 0);
}

/**
 * @brief Demande au service RS485 de transmettre une trame.
 *
 * Construit une trame RS485 complète, calcule le checksum,
 * puis transmet le bloc complet avec le pilote RS485.
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
)
{
    uint8_t trame[SERVICERS485_TAILLE_MAX_DATA + 7];
    uint16_t checksum;
    uint8_t index = 0;

    if(nbByte > SERVICERS485_TAILLE_MAX_DATA)
    {
        return;
    }

    if((nbByte > 0) && (data == 0))
    {
        return;
    }

    checksum = serviceRS485_calculChecksum(slave, cmd, nbByte, data);

    trame[index++] = SERVICERS485_DEBUT_TRAME;
    trame[index++] = slave;
    trame[index++] = cmd;
    trame[index++] = nbByte;

    for(uint8_t i = 0; i < nbByte; i++)
    {
        trame[index++] = data[i];
    }

    trame[index++] = (uint8_t)(checksum >> 8);
    trame[index++] = (uint8_t)(checksum & 0xFF);
    trame[index++] = SERVICERS485_FIN_TRAME;

    piloteMutex_prendre();
    piloteRS485_transmetBloc(trame, index);
    piloteMutex_relacher();
}

/**
 * @brief Cherche une commande reçue dans la FIFO RX.
 *
 * @param cmdArray Tableau des commandes attendues.
 * @param nbCommand Nombre de commandes dans cmdArray.
 * @param dataBuffer Buffer recevant les données.
 *
 * @return Nombre d'octets copiés dans dataBuffer.
 */
uint8_t serviceRS485_read(
    const uint8_t *cmdArray,
    uint8_t nbCommand,
    uint8_t *dataBuffer
)
{
    return serviceRS485_readAvecSlave(
        cmdArray,
        nbCommand,
        0,
        dataBuffer
    );
}

/**
 * @brief Cherche une commande reçue dans la FIFO RX avec l'adresse de l'émetteur.
 *
 * Cette fonction ne retire pas les trames qui ne correspondent pas aux
 * commandes demandées. Elles restent donc disponibles pour les autres processus.
 *
 * @param cmdArray Tableau des commandes attendues.
 * @param nbCommand Nombre de commandes dans cmdArray.
 * @param returnedSlave Adresse de l'émetteur.
 * @param dataBuffer Buffer recevant les données.
 *
 * @return Nombre d'octets copiés dans dataBuffer.
 */
uint8_t serviceRS485_readAvecSlave(
    const uint8_t *cmdArray,
    uint8_t nbCommand,
    uint8_t *returnedSlave,
    uint8_t *dataBuffer
)
{
    uint8_t nbByte = 0;

    if((cmdArray == 0) || (nbCommand == 0) || (dataBuffer == 0))
    {
        return 0;
    }

    piloteMutex_prendre();

    for(uint8_t i = 0; i < serviceRS485_nombreTrames; i++)
    {
        uint8_t index = serviceRS485_indexPhysique(i);

        if(serviceRS485_commandeEstAttendue(
            serviceRS485_fifoRx[index].cmd,
            cmdArray,
            nbCommand
        ) != 0)
        {
            nbByte = serviceRS485_fifoRx[index].nbByte;

            if(returnedSlave != 0)
            {
                *returnedSlave = serviceRS485_fifoRx[index].slave;
            }

            for(uint8_t j = 0; j < nbByte; j++)
            {
                dataBuffer[j] = serviceRS485_fifoRx[index].data[j];
            }

            serviceRS485_retireTrameRx(i);
            piloteMutex_relacher();
            return nbByte;
        }
    }

    piloteMutex_relacher();

    return 0;
}

/**
 * @brief Indique si une trame reçue est disponible.
 *
 * @return 1 si une trame est disponible.
 * @return 0 si aucune trame n'est disponible.
 */
uint8_t serviceRS485_trameDisponible(void)
{
    uint8_t disponible;

    piloteMutex_prendre();
    disponible = (serviceRS485_nombreTrames > 0);
    piloteMutex_relacher();

    return disponible;
}

/**
 * @brief Lit la prochaine trame reçue.
 *
 * Retire la plus ancienne trame de la FIFO RX.
 *
 * @param trame Structure qui recevra la trame lue.
 *
 * @return SERVICERS485_REUSSI si une trame a été lue.
 * @return SERVICERS485_ERREUR si aucune trame n'est disponible.
 */
uint8_t serviceRS485_litTrame(SERVICERS485_TRAME *trame)
{
    if(trame == 0)
    {
        return SERVICERS485_ERREUR;
    }

    piloteMutex_prendre();

    if(serviceRS485_nombreTrames == 0)
    {
        piloteMutex_relacher();
        return SERVICERS485_ERREUR;
    }

    *trame = serviceRS485_fifoRx[serviceRS485_indexLecture];

    serviceRS485_retireTrameRx(0);

    piloteMutex_relacher();

    return SERVICERS485_REUSSI;
}

/**
 * @brief Thread de réception du service RS485.
 *
 * Reçoit les trames RS485 en continu. Lorsqu'une trame valide
 * est reçue, elle est ajoutée dans la FIFO RX du service.
 *
 * @param parametre Paramètre inutilisé.
 */
static void serviceRS485_threadReception(void *parametre)
{
    SERVICERS485_TRAME trameRecue;

    (void)parametre;

    while(1)
    {
        if(serviceRS485_recoitTrame(&trameRecue) == SERVICERS485_REUSSI)
        {
            piloteMutex_prendre();
            serviceRS485_ajouteTrameRx(&trameRecue);
            piloteMutex_relacher();
        }
    }
}

/**
 * @brief Calcule le checksum d'une trame RS485.
 *
 * @param slave Adresse.
 * @param cmd Commande.
 * @param nbByte Nombre d'octets de data.
 * @param data Données.
 *
 * @return Checksum 16 bits.
 */
static uint16_t serviceRS485_calculChecksum(
    uint8_t slave,
    uint8_t cmd,
    uint8_t nbByte,
    const uint8_t *data
)
{
    uint16_t checksum = 0;

    checksum += slave;
    checksum += cmd;
    checksum += nbByte;

    for(uint8_t i = 0; i < nbByte; i++)
    {
        checksum += data[i];
    }

    return checksum;
}

/**
 * @brief Reçoit une trame complète sur le bus RS485.
 *
 * Format de trame utilisé:
 * DEBUT, slave, cmd, nbByte, data..., checksumMSB, checksumLSB, FIN
 *
 * @param trame Structure qui recevra la trame.
 *
 * @return SERVICERS485_REUSSI si une trame valide est reçue.
 * @return SERVICERS485_ERREUR si la trame est invalide.
 */
static uint8_t serviceRS485_recoitTrame(
    SERVICERS485_TRAME *trame
)
{
    uint8_t octet;
    uint8_t checksumHaut;
    uint8_t checksumBas;
    uint8_t finTrame;
    uint16_t checksumRecu;
    uint16_t checksumCalcule;

    if(trame == 0)
    {
        return SERVICERS485_ERREUR;
    }

    do
    {
        octet = piloteRS485_recoitOctet();
    }
    while(octet != SERVICERS485_DEBUT_TRAME);

    trame->slave = piloteRS485_recoitOctet();
    trame->cmd = piloteRS485_recoitOctet();
    trame->nbByte = piloteRS485_recoitOctet();

    if(trame->nbByte > SERVICERS485_TAILLE_MAX_DATA)
    {
        return SERVICERS485_ERREUR;
    }

    for(uint8_t i = 0; i < trame->nbByte; i++)
    {
        trame->data[i] = piloteRS485_recoitOctet();
    }

    checksumHaut = piloteRS485_recoitOctet();
    checksumBas = piloteRS485_recoitOctet();
    finTrame = piloteRS485_recoitOctet();

    if(finTrame != SERVICERS485_FIN_TRAME)
    {
        return SERVICERS485_ERREUR;
    }

    checksumRecu = ((uint16_t)checksumHaut << 8) | checksumBas;
    checksumCalcule = serviceRS485_calculChecksum(
        trame->slave,
        trame->cmd,
        trame->nbByte,
        trame->data
    );

    if(checksumRecu != checksumCalcule)
    {
        return SERVICERS485_ERREUR;
    }

    trame->checksum = checksumRecu;

    return SERVICERS485_REUSSI;
}

/**
 * @brief Ajoute une trame dans la FIFO RX.
 *
 * Si la FIFO est pleine, la plus ancienne trame est supprimée pour garder
 * la nouvelle trame reçue.
 *
 * @param trame Trame à ajouter.
 *
 * @return SERVICERS485_REUSSI.
 */
static uint8_t serviceRS485_ajouteTrameRx(
    const SERVICERS485_TRAME *trame
)
{
    if(trame == 0)
    {
        return SERVICERS485_ERREUR;
    }

    if(serviceRS485_nombreTrames >= SERVICERS485_TAILLE_FIFO_RX)
    {
        serviceRS485_indexLecture++;

        if(serviceRS485_indexLecture >= SERVICERS485_TAILLE_FIFO_RX)
        {
            serviceRS485_indexLecture = 0;
        }

        serviceRS485_nombreTrames--;
    }

    serviceRS485_fifoRx[serviceRS485_indexEcriture] = *trame;

    serviceRS485_indexEcriture++;

    if(serviceRS485_indexEcriture >= SERVICERS485_TAILLE_FIFO_RX)
    {
        serviceRS485_indexEcriture = 0;
    }

    serviceRS485_nombreTrames++;

    return SERVICERS485_REUSSI;
}

/**
 * @brief Vérifie si une commande fait partie des commandes attendues.
 *
 * @param cmd Commande à vérifier.
 * @param cmdArray Tableau des commandes attendues.
 * @param nbCommand Nombre de commandes dans le tableau.
 *
 * @return 1 si la commande est attendue.
 * @return 0 sinon.
 */
static uint8_t serviceRS485_commandeEstAttendue(
    uint8_t cmd,
    const uint8_t *cmdArray,
    uint8_t nbCommand
)
{
    for(uint8_t i = 0; i < nbCommand; i++)
    {
        if(cmd == cmdArray[i])
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Convertit un index logique de FIFO en index physique.
 *
 * @param indexLogique Index logique à partir de indexLecture.
 *
 * @return Index physique dans le tableau FIFO.
 */
static uint8_t serviceRS485_indexPhysique(
    uint8_t indexLogique
)
{
    uint8_t index = serviceRS485_indexLecture + indexLogique;

    while(index >= SERVICERS485_TAILLE_FIFO_RX)
    {
        index -= SERVICERS485_TAILLE_FIFO_RX;
    }

    return index;
}

/**
 * @brief Retire une trame de la FIFO RX.
 *
 * Peut retirer une trame au milieu de la FIFO pour laisser les trames qui
 * concernent les autres processus.
 *
 * @param indexLogique Position logique de la trame à retirer.
 */
static void serviceRS485_retireTrameRx(
    uint8_t indexLogique
)
{
    if(indexLogique >= serviceRS485_nombreTrames)
    {
        return;
    }

    for(uint8_t i = indexLogique; i < (serviceRS485_nombreTrames - 1); i++)
    {
        uint8_t indexDestination = serviceRS485_indexPhysique(i);
        uint8_t indexSource = serviceRS485_indexPhysique(i + 1);

        serviceRS485_fifoRx[indexDestination] = serviceRS485_fifoRx[indexSource];
    }

    serviceRS485_nombreTrames--;
    serviceRS485_indexEcriture = serviceRS485_indexPhysique(serviceRS485_nombreTrames);
}
