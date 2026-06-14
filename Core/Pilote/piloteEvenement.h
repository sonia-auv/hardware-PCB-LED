/*
 * piloteEvenement.h
 *
 *  Created on: Jun 14, 2026
 *      Author: ilyes
 */

#ifndef PILOTE_PILOTEEVENEMENT_H_
#define PILOTE_PILOTEEVENEMENT_H_


#include <stdint.h>

void piloteEvenement_initialise(void);

void piloteEvenement_metFlags(uint32_t flags);

void piloteEvenement_effaceFlags(uint32_t flags);

uint32_t piloteEvenement_attendFlags(uint32_t flags);


#endif /* PILOTE_PILOTEEVENEMENT_H_ */
