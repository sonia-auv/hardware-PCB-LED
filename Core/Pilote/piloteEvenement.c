/*
 * piloteEvenement.c
 *
 * Implementation STM32IDE / CMSIS-RTOS2 du pilote d'evenements.
 */

#include "main.h"
#include "piloteEvenement.h"
#include "cmsis_os.h"

PILOTEEVENEMENT_ID piloteEvenement_cree(void)
{
    osEventFlagsId_t evenement;

    evenement = osEventFlagsNew(0);

    if(evenement == 0)
    {
        Error_Handler();
        return 0;
    }

    return (PILOTEEVENEMENT_ID)evenement;
}

void piloteEvenement_detruit(PILOTEEVENEMENT_ID evenement)
{
    if(evenement == 0)
    {
        return;
    }

    osEventFlagsDelete((osEventFlagsId_t)evenement);
}

void piloteEvenement_metFlags(
    PILOTEEVENEMENT_ID evenement,
    uint32_t flags
)
{
    if(evenement == 0)
    {
        return;
    }

    osEventFlagsSet(
        (osEventFlagsId_t)evenement,
        flags
    );
}

void piloteEvenement_effaceFlags(
    PILOTEEVENEMENT_ID evenement,
    uint32_t flags
)
{
    if(evenement == 0)
    {
        return;
    }

    osEventFlagsClear(
        (osEventFlagsId_t)evenement,
        flags
    );
}

uint32_t piloteEvenement_attendFlags(
    PILOTEEVENEMENT_ID evenement,
    uint32_t flags,
    PILOTEEVENEMENT_MODE_ATTENTE modeAttente,
    PILOTEEVENEMENT_MODE_EFFACEMENT modeEffacement,
    uint32_t timeoutMs
)
{
    uint32_t options = 0;

    if(evenement == 0)
    {
        return 0;
    }

    if(modeAttente == PILOTEEVENEMENT_ATTEND_TOUS)
    {
        options |= osFlagsWaitAll;
    }
    else
    {
        options |= osFlagsWaitAny;
    }

    if(modeEffacement == PILOTEEVENEMENT_NE_PAS_EFFACER)
    {
        options |= osFlagsNoClear;
    }

    return osEventFlagsWait(
        (osEventFlagsId_t)evenement,
        flags,
        options,
        timeoutMs
    );
}

uint32_t piloteEvenement_litFlags(PILOTEEVENEMENT_ID evenement)
{
    if(evenement == 0)
    {
        return 0;
    }

    return osEventFlagsGet((osEventFlagsId_t)evenement);
} 
