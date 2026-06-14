/*
 * pilote_threadex.c
 *
 *  Created on: Jun 14, 2026
 *      Author: ilyes
 */


#include "piloteThread.h"
#include "cmsis_os.h"
#include "main.h"

#define PILOTETHREAD_STACK_SIZE  512
#define PILOTETHREAD_PRIORITE    osPriorityNormal

static osThreadId_t piloteThread_id;

void piloteThread_initialise(
    PILOTETHREAD_FONCTION fonction,
    void *parametre
)
{
    const osThreadAttr_t piloteThread_attributs =
    {
        .name = "rs485Thread",
        .stack_size = PILOTETHREAD_STACK_SIZE,
        .priority = PILOTETHREAD_PRIORITE,
    };

    piloteThread_id = osThreadNew(
        fonction,
        parametre,
        &piloteThread_attributs
    );

    if(piloteThread_id == NULL)
    {
        Error_Handler();
    }
}
