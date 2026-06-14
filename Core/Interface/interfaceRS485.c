/*
 * interfaceRS485.c
 *
 *  Created on: Jun 14, 2026
 *      Author: ilyes
 */

#include "interfaceRS485.h"
#include "../Pilote/piloteRS485.h"
#include "../Pilote/piloteEvenement.h"
#include "../Pilote/piloteMutex.h"
#include "../Pilote/piloteThread.h"

static void interfaceRS485_threadReception(void *parametre);

void interfaceRS485_initialise(void)
{
    piloteRS485_initialise();
    piloteEvenement_initialise();
    piloteMutex_initialise();

    piloteThread_initialise(
        interfaceRS485_threadReception,
        0
    );
}
/**
 * @brief Calcule le checksum d'une trame RS485
 *
 * @param slave slave ID
 * @param cmd  command
 * @param nbByte number of bytes in data
 * @param data data bytes
 * @return uint16_t
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
 * @brief Transmet une trame RS485
 * 
 * @param slave 
 * @param cmd 
 * @param nbByte 
 * @param data 
 */
void interfaceRS485_transmet(
    uint8_t slave,
    uint8_t cmd,
    uint8_t nbByte,
    uint8_t *data
)
{
    uint8_t trame[256];
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
