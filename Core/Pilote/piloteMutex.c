/*
 * piloteMutex.c
 *
 *  Created on: Jun 14, 2026
 *      Author: ilyes
 */

#include "piloteMutex.h"
#include "cmsis_os.h"
#include "main.h"

static osMutexId_t piloteMutex_id;

void piloteMutex_initialise(void)
{
    piloteMutex_id = osMutexNew(NULL);

    if(piloteMutex_id == NULL)
    {
        Error_Handler();
    }
}

void piloteMutex_prendre(void)
{
    osMutexAcquire(piloteMutex_id, osWaitForever);
}

void piloteMutex_relacher(void)
{
    osMutexRelease(piloteMutex_id);
}
