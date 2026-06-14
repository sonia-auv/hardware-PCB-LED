#ifndef INTERFACERS485_H
#define INTERFACERS485_H

#include <stdint.h>

#define INTERFACERS485_DEBUT_TRAME  0x3A
#define INTERFACERS485_FIN_TRAME    0x0D

#define INTERFACERS485_TAILLE_MAX_DATA  250

typedef struct
{
    uint8_t slave;
    uint8_t cmd;
    uint8_t nbByte;
    uint8_t data[INTERFACERS485_TAILLE_MAX_DATA];
    uint16_t checksum;
} INTERFACERS485_TRAME;

void interfaceRS485_initialise(void);

uint16_t interfaceRS485_calculChecksum(
    uint8_t slave,
    uint8_t cmd,
    uint8_t nbByte,
    uint8_t *data
);

void interfaceRS485_transmet(
    uint8_t slave,
    uint8_t cmd,
    uint8_t nbByte,
    uint8_t *data
);

uint8_t interfaceRS485_recoitTrame(
    INTERFACERS485_TRAME *trame
);

#endif
