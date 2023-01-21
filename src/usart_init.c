#include "usart_init.h"

volatile unsigned long long rxCounter = 0;
volatile unsigned int rx_flag = 0;

void usart_init (unsigned int ubrr) // Inicia a USART em 8bit data, 1 stop bit, Assyncronous
{	
	UBRR0H = ((unsigned char)ubrr >> 8); /*  */
	UBRR0L = ((unsigned char)ubrr);

	UCSR0A |= (1 << U2X0); //activates double speed transfer rates to minimize error at 115200 Baud Rate
	UCSR0B |= (1 << RXCIE0)  | (1 << RXEN0) | (1 << TXEN0); // Enable RX and TX, Enable Interrupts for RX and TX
}

/***************************************************************************************
//     //		//          	 USART Transmit					    // 	    //		//

***************************************************************************************/

void usart_transmit (volatile char tx_buffer[120])
{
	unsigned char i = 0;

	rxCounter = 0;
	while ((tx_buffer[i] != '\0') && i < 50)
	{
		while (!(UCSR0A & (1 << UDRE0))); /* Wait for empty transmit buffer */	
		UDR0 = tx_buffer[i++];
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

void usart_receive(void)	//Recebe cada carater da UDR0 e coloca na string 
{
	volatile unsigned char c;
	while (!(UCSR0A & (1<<RXC0)));
	c = UDR0;
	if (c >= 0 && c < 32)
	{	
		c = '\0';
		frase[rxCounter] = c;
		rx_flag = 1;
		return;
	}
	frase[rxCounter] = c;
	//UART0_FLUSH();
	rxCounter++;
}

/***************************************************************************************
//     //		//          	 USART Receive Interrupt		    // 	    //		//

***************************************************************************************/

ISR (USART_RX_vect)	//Interrupção por receção da USART
{
	usart_receive();
}
