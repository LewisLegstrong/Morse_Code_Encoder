#ifndef IO_INIT_H
#define IO_INIT_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdlib.h>

#include "usart_init.h"

/*Defines for Frequency*/
#define MIN_BUZ_FRQ 50 //defines min freq at 20Hz
#define MAX_BUZ_FRQ 20000 //defines max freq at 20kHz
#define FREQ_INC 665 //increases by 100Hz the PWM signal
/*Defines for BPS*/
#define SPB_MAX 1/(1000/60)
#define SPB_MIN 1/(200/60)
#define SPB_INC 1/(200/60)
/*Defines for ADC*/
#define BETA 3435
#define R_NTC_NOMINAL 10000L // a 25ºC

extern volatile unsigned int freq;
extern volatile float spb;

void adc_init(void);
void io_config(void);
void adc_read(char *temp);

#endif