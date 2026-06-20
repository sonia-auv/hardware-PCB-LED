/*
 * pilote_thread.c
 *
 *  Created on: Jun 14, 2026
 *      Author: ilyes
 */
#include "main.h"
#include "pilote_thread.h"
#include "cmsis_os.h"

static osPriority_t piloteThread_convertitPriorite(
    PILOTETHREAD_PRIORITE priorite
)
{
    switch(priorite)
    {
        case PILOTETHREAD_PRIORITE_BASSE:
            return osPriorityLow;

        case PILOTETHREAD_PRIORITE_HAUTE:
            return osPriorityHigh;

        case PILOTETHREAD_PRIORITE_NORMALE:
        default:
            return osPriorityNormal;
    }
} 

PILOTETHREAD_ID piloteThread_initialise(
    PILOTETHREAD_FONCTION fonction,
    void *parametre,
    const char *nom,
    uint32_t stackSize,
    PILOTETHREAD_PRIORITE priorite
)
{
    osThreadId_t threadId;

    const osThreadAttr_t attributs =
    {
        .name = nom,
        .stack_size = stackSize,
        .priority = piloteThread_convertitPriorite(priorite),
    };

    threadId = osThreadNew(
        fonction,
        parametre,
        &attributs
    );

    if(threadId == NULL)
    {
        Error_Handler();
    }

    return (PILOTETHREAD_ID)threadId;
}