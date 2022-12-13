#include <avr/interrupt.h>
#include "io_init.h"


/// ********************* Inicia a USART em 8bit data, 1 stop bit, Assyncronous ***************************///
void usart_init (unsigned int ubrr)
{	
	UBRR0H = (unsigned char)(ubrr >> 8); /*  */
	UBRR0L = (unsigned char)(ubrr);

	UCSR0A &= (1 << UPE0);
	UCSR0B = (1 << RXCIE0) | (1 << TXCIE0) | (1 << RXEN0) | (1 << TXEN0); // Enable RX and TX, Enable Interrupts for RX and TX
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

/// ********************* Passa para UDR0 cada carater da string por ordem para imprimir ***************************///
void usart_transmit (unsigned char *tx_buffer)
{
	unsigned char *aux;

	aux = tx_buffer;
	while (*aux != '\0')
	{
		UDR0 = *aux;
		while (!(UCSR0A & (1 << UDRE0))); /* Wait for empty transmit buffer */	
		aux++;
	}
}

//**************** Limpeza do buffer *************//
void UART0_FLUSH (void)
{
    unsigned char dummy = 0;
    while (UCSR0A & RXC0)
        dummy = UDR0;
}


/// ********************* Recebe cada carater da UDR0 e coloca na string ***************************///
void usart_receive (void)
{
	unsigned char *rx_buffer;
	
	while (rx_buffer != '\n' || rx_buffer != '\r' )
	{
		rx_buffer = UDR0;
		while(!(UCSR0A & (1<<RXC0)));
	}
	rx_buffer = '\0';
	UART0_FLUSH();
}

//*********** Interrupção por receção da USART ***************//
ISR(USART_RX_vect)
{
	usart_receive();
}