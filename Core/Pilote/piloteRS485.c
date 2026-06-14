/*
 * piloteRS485.c
 *
 *  Created on: Jun 14, 2026
 *      Author: ilyes
 */
#include "Pilote_Attente.h"
#include "piloteRS485.h"
#include "main.h"

extern UART_HandleTypeDef huart2;

#define PILOTERS485_UART              huart2

#define PILOTERS485_DE_PORT           RS485_DE_GPIO_Port 
#define PILOTERS485_DE_PIN            RS485_DE_Pin

#define PILOTERS485_RE_PORT           RS485_RE_GPIO_Port
#define PILOTERS485_RE_PIN            RS485_RE_Pin

#define PILOTERS485_TE_PORT           RS485_TE_GPIO_Port
#define PILOTERS485_TE_PIN            RS485_TE_Pin

#define PILOTERS485_TIMEOUT_MS        100
#define PILOTERS485_DELAI_FIN_TRANSMISSION_MS  20

void piloteRS485_initialise(void)
{
    HAL_GPIO_WritePin(PILOTERS485_DE_PORT, PILOTERS485_DE_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PILOTERS485_RE_PORT, PILOTERS485_RE_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PILOTERS485_TE_PORT, PILOTERS485_TE_PIN, GPIO_PIN_SET);
}


uint8_t piloteRS485_recoitOctet(void)
{
    uint8_t octet = 0;

    HAL_UART_Receive(
        &PILOTERS485_UART,
        &octet,
        1,
        HAL_MAX_DELAY
    );

    return octet;
}

uint8_t piloteRS485_octetDisponible(void)
{
    if(__HAL_UART_GET_FLAG(&PILOTERS485_UART, UART_FLAG_RXNE) != RESET)
    {
        return 1;
    }
    return 0;
}

void piloteRS485_transmetBloc(uint8_t *bloc, uint8_t longueur)
{
    HAL_GPIO_WritePin(PILOTERS485_RE_PORT, PILOTERS485_RE_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(PILOTERS485_DE_PORT, PILOTERS485_DE_PIN, GPIO_PIN_SET);

    HAL_UART_Transmit(&PILOTERS485_UART, bloc, longueur, PILOTERS485_TIMEOUT_MS);

    while(__HAL_UART_GET_FLAG(&PILOTERS485_UART, UART_FLAG_TC) == RESET);

    piloteDelai_attendreMs(PILOTERS485_DELAI_FIN_TRANSMISSION_MS);

    HAL_GPIO_WritePin(PILOTERS485_DE_PORT, PILOTERS485_DE_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PILOTERS485_RE_PORT, PILOTERS485_RE_PIN, GPIO_PIN_RESET);
}
