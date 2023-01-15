// #include <avr/interrupt.h>
// #include <avr/io.h>
// #include <util/delay.h>
#include <string.h>

#include "io_init.h"
#include "timer_init.h"
#include "usart_init.h"
#include "mod_mode.h"

volatile unsigned int freq = MIN_BUZ_FRQ;
volatile float spb = SPB_MIN;

void startandsetup(void)
{
	io_config();
	usart_init(BAUD);
	UART0_FLUSH();
	adc_init();
	usart_transmit("Inicio com sucesso");
	delay_t0(2);

}

int main(void)
{
	char temp[6];
	memset(temp, 0, sizeof(temp));

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
			adc_read(temp);
			usart_transmit(temp);			
			rx_flag = 0;
		}
		else
			usart_transmit("funciona\n");

		delay_t0(2);
		timer1_off();
		delay_t0(2);
	}
	return (0);
}
