#ifndef USART_INIT_
#define USART_INIT_

#define BAUD 115200
#define MYUBRR (F_CPU / (16 * BAUD))

#include <avr/interrupt.h>
#include <avr/io.h>

#include "io_init.h"

volatile char frase[120];
extern volatile unsigned long long rxCounter;
extern volatile unsigned int rx_flag;

/***************************************************************************************
//     //		//         Constant Variables for comaprison	    // 	    //		//
***************************************************************************************/
extern const char inp_m[10];
extern const char inp_t[10];
extern const char out_l[10];
extern const char out_b[10];
extern const char inc_f[10];
extern const char inc_b[10];
extern const char dec_f[10];
extern const char dec_b[10];

void usart_init(unsigned int ubrr);
void usart_transmit(volatile char tx_buffer[120]);
void UART0_FLUSH(void);
void usart_receive(void);
unsigned char usart_get_char(void);

#endif
