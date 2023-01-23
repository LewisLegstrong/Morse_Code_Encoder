#include "timer_init.h"
#include "morse.h"

volatile uint16_t period0 = 0; 

void timer1_init(unsigned int frequency) // Não acabado, falta configurar alguns registos e perceber a 100%
{
	int ticks;
	ticks = (MY_F_CPU / PRESCALER1) / frequency;

//Fast PWM with ICR1 set as TOP
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12); 

    ICR1 = ticks;	// Set the frequency of the PWM

	if (out_sel == 'L') //PB1 - LED
	{
		TCCR1A |= (1 << COM1A1); //non inverting output mode for OC1A
		OCR1A = ICR1 / 2; //Duty Cycle at 50%
	}
	else if (out_sel == 'B') //PB2 - Buzzer
	{
		TCCR1A |= (1 << COM1B1); //non inverting output mode for OC1B
		OCR1B = ICR1 / 2; //Duty Cycle at 50%
	}

	TCCR1B |= (1 << CS10); //initializes Timer at 64
}

void timer1_off(void) //Turns off PWM generation
{
	ICR1 = 0;
	OCR1A = 0;
	OCR1B = 0;
	TCCR1B &= ~(1 << CS10); //Turns OFF Timer, shutting the LED/Buzzer OFF
}


/***************************************************************************************
//     //		//           Timer 0 is set for delays only         // 	    //		//

***************************************************************************************/

void timer0_init(void) //Configures Mode and Compare value
{
	TCCR0A |= (1 << WGM01); //Modo CTC
	TIMSK0 |= (1 << OCIE0A); //Ativa a interrupt na compare
	// TCCR0B |= (1 << CS01) | (1 << CS00); //Prescaler a ~64
	TCNT0 = 0;
	OCR0A = 125; // define o timer de 1ms
}

//TESTE
void timer0_start(void) //initializes the timer 
{
	TCCR0B |= (1 << CS01) | (1 << CS00); //Prescaler a ~64
}

void timer0_reset(void) //resets the timer 
{
	timer0_stop();
	TCNT0 = 0;
	timer0_start();
}

void timer0_stop(void) //Stops the timer
{
	TCCR0B &= ~((1 << CS01) | (1 << CS00));
}

void delay_t0(uint16_t mil_secs)
{
	period0 = mil_secs;
	timer0_start();
	while(period0);
}

ISR (TIMER0_COMPA_vect)
{
	if(!period0)
		timer0_stop();
	else
	{
		period0--;
		timer0_reset();
	}
}
