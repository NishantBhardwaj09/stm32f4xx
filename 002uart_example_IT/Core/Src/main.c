#include "stm32f4xx_hal.h"
#include "main.h"
#include "string.h"

#define TRUE  1
#define FALSE 0

void SystemClockConfig(void);
void UART2_Init(void);
void Error_handler(void);
uint8_t convert_to_capital(uint8_t data);


char* data = "Hi, I am Nishant\r\n";
uint8_t data_buff[100];
uint8_t rcv_data;
uint32_t count = 0 ;
uint8_t rx_complete = FALSE ;

UART_HandleTypeDef huart2;

int main(void)
{
	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	while(rx_complete != TRUE)
	{
		HAL_UART_Receive_IT(&huart2, &rcv_data, 1);
	}
	return 0 ;
}

void SystemClockConfig(void)
{

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

uint8_t convert_to_capital(uint8_t data)
{
	if(data >= 'a' && data <= 'z' )
	{
		data = data - ('a' - 'A');
	}
	return data;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(rcv_data == '\r')
	{
		rx_complete = TRUE;
		data_buff[count++] = '\r';
		HAL_UART_Transmit(&huart2, data_buff, count, HAL_MAX_DELAY);
	}
	else
	{
		data_buff[count++] = rcv_data;
	}
}

void Error_handler(void)
{

}








