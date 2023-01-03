// #include <avr/interrupt.h>
// #include <avr/io.h>
// #include <util/delay.h>
#include <string.h>

#include "io_init.h"
#include "timer_init.h"
#include "usart_init.h"
#include "morse.h"

#define F_CPU 16000000UL

volatile unsigned int freq = MIN_BUZ_FRQ;

void startandsetup(void)
{
	io_config();
	usart_init(MYUBRR);
	adc_init();
	UART0_FLUSH();
	strcat((char *)frase, "Sem frequencia");
}

int main(void)
{
	startandsetup();
	sei();
	
	while (1)
	{

	}
	return (0);
}
