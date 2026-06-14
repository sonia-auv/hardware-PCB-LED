/*
 * piloteEvenement.c
 *
 *  Created on: Jun 14, 2026
 *      Author: ilyes
 */
#include "main.h"
#include "piloteEvenement.h"
#include "cmsis_os.h"

static osEventFlagsId_t piloteEvenement_id;

void piloteEvenement_initialise(void)
{
    piloteEvenement_id = osEventFlagsNew(NULL);
    if(piloteEvenement_id == NULL)
    {
        Error_Handler();
    }
}

void piloteEvenement_metFlags(uint32_t flags)
{
    osEventFlagsSet(piloteEvenement_id, flags);
}

void piloteEvenement_effaceFlags(uint32_t flags)
{
    osEventFlagsClear(piloteEvenement_id, flags);
}

uint32_t piloteEvenement_attendFlags(uint32_t flags)
{
    return osEventFlagsWait(
        piloteEvenement_id,
        flags,
        osFlagsWaitAny,
        osWaitForever
    );
}
