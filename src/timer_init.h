#ifndef TIMER_INIT_
#define TIMER_INIT_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "io_init.h"

#define PRESCALER0 1024
#define PRESCALER1 64
#define TI0_FREQ F_CPU/PRESCALER0 // 15635Hz
#define TI0_PERIOD (1/TI0_FREQ) // 64us

volatile unsigned int period0; 

void timer1_init(unsigned int frequency);
void timer1_off(void); 
void delay_t0(float seconds);
void timer0_init(void);

#endif