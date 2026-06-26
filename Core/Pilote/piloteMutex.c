/*
 * piloteMutex.c
 *
 * Implementation STM32IDE / CMSIS-RTOS2 du pilote de mutex.
 */

#include "main.h"
#include "piloteMutex.h"
#include "cmsis_os.h"

PILOTEMUTEX_ID piloteMutex_cree(void)
{
    osMutexId_t mutex;

    mutex = osMutexNew(0);

    if(mutex == 0)
    {
        Error_Handler();
        return 0;
    }

    return (PILOTEMUTEX_ID)mutex;
}

void piloteMutex_detruit(PILOTEMUTEX_ID mutex)
{
    if(mutex == 0)
    {
        return;
    }

    osMutexDelete((osMutexId_t)mutex);
}

void piloteMutex_prendre(PILOTEMUTEX_ID mutex)
{
    if(mutex == 0)
    {
        return;
    }

    if(osMutexAcquire((osMutexId_t)mutex, osWaitForever) != osOK)
    {
        Error_Handler();
    }
}

void piloteMutex_relacher(PILOTEMUTEX_ID mutex)
{
    if(mutex == 0)
    {
        return;
    }

    if(osMutexRelease((osMutexId_t)mutex) != osOK)
    {
        Error_Handler();
    }
}