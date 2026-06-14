/*
 * pilote_thread.h
 *
 *  Created on: Jun 14, 2026
 *      Author: ilyes
 */

#ifndef PILOTE_PILOTE_THREAD_H_
#define PILOTE_PILOTE_THREAD_H_


typedef void (*PILOTETHREAD_FONCTION)(void *parametre);

void piloteThread_initialise(
    PILOTETHREAD_FONCTION fonction,
    void *parametre
);

#endif /* PILOTE_PILOTE_THREAD_H_ */
