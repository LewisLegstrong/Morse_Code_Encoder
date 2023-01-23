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
#define FREQ_INC 200 //increases by 100Hz the PWM signal
/*Defines for BPS*/
#define BPS_MAX 200 //The lowest milisecond value will translate into the maximum amount of beats per second
#define BPS_MIN 1000 //The highest milisecond value will translate into the minimum amount of beats per second
#define BPS_INC 50
/*Defines for ADC*/
#define BETA 3435
#define NOMINAL_TEMP 25 
#define NOMINAL_RES 10000L // NTC resistance value at 25ºC
#define Rref 98000L //Series resistance

extern volatile unsigned int freq;
extern volatile float bps; //the values stored will in ms per beat

void adc_init(void);
void io_config(void);
void adc_read(char *temp_read);

#endif