/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ledtest_Pin GPIO_PIN_2
#define ledtest_GPIO_Port GPIOA
#define signalkill_Pin GPIO_PIN_3
#define signalkill_GPIO_Port GPIOA
#define switch_Pin GPIO_PIN_1
#define switch_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define PILOTEPA2_PORT GPIOA
#define PILOTEPA2_PIN GPIO_PIN_2
#define INTERFACE_LED_ROUGE_VALEUR_POUR_ALLUMER 1
#define INTERFACE_LED_ROUGE_VALEUR_POUR_ETEINDRE 0
#define DUREE_ATTENTE_LEDRED1 500
#define DUREE_ATTENTE_LEDRED2 600

//Definition des Pins pour le bouton
#define PILOTESWITCH1PORT GPIOB
#define PILOTESWITCH1PIN GPIO_PIN_1
extern int Bouton1_Val;

extern TIM_HandleTypeDef htim2;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
