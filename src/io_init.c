#include "io_init.h"

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
	ADMUX |= (1 << REFS0) | (1 << REFS1); //Sets internal reference Voltage to 1.1V
	ADCSRA |= (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	
}

uint16_t adc_read(uint8_t adc_pin)
{
	adc_pin &= 0b00000111;			 // AND operation with 7
	ADMUX = (ADMUX & 0xF8) | adc_pin; // clears the bottom 3 bits before ORing

	ADCSRA |= (1 << ADSC); // ADEN enables the ADC; ADSC - Start Conversion

	while (!(ADCSRA & (1 << ADIF)));

	//voltagem no NTC
	float volt_ntc = 0.0;
	volt_ntc = ADC * (1.1 / 1023);

	// Resistencia de NTC
	float rNTC;
	rNTC = (100000 * volt_ntc) / (5 - volt_ntc);

	// Determinar temperatura (Formula de Steinhart-Hart)
	float temperature = 0.0;
	temperature = rNTC / R_NTC_NOMINAL;			   // (R/Ro)
	temperature = log(temperature);				   // ln(R/Ro)
	temperature /= BETA;						   // 1/B * ln(R/Ro)
	temperature += 1.0 / (R_NTC_NOMINAL + 273.15); // + (1/To)
	temperature = 1.0 / temperature;			   // Invert
	temperature -= 273.15;						   // convert absolute temp to C

	return (ADC);
}

ISR(INT0_vect)
{
	usart_transmit("Button 0");
	freq += FREQ_INC;
	if (freq > MAX_BUZ_FRQ)
		freq = MAX_BUZ_FRQ;
}

ISR(INT1_vect)
{
	usart_transmit("Button 1");
	freq -= FREQ_INC;
	if (freq < MIN_BUZ_FRQ)
		freq = MIN_BUZ_FRQ;
}
