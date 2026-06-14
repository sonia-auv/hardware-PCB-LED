/*
 * Interface_FctWS.h
 *
 *  Created on: May 30, 2026
 *      Author: audou
 */

#ifndef LIBRAIRIEWS_INTERFACE_FCTWS_H_
#define LIBRAIRIEWS_INTERFACE_FCTWS_H_

#include "Interface_ws2812b_driver.h"

void PleineCouleur(int, int, int,int);

HAL_StatusTypeDef ws2812bSend(ws2812bLedStruct * ledStrip,TIM_HandleTypeDef *htim, uint32_t channel);

#endif /* LIBRAIRIEWS_INTERFACE_FCTWS_H_ */
