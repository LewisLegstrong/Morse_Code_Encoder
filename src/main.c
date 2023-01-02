#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "io_init.h"
#include "timer_init.h"
#include "usart_init.h"

#define F_CPU 16000000UL
#define BAUD 115200
#define MYUBRR (F_CPU / (16 * BAUD))

void startandsetup(void)
{
	io_config();
	usart_init(MYUBRR);
	freq = MIN_BUZ_FRQ;
	timer1_init(2 * freq); //colocar o dobro da frequencia pretendida
	adc_init();
	UART0_FLUSH();
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
