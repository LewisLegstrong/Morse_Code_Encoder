#include <string.h>

#include "io_init.h"
#include "timer_init.h"
#include "usart_init.h"
#include "mode_mod.h"
#include "morse.h"

// volatile unsigned int freq = MIN_BUZ_FRQ;
volatile unsigned int freq = 2000;
volatile float spb = 200;

void startandsetup(void)
{
	io_config();
	usart_init(BAUD);
	adc_init();
	timer0_init();
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
			delay_t0(1000);
		}	
		else
		{
			input_selection('T');
			delay_t0(10000);
		}
	}
	return (0);
}
