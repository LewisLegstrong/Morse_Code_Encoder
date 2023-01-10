// #include <avr/interrupt.h>
// #include <avr/io.h>
// #include <util/delay.h>
#include <string.h>

#include "io_init.h"
#include "timer_init.h"
#include "usart_init.h"
#include "morse.h"
#include "mod_mode.h"
#include "auxiliary.h"

volatile unsigned int freq = MIN_BUZ_FRQ;
volatile float spb = SPB_MIN;

void startandsetup(void)
{
	io_config();
	usart_init(BAUD);
	adc_init();
	UART0_FLUSH();
	usart_transmit("Inicio com sucesso");
	delay_t0(2);
}

int main(void)
{
	 int temp = 0;
	 char *temperatura;

	startandsetup();
	sei();

	while (1)
	{
		// delay_t0(2);
		// temp = adc_read(PC0);
		// temperatura = ft_itoa(temp);
		timer1_init(freq);

		if (rx_flag == 1)
		{
			usart_transmit("A ler temp");
			temp = adc_read(0b00000000);
			temperatura = ft_itoa(temp);
			usart_transmit(temperatura);
			
			rx_flag = 0;
		}
		else
			usart_transmit("funciona");
		delay_t0(2);
		timer1_off();
		delay_t0(2);
	}
	return (0);
}
