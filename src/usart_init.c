#include "usart_init.h"

volatile unsigned long long rxCounter = 0;
/// ********************* Inicia a USART em 8bit data, 1 stop bit, Assyncronous ***************************///
void usart_init (unsigned int ubrr)
{	
	UBRR0H = (ubrr >> 8); /*  */
	UBRR0L = (ubrr);

	UCSR0B |= (1 << RXCIE0)  | (1 << RXEN0) | (1 << TXEN0); // Enable RX and TX, Enable Interrupts for RX and TX
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

// ********************* Passa para UDR0 cada carater da string por ordem para imprimir ***************************///
void usart_transmit (volatile char tx_buffer[120])
{
	rxCounter = 0;
	unsigned char i = 0;

	while (tx_buffer[i] != '\0' && i < 50)
	{
		while (!(UCSR0A & (1 << UDRE0))); /* Wait for empty transmit buffer */	
		UDR0 = tx_buffer[i];
		i++;
	}
}

//**************** Limpeza do buffer *************//
void UART0_FLUSH (void)
{
    unsigned char dummy = 0;
    while (UCSR0A & (1 << RXC0))
        dummy = UDR0;
}

/// ********************* Recebe cada carater da UDR0 e coloca na string ***************************///
unsigned char usart_get_char(void)
{
	while (!(UCSR0A & (1<<RXC0)));
	return (UDR0);
}

void usart_receive (void)
{
	volatile unsigned char c;

	c = usart_get_char();
	UART0_FLUSH();
	if (c == '\n' || c == '\r')
		c = '\0';
	frase[rxCounter] = c;
	rxCounter++;
}

//*********** Interrupção por receção da USART ***************//
ISR (USART_RX_vect)
{
	usart_receive();
}