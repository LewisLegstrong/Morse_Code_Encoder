#ifndef USART_INIT_
#define USART_INIT_

#define BAUD 8 //At 8MHz internal Clock, for a BAUD rate of 115200, single speed operation doesn't work, sending trash a ue to an 8,5% error
				//By setting assynchronous operation at double speed, we can have an error 3,5% allowing us to set Serial Port to 115200 as requested 

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
