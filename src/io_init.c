#include "io_init.h"
#include "morse.h"

void io_config(void) // Configure pins as output or input
{
	DDRB |= (1 << PB1); // Define pin LED OUTPUT(PWM)
	DDRB |= (1 << PB2); // Define pin BUZZER OUTPUT
	DDRC &= ~(1 << PC0); // Define NTC como INPUT
	DDRD &= ~(1 << PD2);
	EICRA |= (1 << ISC00) | (1 << ISC01) | (1 << ISC10) | (1 << ISC11); //Sets both EINT to activate on the rising edge
	EIMSK |= (1 << INT0) | (1 << INT1); //enables external interrupts
}

void adc_init(void) // pg216 datasheet
{
	ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0)); //Sets the pin to read as ADC0
	ADMUX |= (1 << REFS1) | (1 << REFS0); //Sets internal reference Voltage to 1.1V
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

}

void adc_read(char *temp_read)
{
	uint16_t ADC_10bit = 0;
	ADCSRA |= (1 << ADEN) | (1 << ADSC); // ADEN enables the ADC; ADSC - Start Conversion
	
	while(!(ADCSRA & (1<<ADIF))); //Waits for conversion to complete
	ADC_10bit = ADC; //Puts converted value in variable
	
	float volt_ntc = (ADC_10bit * 1.1) / 1023;//voltagem no NTC
	float rNTC = (Rref * volt_ntc) / (5 - volt_ntc);// Resistencia de NTC

	// Determinar temperatura (Formula de Steinhart-Hart)
	float temperature;
  	temperature = rNTC / NOMINAL_RES;     // (R/Ro)
  	temperature = log(temperature);                  // ln(R/Ro)
  	temperature /= BETA;                   // 1/B * ln(R/Ro)
  	temperature += 1.0 / (NOMINAL_TEMP + 273.15); // + (1/To)
  	temperature = 1.0 / temperature;                 // Invert
 	temperature -= 273.15;                         // convert absolute temp to C

	itoa(temperature, temp_read, 10);
	usart_transmit("Temperature is: ");
	usart_transmit(temp_read);
	usart_transmit("ºC");
	usart_transmit("\n");
	morse_convert(temp_read);

}

/***********************************************************************************
 * 										Interrupts
************************************************************************************/

ISR(INT0_vect)
{
	usart_transmit("Frequency Decreased\n");
	freq -= FREQ_INC;
	if (freq < MIN_BUZ_FRQ)
		freq = MIN_BUZ_FRQ;
}

ISR(INT1_vect)
{
	usart_transmit("Frequency Increased\n");
	freq += FREQ_INC;
	if (freq > MAX_BUZ_FRQ)
		freq = MAX_BUZ_FRQ;
}
