#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "io_init.h"
#include "usart_init.h"
#include "timer_init.h"

#define F_CPU 16000000UL
#define BAUD 115200
#define MYUBRR (F_CPU / (16 * BAUD))

unsigned char frase[] = {"Hello World!\n"};

unsigned int startandsetup(void)
{
	io_config();
	usart_init(MYUBRR);
	timer1_init(200); //colocar o dobro da frequencia pretendida
	adc_init();

	return (1);
}

int main(void)
{
	unsigned int systemset = 0;

	systemset = startandsetup();
	if (!systemset)
		usart_transmit("UPS, SOMETHING FAILED");
	usart_transmit("ALL SYSTEMS OK");	
	sei();
	while (1)
	{
		PORTD &= ~(1<<PD6);
		delay_t0(1);
		PORTD = (1<<PD6);
		delay_t0(4);
		usart_transmit();
	}
	return (0);
}
