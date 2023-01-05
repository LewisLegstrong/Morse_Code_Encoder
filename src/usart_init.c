#include "usart_init.h"

volatile unsigned long long rxCounter = 0;

void usart_init (unsigned int ubrr) // Inicia a USART em 8bit data, 1 stop bit, Assyncronous
{	
	UBRR0H = (ubrr >> 8); /*  */
	UBRR0L = (ubrr);

	UCSR0B |= (1 << RXCIE0)  | (1 << RXEN0) | (1 << TXEN0); // Enable RX and TX, Enable Interrupts for RX and TX
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

/***************************************************************************************
//     //		//          	 USART Transmit					    // 	    //		//

***************************************************************************************/

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

/***************************************************************************************
//     //		//          	 USART Receive					    // 	    //		//

***************************************************************************************/

void UART0_FLUSH (void)	//Limpeza do buffer 
{
    unsigned char dummy = 0;
    while (UCSR0A & (1 << RXC0))
        dummy = UDR0;
}

unsigned char usart_get_char(void)	//Recebe cada carater da UDR0 e coloca na string 
{
	while (!(UCSR0A & (1<<RXC0)));
	return (UDR0);
}

void usart_receive(void)	//Recebe cada carater da UDR0 e coloca na string 
{
	volatile unsigned char c;

	c = usart_get_char();
	UART0_FLUSH();
	if (c == '\n' || c == '\r')
		c = '\0';
	frase[rxCounter] = c;
	rxCounter++;
}

/***************************************************************************************
//     //		//          	 USART Receive Interrupt		    // 	    //		//

***************************************************************************************/

ISR (USART_RX_vect)	//Interrupção por receção da USART
{
	usart_receive();
}
