/*
1. Initialize the HAL
2. Configure the STM32 Clock
3. Configure PA5 as output
	Physical pin on the STM32
	PA = GPIO Port A
	5 = pin 5
4. Repeatedly toggle PA5 every 250 ms
*/


#include "stm32f4xx_hal.h"


static void SystemClock_Config(void) {
	RCC_OscInitTypeDef osc = {0};
	RCC_ClkInitTypeDef clk = {0};

	__HAL_RCC_PWR_CLK_ENABLE();										// Enable the power controller. peripherals themselves have clocks
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);	// This affects what clock speeds are allowed

	osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;	// Use High-Speed Internal oscillator
	osc.HSIState = RCC_HSI_ON;						// Turn on HSI
	osc.PLL.PLLState = RCC_PLL_ON;					// Turn on the PLL Phase-Locked Loop
	osc.PLL.PLLSource = RCC_PLLSOURCE_HSI;			// Tell PLL where its source comes from. PLL input = HSI which is 16MHz
	osc.PLL.PLLM = 16;								// HSI / PLLM = 16 MHz / 16 = 1 MHz PLL input
	osc.PLL.PLLN = 336;								// 1 MHz * PLLN = 1 MHz * 336 = 336 MHz VCO
	osc.PLL.PLLP = RCC_PLLP_DIV4;					// VCO / PLLP = 336 MHz / 4 = 84 MHz PLL output 
	osc.PLL.PLLQ = 7;
	HAL_RCC_OscConfig(&osc);


	clk.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;	// Select which clocks to configure
	clk.SYSCLKSource	 = RCC_SYSCLKSOURCE_PLLCLK;
	clk.AHBCLKDivider	 = RCC_SYSCLK_DIV1;
	clk.APB1CLKDivider	 = RCC_HCLK_DIV2;
	clk.APB2CLKDivider	 = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_2);
}


int main(void) {
	HAL_Init();
	SystemClock_Config();
	
	// LD2 on NUCLEO-F446RE is PA5
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef gpio = {0};
	gpio.Pin = GPIO_PIN_5;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &gpio);

	while (1) {
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		HAL_Delay(250);
	}
}
