#include <avr/io.h>
#include <avr/interrupt.h>
#include "io_init.h"

#define PRESCALER0 1024
#define PRESCALER1 64
#define TI0_FREQ F_CPU/PRESCALER0 // 15635Hz
#define TI0_PERIOD (1/TI0_FREQ) // 64ms

volatile unsigned int period0;

void timer1_init(volatile unsigned int frequency) //Não acabado, falta configurar alguns registos e perceber a 100% 
{
    int ticks;
    ticks = (F_CPU/PRESCALER1)/frequency;

    TCCR1A |= (1<<COM1A0) | (1<<WGM11) | (1<<WGM10);
    TCCR1B |= (1<<WGM12) | (1<<WGM13);
    
    OCR1AH = ticks >> 8;
    OCR1AL |= ticks;
    
    //Needs to be set last, as setting the prescaler initializes the TCNT1 counter
    TCCR1B |= (1<<CS11) | (1<<CS10);
}

void timer0_init (void)
{
    TIMSK0 = (1 << TOIE0);
    TCCR0B = (1 << CS02) | (1 << CS00);
}

int delay_t0 (volatile unsigned int seconds)
{   
    unsigned int delay_val;

    delay_val = seconds/TI0_PERIOD;
    period0 = delay_val/255;
    timer0_init();
    while(period0);
    TCCR0B = 0x00;
}

ISR(TIMER0_OVF_vect)
{
    period0--;
}