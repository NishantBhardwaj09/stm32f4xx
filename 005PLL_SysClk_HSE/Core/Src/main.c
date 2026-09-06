#include "stm32f4xx_hal.h"
#include "main.h"
#include "string.h"
#include "stdio.h"

#define TRUE  1
#define FALSE 0

void SystemCLk_Config_HSE(uint8_t clk_freq);
void UART2_Init(void);
void Error_handler(void);

UART_HandleTypeDef huart2;

int main(void)
{
	char msg[100];
	HAL_Init();

	SystemCLk_Config_HSE(SYS_CLOCK_FREQ_50_MHZ); // after HAL INIT and before peripheral INIT LIKE UART, SPI ,I2C

	UART2_Init();

	memset(msg,0,sizeof(msg));
	sprintf(msg,"SYSCLK : %ldHz\r\n",HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(msg,0,sizeof(msg));
	sprintf(msg,"HCLK   : %ldHz\r\n",HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(msg,0,sizeof(msg));
	sprintf(msg,"PCLK1  : %ldHz\r\n",HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(msg,0,sizeof(msg));
	sprintf(msg,"PCLK2  : %ldHz\r\n",HAL_RCC_GetPCLK2Freq());

	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	while(1);
	return 0 ;
}

void SystemCLk_Config_HSE(uint8_t clk_freq)
{
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;
	uint32_t Flatency = 0 ;

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osc_init.HSEState = RCC_HSE_BYPASS; //by default it is on
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;


	switch (clk_freq)
	{
		case SYS_CLOCK_FREQ_50_MHZ:
		{
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLM = 100;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			Flatency = FLASH_ACR_LATENCY_1WS; //check reference manual
			break;
		}
		case SYS_CLOCK_FREQ_84_MHZ:
		{
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLM = 168;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			Flatency = FLASH_ACR_LATENCY_2WS;
			break;
		}
		case SYS_CLOCK_FREQ_120_MHZ:
		{

			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLM = 240;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			Flatency = FLASH_ACR_LATENCY_3WS;
			break;
		}
		case SYS_CLOCK_FREQ_180_MHZ:
		{
			// enable clk for power controller
			__HAL_RCC_PWR_CLK_ENABLE();
			//set regulator voltage scale as 1
			__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
			//turn on over drive mode of the voltage regulator
			__HAL_PWR_OVERDRIVE_ENABLE();

			//refer the DATASHEET as mentioned there in general operating condition
			// to run the CLK at 180MHz u need to do all these

			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLM = 360;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			Flatency = FLASH_ACR_LATENCY_5WS;
			break;
		}
		default:
			return;
	}

	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
	{
		Error_handler();
	}

	if(HAL_RCC_ClockConfig(&clk_init, Flatency) != HAL_OK)
	{
		Error_handler();
	}

	// SYSTICK configuration
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000); // to generate delay of 1ms
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}

void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 11520;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;

	if( HAL_UART_Init(&huart2) != HAL_OK)
	{
		// there is a problem
		Error_handler();
	}
}

void Error_handler(void)
{

}



