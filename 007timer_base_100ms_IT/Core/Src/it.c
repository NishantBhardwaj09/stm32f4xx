#include "main.h"

extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htimer6;
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler(); // to process the systick interrupt
}

void TIM6_DAC_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer6);
}

