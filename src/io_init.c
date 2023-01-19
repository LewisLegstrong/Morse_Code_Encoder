#include "io_init.h"
#include <stdio.h>

void io_config(void) // Configure pins as output or input
{
	DDRB |= (1 << PB1); // Define pin LED OUTPUT(PWM)
	DDRD |= (1 << PB2); // Define pin BUZZER OUTPUT
	DDRC &= ~(1 << PC0); // Define NTC como INPUT
	DDRD &= ~(1 << PD2);
	EICRA |= (1 << ISC00) | (1 << ISC01) | (1 << ISC10) | (1 << ISC11);
	EIMSK |= (1 << INT0) | (1 << INT1);
}

void adc_init(void) // pg216 datasheet
{
	ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0)); //Sets the pin to read as ADC0
	ADMUX |= (1 << REFS1) | (1 << REFS0); //Sets internal reference Voltage to 1.1V
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

}

void adc_read(char *tempe)
{
	uint16_t ADC_10bit = 0;
	ADCSRA |= (1 << ADSC); // ADEN enables the ADC; ADSC - Start Conversion
	
	while(!(ADCSRA & (1<<ADIF)));
	ADC_10bit = ADC;

	//voltagem no NTC
	float volt_ntc = (ADC_10bit * 1.1) / 1023;
	
	// Resistencia de NTC
	float rNTC = (Rref * volt_ntc) / (5 - volt_ntc);
	/*	TESTING	*/
	char resNTC[20];
	itoa(rNTC, resNTC, 10);
	usart_transmit(resNTC);
	usart_transmit("\n");

	// Determinar temperatura (Formula de Steinhart-Hart)
	float temperature;
  	temperature = rNTC / NOMINAL_RES;     // (R/Ro)
  	temperature = log(temperature);                  // ln(R/Ro)
  	temperature /= BETA;                   // 1/B * ln(R/Ro)
  	temperature += 1.0 / (NOMINAL_TEMP + 273.15); // + (1/To)
  	temperature = 1.0 / temperature;                 // Invert
 	temperature -= 273.15;                         // convert absolute temp to C

/* Determine temperature (Steinhart-Hart equation) */
	// float lnR_Ro = log(rNTC / R_NTC_NOMINAL);
	// float temp_Kelvin = 1 / (BETA + (1 / (25 + 273.15)) + lnR_Ro);
	// int temperature = (int)temp_Kelvin - 273.15;

/*	Testing	*/
	itoa(temperature, tempe, 10);
	usart_transmit(tempe);
}

/***********************************************************************************
 * 										Interrupts
************************************************************************************/

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
