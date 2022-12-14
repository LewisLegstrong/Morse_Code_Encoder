#include "timer_init.h"
#include "morse.h"

void timer1_init(unsigned int frequency) // Não acabado, falta configurar alguns registos e perceber a 100%
{
	int ticks;
	ticks = (F_CPU / PRESCALER1) / frequency;

	TCCR1A |= (1 << COM1A0) | (1 << WGM11) | (1 << WGM10);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);

	if (out_sel == 'B')
	{
		OCR1AH = ticks >> 8;
		OCR1AL = ticks;
		timer1_on();
	}
	else if (out_sel == 'L')
	{
		OCR1BH = ticks >> 8;
		OCR1BL = ticks;
		timer1_on();
	}		
}

void timer1_on(void)
{
	TCCR1B |= (1 << CS11) | (1 << CS10); //Chooses Prescaler starting the Timer and generating PWM
}

void timer1_off(void)
{
	TCCR1B &= ~((1 << CS11) | (1 << CS10)); //Turns OFF Timer, shutting the LED/Buzzer OFF
}


/***************************************************************************************
//     //		//           Timer 0 is set for delays only         // 	    //		//

***************************************************************************************/

void timer0_init(void)
{
	// TCCR0A = 0x00;
	TCCR0B &= ~(1 << WGM02);

	TIMSK0 |= (1 << TOIE0);
	TCCR0B |= (1 << CS02) | (1 << CS00); //Prescaler a 1024
}

void delay_t0(float seconds)
{
	float delay_val = 0;

	delay_val = seconds * TI0_FREQ;
	period0 = delay_val / 255;
	timer0_init();
	sei();
	while (period0)	;
	TCCR0B &= ~((1 << CS02) | (1 << CS00));
	cli();
}

ISR (TIMER0_OVF_vect)
{
	period0--;	
}
