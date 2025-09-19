// TADALAS BRANCH - F0
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
#include "stm32f0xx.h"

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
// Performance timing variables
int start_time = 0;
int end_time = 0;
int wall_clock_time = 0;
uint64_t checksum = 0;
// NOTE: STM32F0 has no cycle counter (DWT->CYCCNT), so only SysTick (ms) timing works
uint32_t elapsed_clock_cycles = 0; // Placeholder (not valid on F0)
double through_put = 0;
int imageSize[5] = {128,160,192,224,256};
int max_iter = 100;

// test of resolutions
int resolutions[][2] = {
    {128, 128},
    {320, 240},
    {640, 480},
    {1280, 720},
    {1920, 1080}
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
// Mandelbrot functions
uint64_t calculate_mandelbrot_fixed_point_arithmetic(int width, int height, int max_iterations);
uint64_t calculate_mandelbrot_double(double width, double height, double max_iterations);
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
 // int height, width;
  //width = height = imageSize[0];
  //width = height = imageSize[1];
  //width = height = imageSize[2];
  //width = height = imageSize[3];
  //width = height = imageSize[4]; // Using 256x256 test size
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();

  /* USER CODE BEGIN Init */
  // No DWT cycle counter available on Cortex-M0, so we only use HAL_GetTick()
  /* USER CODE END Init */

  SystemClock_Config();

  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  int width = resolutions[4][0];
  int height = resolutions[4][1];
  // Turn on LED0 to signal start
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

  // Record start time
  start_time = HAL_GetTick();

  // Run Mandelbrot (choose one implementation)
  checksum = calculate_mandelbrot_fixed_point_arithmetic(width, height, max_iter);
  //checksum = calculate_mandelbrot_double(width, height, max_iter);

  // Record end time
  end_time = HAL_GetTick();

  // Execution stats
  wall_clock_time = end_time - start_time;
  elapsed_clock_cycles = 48000000*(wall_clock_time/1000); // Not available on F0 so needs to be caculated
  through_put = (width * height) * 1000.0 / wall_clock_time;

  // Turn on LED1 to indicate end of operation
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

  // Keep LEDs ON for 2s
  HAL_Delay(2000);

  // Turn OFF LEDs
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
 // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

  /* USER CODE END 2 */

  while (1)
  {
    /* USER CODE BEGIN WHILE */
    // Loop idle – could repeat benchmarking with different sizes here
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    //TODO: Add profiling of other image sizes if required
    /* USER CODE END 3 */
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,
                          GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */
uint64_t calculate_mandelbrot_fixed_point_arithmetic(int width, int height, int max_iterations){
    uint64_t mandelbrot_sum = 0;
    int x0, y0, xi, yi, iteration, x, y, temp;
    const int S = 1000000; // scaling factor

    height = height * S;
    width  = width  * S;

    for (y = 0; y < height - 1*S; y += 1*S) {
        for (x = 0; x < width - 1*S; x += 1*S) {
            x0 = (((x/width)*S)*3500000)/S - 2500000;
            y0 = (((y/height)*S)*2000000)/S - 1000000;
            xi = 0;
            yi = 0;
            iteration = 0;
            while ((iteration < max_iterations) && ((xi*xi)/S + (yi*yi)/S <= 4*S)) {
                temp = (xi*xi)/S - (yi*yi)/S;
                yi = 2*xi*yi/S + y0;
                xi = temp + x0;
                iteration++;
            }
            mandelbrot_sum += iteration;
        }
    }
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
/* USER CODE END 4 */

void Error_Handler(void)
{
  __disable_irq();
  while (1) { }
}
