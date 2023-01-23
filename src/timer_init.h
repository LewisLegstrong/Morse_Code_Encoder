#ifndef TIMER_INIT_
#define TIMER_INIT_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "io_init.h"

#define MY_F_CPU 8000000L
#define PRESCALER1 1

extern volatile uint16_t period0; 

void timer0_reset();
void timer0_start();
void timer0_stop();

void timer1_init(unsigned int frequency);
void timer1_off(void); 
void delay_t0(uint16_t mil_secs);
void timer0_init(void);

#endif