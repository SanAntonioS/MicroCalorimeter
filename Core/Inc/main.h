/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define AD1_CS_Pin GPIO_PIN_4
#define AD1_CS_GPIO_Port GPIOA
#define AD1_SCLK_Pin GPIO_PIN_5
#define AD1_SCLK_GPIO_Port GPIOA
#define AD1_MISO_Pin GPIO_PIN_6
#define AD1_MISO_GPIO_Port GPIOA
#define AD1_MOSI_Pin GPIO_PIN_7
#define AD1_MOSI_GPIO_Port GPIOA
#define AD_EXTI_Pin GPIO_PIN_4
#define AD_EXTI_GPIO_Port GPIOC
#define AD_EXTI_EXTI_IRQn EXTI4_IRQn
#define AD2_CS_Pin GPIO_PIN_7
#define AD2_CS_GPIO_Port GPIOE
#define AD3_CS_Pin GPIO_PIN_8
#define AD3_CS_GPIO_Port GPIOE
#define AD4_CS_Pin GPIO_PIN_9
#define AD4_CS_GPIO_Port GPIOE
#define AD5_CS_Pin GPIO_PIN_10
#define AD5_CS_GPIO_Port GPIOE
#define AD6_CS_Pin GPIO_PIN_11
#define AD6_CS_GPIO_Port GPIOE
#define AD7_CS_Pin GPIO_PIN_12
#define AD7_CS_GPIO_Port GPIOE
#define AD8_CS_Pin GPIO_PIN_13
#define AD8_CS_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_12
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_13
#define LED2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
