/*
 * processTestRS485.c
 *
 *  Created on: 19 juin 2026
 *      Author: ilyes
 */
/*
 * processTestRS485.c
 */

#include "main.h"
#include "cmsis_os.h"
#include "processTestRS485.h"
#include "../Service/serviceRS485.h"
#include "RS485_definition.h"


#define PROCESSTESTRS485_ADRESSE_LOCALE    SLAVE_LED
#define PROCESSTESTRS485_NOMBRE_FLASH      3
#define PROCESSTESTRS485_TEMPS_FLASH_MS    100

static void processTestRS485_flashLedReception(void);

void processTestRS485_thread(void *argument)
{
    uint8_t commandesAttendues[] =
    {
        CMD_KEEP_ALIVE
    };

    uint8_t dataRx[SERVICERS485_TAILLE_MAX_DATA];
    uint8_t nbByte;
    uint8_t adresseDestination;

    (void)argument;

    for(;;)
    {
        nbByte = serviceRS485_readAvecSlave(
            commandesAttendues,
            1,
            &adresseDestination,
            dataRx
        );

        if(nbByte > 0)
        {
            if(adresseDestination == PROCESSTESTRS485_ADRESSE_LOCALE)
            {
                processTestRS485_flashLedReception();
            }
        }

        osDelay(10);
    }
}

static void processTestRS485_flashLedReception(void)
{
    for(uint8_t i = 0; i < PROCESSTESTRS485_NOMBRE_FLASH; i++)
    {
        HAL_GPIO_WritePin(ledtest_GPIO_Port, ledtest_Pin, GPIO_PIN_SET);
        osDelay(PROCESSTESTRS485_TEMPS_FLASH_MS);

        HAL_GPIO_WritePin(ledtest_GPIO_Port, ledtest_Pin, GPIO_PIN_RESET);
        osDelay(PROCESSTESTRS485_TEMPS_FLASH_MS);
    }
}
