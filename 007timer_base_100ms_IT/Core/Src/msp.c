#include "main.h"

void HAL_MspInit(void)
{
	//Here will do low level processor specific inits

	//1. Set up the priority grouping of arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. enable the required system exception of arm cortex mx processor

	SCB->SHCSR |= 0x7 << 16; //usage fault, bus fault, memory fault system exception

	//3. configure the priority for the system exception (optional as default priority is zero which is the maximum priority )
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer)
{
	//enable the clock for TIM6 peripheral
	__HAL_RCC_TIM6_CLK_ENABLE();

	//enable IRQ of TIM6
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	//setup priority for TIM6_DAC_IRQn
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn,15,0);
}
