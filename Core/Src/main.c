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
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "ssd1306.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PWM_ARR 1000
#define PWM_MID_CCR 500
#define PWM_INCRENEMT 100
#define V_DC 11.3f // V

#define MAX_NUMBER_OF_SWIPES 32

#define OLED_REFRESH_RATE 200 // ms
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint16_t pwm_ccr = PWM_MID_CCR;
volatile uint8_t up_down_dir = 0;

volatile uint16_t number_of_swipes = 0;

uint32_t softTimerOLED;
char lcd_line[32];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
	MX_USART2_UART_Init();
	MX_I2C1_Init();
	MX_TIM2_Init();
	/* USER CODE BEGIN 2 */
	ssd1306_Init();
	ssd1306_Fill(Black);
	ssd1306_SetCursor(21, 2);
	ssd1306_WriteString("ufnalski.edu.pl", Font_6x8, White);
	ssd1306_SetCursor(6, 14);
	ssd1306_WriteString("Nissan Qashqai (J11)", Font_6x8, White);
	ssd1306_SetCursor(16, 26);
	ssd1306_WriteString("rear wiper motor", Font_6x8, White);
	ssd1306_UpdateScreen();

	softTimerOLED = HAL_GetTick();

	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, PWM_MID_CCR);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2); // PWM_L
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, PWM_ARR - PWM_MID_CCR);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4); // PWM_R
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		if ((HAL_GetTick() - softTimerOLED) > OLED_REFRESH_RATE)
		{
			softTimerOLED = HAL_GetTick();
			HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

			ssd1306_SetCursor(15, 42);
			sprintf(lcd_line, "v_out = %.1f V  ",
					((float) PWM_MID_CCR - (float) pwm_ccr) / PWM_MID_CCR * V_DC);
			ssd1306_WriteString(lcd_line, Font_6x8, White);
			ssd1306_SetCursor(15, 54);
			sprintf(lcd_line, "n_of_swipes = %d  ", number_of_swipes);
			ssd1306_WriteString(lcd_line, Font_6x8, White);
			ssd1306_UpdateScreen();
		}

		if (number_of_swipes >= MAX_NUMBER_OF_SWIPES)  // stop the wiper
		{
			pwm_ccr = PWM_MID_CCR;
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pwm_ccr);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, PWM_ARR - pwm_ccr);
		}
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct =
	{ 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct =
	{ 0 };

	/** Configure the main internal regulator output voltage
	 */
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure LSE Drive Capability
	 */
	HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE
			| RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSICalibrationValue = 0;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 40;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
		Error_Handler();
	}

	/** Enable MSI Auto calibration
	 */
	HAL_RCCEx_EnableMSIPLLMode();
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == WHITE_BUTTON_Pin)
	{
		number_of_swipes = 0;

		if (up_down_dir == 0)
		{
			if (pwm_ccr >= PWM_INCRENEMT)
			{
				pwm_ccr -= PWM_INCRENEMT;
			}
			else
			{
				up_down_dir = 1;
			}
		}
		else
		{
			if (PWM_ARR - pwm_ccr >= PWM_INCRENEMT)
			{
				pwm_ccr += PWM_INCRENEMT;
			}
			else
			{
				up_down_dir = 0;
			}
		}
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pwm_ccr);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, PWM_ARR - pwm_ccr);
	}

	if (GPIO_Pin == POSITION_SENSE_Pin)
	{
		number_of_swipes++;
	}
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
