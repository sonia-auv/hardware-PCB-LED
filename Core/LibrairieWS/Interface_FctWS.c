/*
 * Intreface_FctWS.c
 *
 *  Created on: May 30, 2026
 *      Author: audou
 */

#include "../Inc/main.h"
#include "Interface_FctWs.h"
#include "Interface_ws2812b_driver.h"
extern ws2812bLedStruct ledStrip;
/*
HAL_StatusTypeDef ws2812bSend(ws2812bLedStruct * ledStrip,TIM_HandleTypeDef * htim, uint32_t channel)
{
	if(ledStrip->dataSentFlag == true)
	{
		ws2812bGetBytesArray(ledStrip);
		//void(ledStrip);
		HAL_TIM_PWM_Start_DMA(htim, channel, (uint32_t *)ledStrip->pwmData, ledStrip->bytesToSend);
		ledStrip->dataSentFlag = false;
		return HAL_OK;

	}
	else
	{
		return HAL_BUSY;
	}
}
*/
HAL_StatusTypeDef ws2812bSend(ws2812bLedStruct * ledStrip,
                             TIM_HandleTypeDef *htim,
                             uint32_t channel)
{
    if(ledStrip->dataSentFlag == false)
    {
        return HAL_BUSY;
    }

    ws2812bGetBytesArray(ledStrip);

    ledStrip->dataSentFlag = false; // IMPORTANT avant envoi

    HAL_TIM_PWM_Start_DMA(htim, channel,
                          (uint32_t *)ledStrip->pwmData,
                          ledStrip->bytesToSend);

    return HAL_OK;
}

void PleineCouleur(int R, int G, int B,int NLED){
	for (int i =0; i-1<NLED; i++){
		ws2812bSetRGB(&ledStrip,i,R,G,B);
	}
	ws2812bSend(&ledStrip,&htim2,TIM_CHANNEL_2);
}
