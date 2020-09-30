/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32l1xx_hal.h"

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
#define Bub5V_CTRL_Pin GPIO_PIN_1
#define Bub5V_CTRL_GPIO_Port GPIOC
#define PWR_CTRL_Pin GPIO_PIN_2
#define PWR_CTRL_GPIO_Port GPIOC
#define KEY2_Pin GPIO_PIN_3
#define KEY2_GPIO_Port GPIOC
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOA
#define PWR_5V_CTRL_Pin GPIO_PIN_1
#define PWR_5V_CTRL_GPIO_Port GPIOA
#define AD7799_CS_Pin GPIO_PIN_4
#define AD7799_CS_GPIO_Port GPIOA
#define KEY3_Pin GPIO_PIN_4
#define KEY3_GPIO_Port GPIOC
#define AD5V_CTRL_Pin GPIO_PIN_5
#define AD5V_CTRL_GPIO_Port GPIOC
#define KEY4_Pin GPIO_PIN_0
#define KEY4_GPIO_Port GPIOB
#define AD3_3V_CTRL_Pin GPIO_PIN_1
#define AD3_3V_CTRL_GPIO_Port GPIOB
#define Bub_State_Pin GPIO_PIN_10
#define Bub_State_GPIO_Port GPIOB
#define Bub_Det_Pin GPIO_PIN_11
#define Bub_Det_GPIO_Port GPIOB
#define Bub_Det_EXTI_IRQn EXTI15_10_IRQn
#define LCD_CS_Pin GPIO_PIN_12
#define LCD_CS_GPIO_Port GPIOB
#define LCD_SCK_Pin GPIO_PIN_13
#define LCD_SCK_GPIO_Port GPIOB
#define LCD_RST_Pin GPIO_PIN_14
#define LCD_RST_GPIO_Port GPIOB
#define LCD_SDA_Pin GPIO_PIN_15
#define LCD_SDA_GPIO_Port GPIOB
#define BEEP_Pin GPIO_PIN_6
#define BEEP_GPIO_Port GPIOC
#define LCD5V_CTRL_Pin GPIO_PIN_7
#define LCD5V_CTRL_GPIO_Port GPIOC
#define LCD_BK_CTRL_Pin GPIO_PIN_8
#define LCD_BK_CTRL_GPIO_Port GPIOC
#define LCD3_3V_CTRL_Pin GPIO_PIN_9
#define LCD3_3V_CTRL_GPIO_Port GPIOC
#define LCD_A0_Pin GPIO_PIN_8
#define LCD_A0_GPIO_Port GPIOA
#define BLE_UART_TX_Pin GPIO_PIN_9
#define BLE_UART_TX_GPIO_Port GPIOA
#define BLE_UART_RX_Pin GPIO_PIN_10
#define BLE_UART_RX_GPIO_Port GPIOA
#define BLE_SHDN_Pin GPIO_PIN_11
#define BLE_SHDN_GPIO_Port GPIOA
#define LED_RED_Pin GPIO_PIN_10
#define LED_RED_GPIO_Port GPIOC
#define LED_YELLOW_Pin GPIO_PIN_11
#define LED_YELLOW_GPIO_Port GPIOC
#define LED_BLUE_Pin GPIO_PIN_12
#define LED_BLUE_GPIO_Port GPIOC
#define BLE_WAKEUP_Pin GPIO_PIN_5
#define BLE_WAKEUP_GPIO_Port GPIOB
#define BLE_DON_Pin GPIO_PIN_6
#define BLE_DON_GPIO_Port GPIOB
#define BLE_DON_EXTI_IRQn EXTI9_5_IRQn
#define BLE_RST_Pin GPIO_PIN_7
#define BLE_RST_GPIO_Port GPIOB
#define BLE_STATE_Pin GPIO_PIN_8
#define BLE_STATE_GPIO_Port GPIOB
#define BLE_DIN_Pin GPIO_PIN_9
#define BLE_DIN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
