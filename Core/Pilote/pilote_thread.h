/*
 * pilote_thread.h
 *
 *  Created on: Jun 14, 2026
 *      Author: ilyes
 */
#ifndef PILOTE_PILOTE_THREAD_H_
#define PILOTE_PILOTE_THREAD_H_

#include <stdint.h>

typedef void (*PILOTETHREAD_FONCTION)(void *parametre);

typedef void *PILOTETHREAD_ID;

typedef enum
{
    PILOTETHREAD_PRIORITE_BASSE,
    PILOTETHREAD_PRIORITE_NORMALE,
    PILOTETHREAD_PRIORITE_HAUTE
} PILOTETHREAD_PRIORITE;

PILOTETHREAD_ID piloteThread_initialise(
    PILOTETHREAD_FONCTION fonction,
    void *parametre,
    const char *nom,
    uint32_t stackSize,
    PILOTETHREAD_PRIORITE priorite
);

#endif 