#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <stdio.h>
#include "io_init.h"
#include "usart_init.h"
#include "timer_init.h"

#define F_CPU 16000000UL
#define BAUD 115200
#define MYUBRR (F_CPU / (16 * BAUD))

int main(void)
{
	unsigned char frase[] = {"Hello World!\n"};
	io_config();
	usart_init(MYUBRR);
	adc_init();
	timer1_init(200); //colocar o dobro da frequencia pretendida

	sei();

	while (1)
	{
		usart_transmit(frase);
	}
	return (0);
}
 