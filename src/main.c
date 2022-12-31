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
	timer1_init(200); //colocar o dobro da frequencia pretendida
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
		usart_transmit(frase);
	}
	return (0);
}
