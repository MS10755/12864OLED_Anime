/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "U8g2lib.h"
#include "page.h"
#include "HAL.h"
#include "Juan_EventButton.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
page_manager_t page_manager;
U8G2_UC1701_MINI12864_f_4W_HW_SPI_STM32 u8g2(U8G2_R0);

Juan_EventButton_t key1;
Juan_EventButton_t key2;
Juan_EventButton_t key3;
Juan_EventButton_t key4;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static int pressed_key = -1;
void key_event_handler(void * btn,ButtonEvent_t event){
  if(btn == &key1 && event == BUTTON_EVENT_PRESSED){
    pressed_key = 1;
  }else if(btn == &key2 && event == BUTTON_EVENT_PRESSED){
    pressed_key = 2;
  }else if(btn == &key3 && event == BUTTON_EVENT_PRESSED){
    pressed_key = 3;
  }else if(btn == &key4 && event == BUTTON_EVENT_PRESSED){
    pressed_key = 4;
  }
}
int get_key(){
  int key;
  Juan_EventMonitor(&key1,HAL_GPIO_ReadPin(KEY2_Port,KEY2_Pin));
  Juan_EventMonitor(&key2,HAL_GPIO_ReadPin(KEY1_Port,KEY1_Pin));
  Juan_EventMonitor(&key3,HAL_GPIO_ReadPin(KEY0_Port,KEY0_Pin));
  Juan_EventMonitor(&key4,HAL_GPIO_ReadPin(KEY_WKUP_Port,KEY_WKUP_Pin));
  if(pressed_key > 0){
    key = pressed_key;
    pressed_key = -1;
    return key;
  }
    return -1;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  setvbuf(stdout, NULL, _IONBF, 0);
  u8g2.begin();

  PAGE_INIT(PAGE_ID_MAIN);
  PAGE_INIT(PAGE_ID_MENU);
  PAGE_INIT(PAGE_ID_CLOCK);
  PAGE_INIT(PAGE_ID_TOOLBOX);
  PAGE_INIT(PAGE_ID_GAME);
  page_switch(&page_manager,PAGE_ID_MAIN);

  Juan_EventButtonInitStatic(&key1,1,500,3000,3000);
  Juan_EventButtonInitStatic(&key2,1,500,3000,3000);
  Juan_EventButtonInitStatic(&key3,1,500,3000,3000);
  Juan_EventButtonInitStatic(&key4,0,500,3000,3000);
  Juan_AddEventHandler(&key1,key_event_handler);
  Juan_AddEventHandler(&key2,key_event_handler);
  Juan_AddEventHandler(&key3,key_event_handler);
  Juan_AddEventHandler(&key4,key_event_handler);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    page_manager_loop(&page_manager);
    int key = get_key();
    if(key > 0 ){
      page_key_event_send(&page_manager,key,0);
    }
    HAL_Delay(1);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
