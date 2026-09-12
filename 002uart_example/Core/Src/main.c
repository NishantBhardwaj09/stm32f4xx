#include "stm32f4xx_hal.h"
#include "main.h"
#include "string.h"

void SystemClockConfig(void);
void UART2_Init(void);
void Error_handler(void);
uint8_t convert_to_capital(uint8_t data);


char* data = "Hi, I am Nishant\r\n";

UART_HandleTypeDef huart2;

int main(void)
{
	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	uint16_t data_len = strlen(data);
	HAL_UART_Transmit(&huart2, (uint8_t*)data, data_len, HAL_MAX_DELAY);

	uint8_t data_rcv ;
	uint8_t data_buffer[100];
	uint32_t count = 0;

	while(1)
	{
		HAL_UART_Receive(&huart2, &data_rcv, 1, HAL_MAX_DELAY);

		if(data_rcv == '\r')
		{
			 break;
		}
		else
		{
			data_buffer[count++] = convert_to_capital(data_rcv);

		}
	}
	data_buffer[count++] = '\r';
	HAL_UART_Transmit(&huart2, data_buffer, count, HAL_MAX_DELAY);

	return 0 ;
}

void SystemClockConfig(void)
{

}

void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
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

uint8_t convert_to_capital(uint8_t data)
{
	if(data >= 'a' && data <= 'z' )
	{
		data = data - ('a' - 'A');
	}
	return data;
}

void Error_handler(void)
{
	while(1);
}








