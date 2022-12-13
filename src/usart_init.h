#ifndef USART_INIT_
#define USART_INIT_

void usart_init(unsigned int ubrr);
void usart_transmit(unsigned char *tx_buffer);
void UART0_FLUSH(void);
void usart_receive (void);

#endif