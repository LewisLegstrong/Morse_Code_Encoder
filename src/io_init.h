#ifndef INIT_IO_
#define INIT_IO_

#include <avr/io.h>
#include <avr/interrupt.h>

/*Defines for Frequency*/
#define MIN_BUZ_FRQ 50 //defines min freq at 20Hz
#define MAX_BUZ_FRQ 20000 //defines max freq at 20kHz
#define FREQ_INC 665 //increases by 100Hz the PWM signal
/*Defines for BPS*/
#define SPB_MAX 1000
#define SPB_MIN 200
#define SPB_INC 200
/*Defines for ADC*/
#define BETA 3435
#define R_NTC_NOMINAL 10000 // a 25ºC

extern volatile unsigned int freq;
extern volatile float spb;

void adc_init(void);
void io_config(void);
unsigned int adc_read(unsigned int ch);

#endif