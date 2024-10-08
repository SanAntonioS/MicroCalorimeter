/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "iwdg.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sys.h"
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

static rt_sem_t sem;

rt_sem_t get_semaphore(void) {
    return sem;
}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void led1_thread_entry(void* parameter);
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
  MX_USART3_UART_Init();
  MX_IWDG_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
//	HAL_NVIC_DisableIRQ(EXTI4_IRQn);
	I2C_Config();
	rt_show_version();
//	InitAD7177(&device1,0);						//AD7177初始化
//	InitAD7177(&device2,0);						//AD7177初始化
//	InitAD7177(&device3,0);						//AD7177初始化
//	InitAD7177(&device4,0);						//AD7177初始化
//	InitAD7177(&device5,0);						//AD7177初始化
//	InitAD7177(&device6,0);						//AD7177初始化
//	InitAD7177(&device7,0);						//AD7177初始化
//	InitAD7177(&device8,0);						//AD7177初始化
//	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
//	cpu_usage_init();
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	sem = rt_sem_create("my_semaphore", 1, RT_IPC_FLAG_FIFO);
		
	rt_thread_t led1_thread =              /* 线程控制块指针 */
	rt_thread_create("led1",               /* 线程名字 */
										led1_thread_entry,   /* 线程入口函数 */
										RT_NULL,             /* 线程入口函数参数 */
										512,                 /* 线程栈大小 */
										5,                   /* 线程的优先级 */
										10);                 /* 线程时间片 */
								 
	if (led1_thread != RT_NULL)
			rt_thread_startup(led1_thread);
	else
			return -1;

//	rt_thread_t cpu_usage_thread =                   // 线程控制块指针
//	rt_thread_create("cpu_usage_thread",           	 // 线程名字
//										cpu_usage_thread_entry,        // 线程入口函数
//										RT_NULL,                       // 入口函数参数
//										255,                           // 线程栈大小
//										5,                             // 线程优先级
//										20);                           // 线程时间片

//	if(cpu_usage_thread != RT_NULL)
//			rt_thread_startup(cpu_usage_thread);
//	else
//			return -1; 

	rt_thread_t watchdog_thread =                    // 线程控制块指针
	rt_thread_create("watchdog",           					 // 线程名字
										watchdog_thread_entry,         // 线程入口函数
										RT_NULL,                       // 入口函数参数
										255,                           // 线程栈大小
										5,                             // 线程优先级
										20);                           // 线程时间片

	if(watchdog_thread != RT_NULL)
			rt_thread_startup(watchdog_thread);
	else
			return -1; 
	
	rt_thread_t data_conversion_thread =             // 线程控制块指针
	rt_thread_create("data_conversion",           	 // 线程名字
										data_conversion_thread_entry,  // 线程入口函数
										RT_NULL,                       // 入口函数参数
										255,                           // 线程栈大小
										3,                             // 线程优先级
										20);                           // 线程时间片

	if(data_conversion_thread != RT_NULL)
			rt_thread_startup(data_conversion_thread);
	else
			return -1; 
}

static void led1_thread_entry(void* parameter)
{	
	while (1)
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
		rt_thread_delay(20);   /* 延时20个tick */
		
		HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
		rt_thread_delay(940);   /* 延时1000个tick */
		
//		at24c256_test();
	}
}

  /* USER CODE END 3 */

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
