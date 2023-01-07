// #include <avr/interrupt.h>
// #include <avr/io.h>
// #include <util/delay.h>
#include <string.h>

#include "io_init.h"
#include "timer_init.h"
#include "usart_init.h"
#include "morse.h"

#define F_CPU 16000000UL

volatile unsigned int freq = 200;
volatile float spb = 0.2;

void startandsetup(void)
{
	io_config();
	usart_init(MYUBRR);
	adc_init();
	UART0_FLUSH();
}

int main(void)
{
	startandsetup();
	sei();
	
	while (1)
	{
		delay_t0(2);
		usart_transmit((char *)inc_b);
	}
	return (0);
}
