#include <avr/io.h>
#include "io_init.h"

// #define MIN_BUZ_FRQ
// #define MAX_BUZ_FRQ

void io_config(void) // Configure pins as output or input
{
	DDRB |= (1 << PB1); // Define pin Buzzer OUTPUT(PWM)
	DDRD |= (1 << PD6); // Define pin LED OUTPUT
	DDRC &= (1 << PC0); // Define NTC como INPUT

	DDRD |= (1 << PD1);
	DDRD &= (1 << PD0);
}

void adc_init(void) // pg216 datasheet
{
	ADMUX |= (1 << REFS0) | (1 << REFS1);
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

	ADCSRB &= (1 << ADTS0) | (1 << ADTS1) | (1 << ADTS2);
	// ADEN enables the ADC;
	// ADSC necessary to start the conversion, resets to zero auto when a conversion is concluded;
	// ADATE activates trigger mode instead of Single conversion mode
	// ADIE conversion interrupt enabler
	// ADPS:2 Prescaler selections
}

