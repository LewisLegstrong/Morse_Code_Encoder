#include <avr/io.h>
#include "io_init.h"

#define PRESCALER 64

void timer1_init(volatile unsigned int frequency) //Não acabado, falta configurar alguns registos e perceber a 100% 
{
    int ticks;
    ticks = (F_CPU/PRESCALER)/frequency;

    TCCR1A |= (1<<COM1A0) | (1<<WGM11) | (1<<WGM10);
    TCCR1B |= (1<<WGM12) | (1<<WGM13);
    
    OCR1AH = ticks >> 8;
    OCR1AL |= ticks;
    
    //Needs to be set last, as setting the prescaler initializes the TCNT1 counter
    TCCR1B |= (1<<CS11) | (1<<CS10);
}
