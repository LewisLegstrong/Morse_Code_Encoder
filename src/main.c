#include <string.h>

#include "io_init.h"
#include "timer_init.h"
#include "usart_init.h"
#include "mod_mode.h"
#include "morse.h"

// volatile unsigned int freq = MIN_BUZ_FRQ;
volatile unsigned int freq = 2000;
volatile float spb = 0.2;

void startandsetup(void)
{
	io_config();
	usart_init(BAUD);
	UART0_FLUSH();
	adc_init();
	usart_transmit("Inicio com sucesso");
}

int main(void)
{
	char temp[6];
	memset(temp, 0, sizeof(temp));

	startandsetup();
	strcat((char *)frase, "Hello World\n");
	sei();

	while (1)
	{
		if (rx_flag)
		{
			mode_change();
			usart_transmit(frase);
		}	
		else
		{
			input_selection('T');
			delay_t0(10);
		}
	}
	return (0);
}
