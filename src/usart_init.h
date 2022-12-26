#ifndef USART_INIT_
#define USART_INIT_

#include <avr/interrupt.h>
#include <avr/io.h>

#include "io_init.h"

volatile char frase[120] = {"Hello World"};

void usart_init(unsigned int ubrr);
void usart_transmit(char tx_buffer[120]);
void UART0_FLUSH(void);
void usart_receive (void);

#endif

/*Before doing a re-initialization with changed baud rate or frame format, be sure that there are no ongoing transmissions
during the period the registers are changed. The TXCn flag can be used to check that the transmitter has completed all
transfers, and the RXC flag can be used to check that there are no unread data in the receive buffer. Note that the TXCn flag
must be cleared before each transmission (before UDRn is written) if it is used for this purpose. */