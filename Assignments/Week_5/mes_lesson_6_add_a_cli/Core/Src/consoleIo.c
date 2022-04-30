// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include <stdio.h>
#include "stm32wbxx_hal.h"

extern UART_HandleTypeDef huart1;
char readBuf[1];
__IO ITStatus UartReady = SET;

static int getch_noblock() {
	int retVal = EOF;

	if (UartReady == SET) {
		UartReady = RESET;
		HAL_UART_Receive_IT(&huart1, (uint8_t*)readBuf, 1);
		HAL_UART_Transmit_IT(&huart1, (uint8_t*)readBuf, 1); // echo
		retVal = *readBuf;
	}
	return retVal;

}

eConsoleError ConsoleIoInit(void)
{
	/* Enable USART1 interrupt*/
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);

	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoReceive(uint8_t *buffer, const uint32_t bufferLength, uint32_t *readLength)
{
	uint32_t i = 0;
	int ch;
	
	ch = getch_noblock();
	while ( ( EOF != ch ) && ( i < bufferLength ) )
	{
		buffer[i] = (uint8_t) ch;
		i++;
		ch = getch_noblock();
	}
	*readLength = i;
	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
	printf("%s", buffer);
	return CONSOLE_SUCCESS;
}

void USART1_IRQHandler(void) {
  HAL_UART_IRQHandler(&huart1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) {
 /* Set transmission flag: transfer complete*/
 UartReady = SET;
}

