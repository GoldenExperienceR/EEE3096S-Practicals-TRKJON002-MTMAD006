// JONATHANS BRANCH - 3F4
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
// TASKS 2: CHANGING THE MAXIMUM INTRATION VARIABLE
#define MAX_ITER 100
//#define MAX_ITER 200
//#define MAX_ITER 400
//#define MAX_ITER 600
///#define MAX_ITER 1000

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
int start_time = 0;
int end_time = 0;
int execution_time = 0;
uint64_t checksum = 0;
int imageSize[5] = { 128, 160, 192, 224, 256 };

//Global variables to track risk of overflow for Task 7
int64_t max_xi = 0;
int64_t max_yi = 0;


/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
uint64_t calculate_mandelbrot_fixed_point_arithmetic(int width, int height, int max_iterations);
uint64_t calculate_mandelbrot_double(double width, double height, double max_iterations);
uint64_t calculate_mandelbrot_float(int width, int height, int max_iterations);

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

  /* USER CODE END 2 */
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
  int height, width;
    //width = height = imageSize[0]; //128
    //width = height = imageSize[1]; //160
    //width = height = imageSize[2]; //192
    //width = height = imageSize[3]; //224
    width = height = imageSize[4];	//256
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

     start_time = HAL_GetTick();
     checksum = calculate_mandelbrot_fixed_point_arithmetic(width, height, MAX_ITER);
     //checksum = calculate_mandelbrot_double(width, height, MAX_ITER);
     //checksum = calculate_mandelbrot_float(width, height, MAX_ITER);
     end_time = HAL_GetTick();
     execution_time = end_time - start_time;
     HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
     HAL_Delay(2000);
     HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1);
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
	  // Toggle the LEDs with a 1s delay
	  // Code to check if the board is working

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */

uint64_t calculate_mandelbrot_fixed_point_arithmetic(int width, int height, int max_iterations){

	uint64_t mandelbrot_sum = 0;

	  // Defining scaling factor
	  //const int64_t S = 10000000; //10^6
	  //const int64_t S = 100000; //10^4
	  const int64_t S = 10000; //10^3
	  // Fixed-point equivalents of the constants used in the function's operations
	  const int64_t const_2_5=  2.5*S;
	  const int64_t const_3_5 = 3.5*S;
	  const int64_t const_1 = 1*S;
	  const int64_t const_2 = 2*S;
	  const int64_t const_4 = 4*S;

	  int64_t xi, yi, temp, x0, y0;
	  int iteration;

	  for (int y = 0; y < height; ++y) {
	    for (int x = 0; x < width; ++x) {
	      // x0 = (x/width) * 3.5 - 2.5
	      x0 = (x * const_3_5) / width - const_2_5;
	      // y0 = (y/height) * 2.0 - 1.0
	      y0 = (y * const_2) / height - const_1;

	      xi = 0;
	      yi = 0;
	      iteration = 0;

	      while (iteration < max_iterations && (xi * xi/S + yi * yi/S) <= const_4) {
	        temp = (xi * xi)/S - (yi * yi)/S;
	        yi = (2 * xi * yi / S) + y0;
	        xi = temp + x0;
	        iteration++;
	      }

	      if (llabs(xi) > max_xi) max_xi = llabs(xi);
	      if (llabs(yi) > max_yi) max_yi = llabs(yi);
	      mandelbrot_sum += iteration;
	    }
	  }
	  return mandelbrot_sum;

}
//TODO: Mandelbrot using variable type double
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

            // Task 7: Update global Max_xi and max_yiif new max found
            	         if (llabs(xi) > max_xi) max_xi = llabs(xi);
            	         if (llabs(yi) > max_yi) max_yi = llabs(yi);

            mandelbrot_sum += iteration;
        }
    }

    return mandelbrot_sum;
}

//TODO: Mandelbrot using variable type float
uint64_t calculate_mandelbrot_float(int width, int height, int max_iterations) {
	uint64_t mandelbrot_sum = 0;
    for (int py = 0; py < height; py++) {
        for (int px = 0; px < width; px++) {
            float x0 = ((float)px / (float)width) * 3.5 - 2.5;
            float y0 = ((float)py / (float)height) * 2.0 - 1.0;
            float xi = 0.0, yi = 0.0;

            uint64_t iteration = 0;
            while ((iteration < max_iterations) && ((xi * xi + yi * yi) <= 4.0)) {
                float temp = xi * xi - yi * yi;
                yi = 2.0 * xi * yi + y0;
                xi = temp + x0;
                iteration++;
            }

            mandelbrot_sum += iteration;
        }
    }

    return mandelbrot_sum;
}

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
