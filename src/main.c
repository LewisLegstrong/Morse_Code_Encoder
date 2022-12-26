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

unsigned int startandsetup(void)
{
	io_config();
	usart_init(MYUBRR);
	sei();
	timer1_init(200); //colocar o dobro da frequencia pretendida
	//adc_init();

	strcat((char *)frase, "Hello World");

	return (1);
}

int main(void)
{
	unsigned int systemset = 0;

	systemset = startandsetup();
	if (!systemset)
		usart_transmit("UPS, SOMETHING FAILED");
	usart_transmit("ALL SYSTEMS OK");	
	
	while (1)
	{
		if (usartint_flg == 1)
			usart_receive();
		// PORTD &= ~(1<<PD6);
		// delay_t0(1);
		PORTD = (1<<PD6);
		delay_t0(4);
		usart_transmit(frase);
	}
	return (0);
}
