#include "stm32f4xx_hal.h"
#include "main.h"
#include "string.h"
#include "stdio.h"

#define TRUE  1
#define FALSE 0

void SystemCLk_Config(void);
void Error_handler(void);
void GPIO_Init(void);
void timer6_init(void);

TIM_HandleTypeDef htimer6 ;

int main(void)
{
	HAL_Init();
	SystemCLk_Config();
	GPIO_Init();
	timer6_init();

	//start timer
	HAL_TIM_Base_Start(&htimer6);
	while(1)
	{
		while( !(TIM6->SR & (1 << TIM_SR_UIF) )); //wait till event flag is set
		TIM6->SR = 0 ;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}

	return 0 ;
}

void SystemCLk_Config()
{

}
void GPIO_Init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &ledgpio);
}
void timer6_init(void)
{
	htimer6.Instance = TIM6;
	htimer6.Init.Prescaler = 24;
	htimer6.Init.Period = 64000 - 1;
	if(HAL_TIM_Base_Init(&htimer6) != HAL_OK)
	{
		Error_handler();
	}
}
void Error_handler(void)
{

}



