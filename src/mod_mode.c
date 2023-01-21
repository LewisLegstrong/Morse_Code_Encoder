#include "mod_mode.h"

const char inp_m[120] = "<INP:MSG:"; //change input to Message
const char inp_t[10] = "<INP:TMP>"; //Change input to Temperature
const char out_l[10] = "<OUT:LED>";	//Change Output to LED	
const char out_b[10] = "<OUT:BUZ>";	//Change Output to Buzzer
const char inc_f[10] = "<INC:FRQ>"; //Increment frequency Values
const char inc_b[10] = "<INC:BPS>";	//Increment Beats per Second values
const char dec_f[10] = "<DEC:FRQ>"; //Decrement frequency values
const char dec_b[10] = "<DEC:BPS>";	//Decrement BEats per Second Values

/*******************************Terminal Modifiable funciotns************************************/
void mode_change(void)
{
//TESTES
	usart_transmit("entered function\n");

	int make_change = 0;
	while (!make_change)
	{
					//TESTE
			int result = (strncmp((char *)frase, inp_m, 9));
			char str[10];
			itoa(result, str, 10);
			usart_transmit(str);
			usart_transmit(frase);
			make_change = 1;

		//changes Input method
		if ((strncmp((char *)frase, inp_m, 10))) //INPUT change to MESSAGE
		{	
			input_selection('M');
			make_change = 1;
			rx_flag = 0;
		}
		else if (!(strcmp((char *)frase, inp_t)))
		{
			input_selection('T');
			make_change = 1;
			rx_flag = 0;
		}
		/*	
		Changes output between LED and Buzzer 
		*/
		else if (!(strcmp((char *)frase, out_l)))
		{
			out_sel = 'L';
			usart_transmit("Output is now LED\n");
			make_change = 1;
			rx_flag = 0;
		}
		else if (!(strcmp((char *)frase, out_b)))
		{
			out_sel = 'B';
			usart_transmit("Output is now LED\n");
			make_change = 1;
			rx_flag = 0;
		}
		/*	
		Changes frequency	
		*/	
		else if (!(strcmp((char *)frase, inc_f)))
		{
			freq += FREQ_INC;
			if (freq > MAX_BUZ_FRQ)
				freq = MAX_BUZ_FRQ;
			usart_transmit("Increased FREQUENCY\nIt is now: ");
			make_change = 1;
			rx_flag = 0;
		}
		else if (!(strcmp((char *)frase, dec_f)))
		{
			freq -= FREQ_INC;
			if (freq < MIN_BUZ_FRQ)
				freq = MIN_BUZ_FRQ;
			usart_transmit("Decreased FREQUENCY\nIt is now: ");
			make_change = 1;
			rx_flag = 0;
		}

		/*	
		Changes BPS (by changing the seconds per beat, it changes BPS)	
		*/	
		else if (!(strcmp((char *)frase, inc_b)))
		{
			spb += SPB_INC;
			if (spb > SPB_MAX)
				spb = SPB_MAX;
			usart_transmit("Increased BPS\nIt is now: ");
			make_change = 1;
			rx_flag = 0;
		}
		else if (!(strcmp((char *)frase, dec_b)))
		{
			spb -= SPB_INC;
			if (spb < SPB_MIN)
				spb = SPB_MIN;
			usart_transmit("Decreased BPS\nIt is now: ");
			make_change = 1;
			rx_flag = 0;
		}

		else
		{
			usart_transmit("Invalid Input, please refer to manual\n");
			make_change = 1;
			rx_flag = 0;
		}
	}
}

void input_selection(char inp_sel)
{
	char *aux;
	char temp[6];

	switch (inp_sel)
	{
		case 'T':
			adc_read(temp);
			timer1_init(freq);
			timer1_off();
			break;
	
		case 'M':
			aux = (char *)frase + 10; //walks up ten positions to start from the beggining of the string to be converted
			morse_convert(aux);
			inp_sel = 'T';
			rx_flag = 0;
			break;
	}
}