//TADALAS BRANCH - F4
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
//TODO: Define variables you think you might need
// - Performance timing variables (e.g execution time, throughput, pixels per second, clock cycles)

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
//TODO: Define any function prototypes you might need such as the calculate Mandelbrot function among others
void LED_ON(void);
uint64_t Calculate_fixed_Mandelbrot(int width, int height,int maxInter );
uint64_t Calculate_double_Mandelbrot(double width, double height,double maxInter );
static inline void DWT_init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	int sizes[] = {128};// 160, 192,224, 256
	int maxIter = 100;
	volatile uint64_t elapsed_Cycles;
	volatile uint64_t elapsed_Time;

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
  /* USER CODE BEGIN 2 */


  // turning on LED 0 to signal start
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET); // CONFIGURE LED 0 ON
  	  	HAL_Delay(2000); // remove once perfomance test are implmented

  // intiating testing
  	  	//for (int i = 0; i < 5; i++){
  	  	int size = 128;

  	  	DWT_init();// intializing DWT counter

  	  	uint64_t startCycle = DWT->CYCCNT;
  	  	uint64_t startTime = HAL_GetTick();

  	  	int checksum = Calculate_fixed_Mandelbrot(size, size, maxIter );

  	  	uint64_t endCycle = DWT->CYCCNT;
  	  	uint64_t endTime = HAL_GetTick();

  	  	elapsed_Cycles = endCycle - startCycle;
  	  	elapsed_Time = endTime - startTime;
  	  	uint64_t throughPut = (size*size)/(elapsed_Time/1000);

  	  //printf("Image Size: %dx%d\n", size, size);
  	          printf("Checksum = %d\n", checksum);
  	          //printf("Wall-clock time = %lu ms\n", elapsed_ms);
  	          //printf("CPU cycles = %lu\n", elapsed_cycles);
  	         // printf("Throughput = %.2f pixels/s\n\n", throughPut);


 // 	  	}

  // turing on LED 1 to signal end of test
  	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
  	  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
  	HAL_Delay(3000);
  // reset LED

  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
  		  HAL_Delay(2000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  //TODO: Visual indicator: Turn on LED0 to signal processing start


	  //TODO: Benchmark and Profile Performance

	  //TODO: Visual indicator: Turn on LED1 to signal processing start


	  //TODO: Keep the LEDs ON for 2s
	  			  //TODO: Turn OFF LEDs

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 144;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 PB2 PB3
                           PB4 PB5 PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
//TODO: Function signatures you defined previously , implement them here
void LED_ON(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET); // CONFIGURE LED 0 ON
	HAL_Delay(2000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET); // CONFIGURE LED 0 OFF
}
uint64_t Calculate_fixed_Mandelbrot(int width, int height,int maxInter )
{
	uint64_t checksum = 0;
	// scaling factor S
	const int S = 1000000;
	height = height *S;
	width = width *S;

	for(int y = 0; (y < height-1*S); y = y +1*S)
	{
		for(int x = 0;(x < width-1*S); x = x + 1*S )
		{
			int x0,y0,xi,yi;
			int iteration = 0;
			x0 = (((x/width)*S)*3500000)/S - 2500000;
			y0 = (((y/height)*S)*2000000)/S - 1000000;
			xi = 0, yi = 0;
			while (iteration < maxInter && ((xi*xi)/S + (yi*yi)/S) <= 4*S)
			{
				int temp = (xi*xi)/S + (yi*yi)/S;
				yi = 2*xi*yi/S + y0;
				xi = temp + x0;
				iteration ++;

			}
			checksum = checksum + iteration;

		}
	}
	return checksum;
}

uint64_t Calculate_double_Mandelbrot(double width, double height,double maxInter )
{
	uint64_t checksum = 0;

	for(int y = 0; (y < (int)height-1); y = y +1)
	{
		for(int x = 0;(x < (int)width-1); x = x + 1)
		{
			double x0,y0,xi,yi;
			uint64_t iteration = 0;
			x0 = ((double)x/width) * 3.5 - 2.5;
			y0 = ((double)y/height) * 2.0 - 1.0;
			xi = 0.0, yi = 0.0;
			while (iteration < maxInter && ((xi*xi) + (yi*yi)) <= 4.0)
			{
				double temp = (xi*xi) - (yi*yi);
				yi = 2*xi*yi + y0;
				xi = temp + x0;
				iteration ++;

			}
			checksum = checksum + iteration;

		}
	}
	return checksum;
}

static inline void DWT_init(void)
{
		CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
		// Only write to LAR if it exists
		#ifdef DWT_LAR
		    DWT->LAR = 0xC5ACCE55;  // Unlock access (for M7/M33)
		#endif

		DWT ->CYCCNT = 0;
		DWT ->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

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
#ifdef USE_FULL_ASSERT
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

