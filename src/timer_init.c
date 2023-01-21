#include "timer_init.h"
#include "morse.h"

void timer1_init(unsigned int frequency) // Não acabado, falta configurar alguns registos e perceber a 100%
{
	int ticks;
	ticks = (MY_F_CPU / PRESCALER1) / frequency;

//Kinda Working, requires further testing
//Fast PWM with ICR1 set as TOP
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12); 

	// Set the frequency of the PWM
    ICR1 = ticks;

	if (out_sel == 'L') //PB1
	{
		TCCR1A |= (1 << COM1A1); //non inverting output mode for OC1A
		OCR1A = ICR1 / 2;
	}
	else if (out_sel == 'B') //PB2
	{
		TCCR1A |= (1 << COM1B1); //non inverting output mode for OC1B
		OCR1B = ICR1 / 2; 
	}

	TCCR1B |= (1 << CS10); 
}

void timer1_off(void)
{
	ICR1 = 0;
	OCR1A = 0;
	OCR1B = 0;
	TCCR1B &= ~(1 << CS10); //Turns OFF Timer, shutting the LED/Buzzer OFF
}


/***************************************************************************************
//     //		//           Timer 0 is set for delays only         // 	    //		//

***************************************************************************************/

void timer0_init(void)
{
	TCCR0B &= ~(1 << WGM02);
	TIMSK0 |= (1 << TOIE0);
	TCCR0B |= ((1 << CS02) | (1<< CS00)); //Prescaler a 1024
}

void delay_t0(float seconds)
{
	float delay_val = 0;

	delay_val = seconds * TI0_FREQ;
	period0 = delay_val / 255;

	timer0_init();
	sei();
	if (!period0);
		TCCR0B &= ~((1 << CS02) | (1<< CS00)); //desliga o Timer
	cli();
}

ISR (TIMER0_OVF_vect)
{
	period0--;	
}
