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
#include "stdint.h"
#include "stm32f4xx.h"

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
int start_time = 0;
int end_time = 0;
int wall_clock_time = 0;
uint64_t checksum = 0;
int start_cycle = 0;
int end_cycle = 0;
int elapsed_clock_cycles = 0;
double through_put = 0;
int imageSize[5] = {128,160,192,224,256};
int max_iter = 100;
double x = 0;
int cycles_per_pixel = 0;

// test of resolutions
/*int resolutions[][2] = {
    {128, 128},
    {320, 240},
    {640, 480},
    {1280, 720},
    {1920, 1080}
};*/
//int num_resolutions = sizeof(resolutions) / sizeof(resolutions[0]);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
//TODO: Define any function prototypes you might need such as the calculate Mandelbrot function among others
uint64_t calculate_mandelbrot_fixed_point_arithmetic(int width, int height, int max_iterations);
uint64_t calculate_mandelbrot_double(double width, double height, double max_iterations);
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

	  // image dimesnisons
	  int height, width;
	  //width = height = imageSize[0];
	  //width = height = imageSize[1];
	  //width = height = imageSize[2];
	  //width = height = imageSize[3];
	  width = height = imageSize[4];



  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  DWT_init();// Initializing DWT counter
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
 // for (int i = 0; i < num_resolutions; i++) {
     // int width = resolutions[4][0];
      // int height = resolutions[4][1];

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET); // CONFIGURE LED 0 ON
  // Record the start time and cycles
  	  start_time = HAL_GetTick();
  	  start_cycle = DWT->CYCCNT;

  	  //Call the Mandelbrot Function and store the output in the checksum variable defined initially
		  //checksum = calculate_mandelbrot_fixed_point_arithmetic(width, height, max_iter);
		  checksum = calculate_mandelbrot_double(width, height, max_iter);

  	  // Record the end time
		  end_time = HAL_GetTick();
		  end_cycle = DWT->CYCCNT;

  	  // Calculate the execution time and cycles
    	wall_clock_time = end_time - start_time;
    	elapsed_clock_cycles = end_cycle - start_cycle;

    	// calculation of through
    	cycles_per_pixel = elapsed_clock_cycles/(width*height);
    	through_put = 120000000 / cycles_per_pixel ;


  	  // Turn on LED 1 to signify the end of the operation
    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

  	  // Hold the LEDs on for a 2s delay
    	HAL_Delay(667); // had originally used 2000 as recommended by HAL library but found LED didn't turn on after 2s

  	  // Turn off the LEDs
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
 // }
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

uint64_t calculate_mandelbrot_fixed_point_arithmetic(int width, int height, int max_iterations){
	uint64_t mandelbrot_sum = 0;

	//TODO: Complete the function implementation
	int x0, y0, xi, yi, iteration, x, y, temp;
	// Defining scaling factor
	const int S = 1000000;
	//Scaling height and width
	height = height*S;
	width = width*S;
	for(y = 0; y < height - 1*S; y = y + 1*S){
		for(x = 0; x < width - 1*S; x = x + 1*S){
			x0 = (((x/width)*S)*3500000)/S - 2500000;
			y0 = (((y/height)*S)*2000000)/S - 1000000;
			xi = 0;
			yi = 0;
			iteration = 0;
			while((iteration < max_iterations)&&((xi^2)/S + (yi^2)/S <= 4*S)){
				temp = (xi^2)/S - (yi^2)/S;
				yi = 2*xi*yi/S +y0;
				xi = temp + x0;
				iteration = iteration + 1;
			};
			mandelbrot_sum = mandelbrot_sum + iteration;
		};
	};
	return mandelbrot_sum;
}

uint64_t calculate_mandelbrot_double(double width, double height, double max_iterations) {
	uint64_t mandelbrot_sum = 0;
	for (int py = 0; py < (int)height; py++) {
		for (int px = 0; px < (int)width; px++) {
			double x0 = ((double)px / width) * 3.5 - 2.5;
			double y0 = ((double)py / height) * 2.0 - 1.0;
			double xi = 0.0, yi = 0.0;
			uint64_t iteration = 0;
			while ((iteration < max_iterations) && ((xi * xi + yi * yi) <= 4.0)) {
				double temp = xi * xi - yi * yi;
				yi = 2.0 * xi * yi + y0;
				xi = temp + x0;
				iteration++;
			}
			mandelbrot_sum += iteration;
		}
	}
	return mandelbrot_sum;
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
