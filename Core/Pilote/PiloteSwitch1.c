/*
 * Switch1.c
 *
 *  Created on: May 31, 2026
 *      Author: audou
 */

#include "../Inc/main.h"
#include "PiloteSwitch1.h"

unsigned char PiloteSwitch1_LitEntree(void)
{
return HAL_GPIO_ReadPin(PILOTESWITCH1PORT,PILOTESWITCH1PIN);
}

void PiloteSwitch1_Initialise(void)
{

}
