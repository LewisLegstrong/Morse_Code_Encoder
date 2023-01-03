#include "io_init.h"
#include "usart_init.h"

void io_config(void) // Configure pins as output or input
{
	DDRB |= (1 << PB1); // Define pin Buzzer OUTPUT(PWM)
	DDRD |= (1 << PD6); // Define pin LED OUTPUT
	DDRC &= ~(1 << PC0); // Define NTC como INPUT
	DDRD &= ~(1 << PD2);
	EICRA |= (1 << ISC00) | (1 << ISC01) | (1 << ISC10) | (1 << ISC11);
	EIMSK |= (1 << INT0) | (1 << INT1);
}

void adc_init(void) // pg216 datasheet
{
	ADMUX |= (1 << REFS0) | (1 << REFS1);
	ADCSRB &= ~((1 << ADTS0) | (1 << ADTS1) | (1 << ADTS2)); //sets Auto trigger to free running mode
	ADCSRA |= (1 << ADSC) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	ADCSRA |= (1 << ADEN);	// ADEN enables the ADC;
}	

ISR(INT0_vect)
{
	freq += FREQ_INC;
	if (freq > MAX_BUZ_FRQ)
		freq = MAX_BUZ_FRQ;
	usart_transmit("INT0 +1000");
}

ISR(INT1_vect)
{
	freq -= FREQ_INC;
	if (freq < MIN_BUZ_FRQ)
		freq = MIN_BUZ_FRQ;
	usart_transmit("INT1 +1000");
}
