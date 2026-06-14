/*
 * piloteRS485.h
 *
 *  Created on: Jun 14, 2026
 *      Author: ilyes
 */

#ifndef PILOTERS485_H
#define PILOTERS485_H

#include <stdint.h>

void piloteRS485_initialise(void);

uint8_t piloteRS485_recoitOctet(void);

uint8_t piloteRS485_octetDisponible(void);

void piloteRS485_transmetBloc(uint8_t *bloc, uint8_t longueur);

#endif /* PILOTERS485_H_ */
