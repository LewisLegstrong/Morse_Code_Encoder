#ifndef TIMER_INIT_
#define TIMER_INIT_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "io_init.h"

#define MY_F_CPU 8000000L
#define PRESCALER0 1024
#define PRESCALER1 1
#define TI0_FREQ MY_F_CPU/PRESCALER0 // 15635Hz
#define TI0_PERIOD (1/TI0_FREQ) // 64us

extern volatile uint16_t period0; 

void timer0_reset();
void timer0_start();
void timer0_stop();

void timer1_init(unsigned int frequency);
void timer1_off(void); 
void delay_t0(uint16_t seconds);
void timer0_init(void);

#endif