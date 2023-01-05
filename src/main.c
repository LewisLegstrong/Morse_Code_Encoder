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

const char inp_m[10] = "$INP:MSG$";
const char inp_t[10] = "$INP:TMP$";
const char out_l[10] = "$OUT:LED$";
const char out_b[10] = "$OUT:BUZ$";
const char inc_f[10] = "$INC:FRQ$";
const char inc_b[10] = "$INC:BPS$";
const char dec_f[10] = "$DEC:FRQ$";
const char dec_b[10] = "$DEC:BPS$";

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
