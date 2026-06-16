/*
 * interfaceRS485.c
 *
 *  Created on: Jun 14, 2026
 *      Author: ilyes
 */

#include "interfaceRS485.h"
#include "../Pilote/piloteRS485.h"

/**
 * @brief Initialise l'interface RS485.
 *
 * Initialise le pilote RS485 ainsi que les variables internes
 * utilisées par l'interface.
 */
void interfaceRS485_initialise(void)
{
    piloteRS485_initialise();
}

/**
 * @brief Calcule le checksum d'une trame RS485.
 *
 * Le checksum est calculé avec le début de trame, l'adresse slave,
 * la commande, le nombre d'octets, les données et la fin de trame.
 *
 * @param slave Adresse du destinataire.
 * @param cmd Commande de la trame.
 * @param nbByte Nombre d'octets contenus dans data.
 * @param data Pointeur vers les données de la trame.
 *
 * @return Checksum calculé sur 16 bits.
 */
uint16_t interfaceRS485_calculChecksum(
    uint8_t slave,
    uint8_t cmd,
    uint8_t nbByte,
    uint8_t *data
)
{
    uint16_t checksum = INTERFACERS485_DEBUT_TRAME
                      + slave
                      + cmd
                      + nbByte
                      + INTERFACERS485_FIN_TRAME;

    for(uint8_t i = 0; i < nbByte; i++)
    {
        checksum += data[i];
    }

    return checksum;
}

/**
 * @brief Transmet une trame RS485.
 *
 * Construit une trame RS485 complète, ajoute le checksum, puis
 * demande au pilote RS485 de transmettre le bloc complet.
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
)
{
    uint8_t trame[INTERFACERS485_TAILLE_MAX_DATA + 7];
    uint16_t checksum = 0;
    uint8_t index = 0;

    checksum = interfaceRS485_calculChecksum(slave, cmd, nbByte, data);

    trame[index++] = INTERFACERS485_DEBUT_TRAME;
    trame[index++] = slave;
    trame[index++] = cmd;
    trame[index++] = nbByte;

    for(uint8_t i = 0; i < nbByte; i++)
    {
        trame[index++] = data[i];
    }

    trame[index++] = (uint8_t)(checksum >> 8);
    trame[index++] = (uint8_t)(checksum & 0xFF);
    trame[index++] = INTERFACERS485_FIN_TRAME;

    piloteRS485_transmetBloc(trame, index);
}

/**
 * @brief Reçoit une trame RS485.
 *
 * Attend le début de trame, lit les champs de la trame, valide le
 * checksum et remplit la structure passée en paramètre.
 *
 * Cette fonction est bloquante. Elle doit être appelée par le service
 * RS485 lorsque celui-ci décide de faire une réception.
 *
 * @param trame Structure qui recevra les informations de la trame.
 *
 * @return INTERFACERS485_TRAME_VALIDE si la trame est valide.
 * @return INTERFACERS485_TRAME_INVALIDE si la trame reçue est invalide.
 */
uint8_t interfaceRS485_recoitTrame(
    INTERFACERS485_TRAME *trame
)
{
    uint8_t octet = 0;
    uint8_t finTrame = 0;
    uint16_t checksumRecu = 0;
    uint16_t checksumCalcule = 0;

    while(octet != INTERFACERS485_DEBUT_TRAME)
    {
        octet = piloteRS485_recoitOctet();
    }

    trame->slave = piloteRS485_recoitOctet();
    trame->cmd = piloteRS485_recoitOctet();
    trame->nbByte = piloteRS485_recoitOctet();

    if(trame->nbByte > INTERFACERS485_TAILLE_MAX_DATA)
    {
        return INTERFACERS485_TRAME_INVALIDE;
    }

    for(uint8_t i = 0; i < trame->nbByte; i++)
    {
        trame->data[i] = piloteRS485_recoitOctet();
    }

    checksumRecu = ((uint16_t)piloteRS485_recoitOctet()) << 8;
    checksumRecu |= piloteRS485_recoitOctet();

    finTrame = piloteRS485_recoitOctet();

    if(finTrame != INTERFACERS485_FIN_TRAME)
    {
        return INTERFACERS485_TRAME_INVALIDE;
    }

    checksumCalcule = interfaceRS485_calculChecksum(
        trame->slave,
        trame->cmd,
        trame->nbByte,
        trame->data
    );

    if(checksumRecu != checksumCalcule)
    {
        return INTERFACERS485_TRAME_INVALIDE;
    }

    trame->checksum = checksumRecu;

    return INTERFACERS485_TRAME_VALIDE;
}
