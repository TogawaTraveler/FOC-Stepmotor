/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AP_Pin GPIO_PIN_4
#define AP_GPIO_Port GPIOA
#define AM_Pin GPIO_PIN_5
#define AM_GPIO_Port GPIOA
#define BP_Pin GPIO_PIN_6
#define BP_GPIO_Port GPIOA
#define BM_Pin GPIO_PIN_7
#define BM_GPIO_Port GPIOA
#define BT0_Pin GPIO_PIN_0
#define BT0_GPIO_Port GPIOB
#define BT1_Pin GPIO_PIN_1
#define BT1_GPIO_Port GPIOB
#define BT2_Pin GPIO_PIN_2
#define BT2_GPIO_Port GPIOB
#define Button_Pin GPIO_PIN_13
#define Button_GPIO_Port GPIOB
#define CS_Pin GPIO_PIN_15
#define CS_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
