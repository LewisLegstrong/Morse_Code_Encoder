#ifndef INIT_IO_
#define INIT_IO_

#include <avr/io.h>
#include <avr/interrupt.h>

#define MIN_BUZ_FRQ 50 //defines min freq at 20Hz
#define MAX_BUZ_FRQ 20000 //defines max freq at 20kHz
#define FREQ_INC 200 //increases by 100Hz the PWM signal

extern volatile unsigned int freq;
extern volatile unsigned int spb;

void adc_init(void);
void io_config(void);

#endif