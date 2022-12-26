#include "usart_init.h"

/// ********************* Inicia a USART em 8bit data, 1 stop bit, Assyncronous ***************************///
void usart_init (unsigned int ubrr)
{	
	UBRR0H = (unsigned char)(ubrr >> 8); /*  */
	UBRR0L = (unsigned char)(ubrr);

	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	UCSR0B |= (1 << RXCIE0)  | (1 << RXEN0) | (1 << TXEN0); // Enable RX and TX, Enable Interrupts for RX and TX
}

/// ********************* Passa para UDR0 cada carater da string por ordem para imprimir ***************************///
void usart_transmit (unsigned char tx_buffer[50])
{
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
char *usart_receive (void)
{
	unsigned char aux;
	unsigned char rx_buffer[120];
	unsigned int i;

	i = 0;
	while (i < 120)
	{
		while(!(UCSR0A & (1<<RXC0)));
		aux = UDR0;
		if (aux == '\n' || aux == '\r')
			break ;
		else
			rx_buffer[i] = aux;
		i++;
	}
	*rx_buffer = '\0';
	UART0_FLUSH();
	return (rx_buffer);
}

//*********** Interrupção por receção da USART ***************//
ISR(USART_RX_vect)
{
	reception = 1; //Ter uma forma de receber uma variável para ser modificada na Receive quando a interrupt é ativa
	frase = usart_receive(); //A variável aqui alterada é diferente da que é usada em USart_transmit

	/* Usart transmit passa apenas a mensagem em Morse, A USart receive recebe comandos que vão ser interpretados para alterar valores ou alterar modos de funcionamnento*/
}