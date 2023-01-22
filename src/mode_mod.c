#include "mode_mod.h"

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
		//changes Input method
		if (!(strncmp((char *)frase, inp_m, 9))) //INPUT change to MESSAGE
		{	
			input_selection('M');
			make_change = 1;
			rx_flag = 0;
		}
		else if (!(strncmp((char *)frase, inp_t, 10)))
		{
			input_selection('T');
			make_change = 1;
			rx_flag = 0;
		}
		/*	
		Changes output between LED and Buzzer 
		*/
		else if (!(strncmp((char *)frase, out_l, 10)))
		{
			out_sel = 'L';
			usart_transmit("Output is now LED\n");
			make_change = 1;
			rx_flag = 0;
		}
		else if (!(strncmp((char *)frase, out_b, 10)))
		{
			out_sel = 'B';
			usart_transmit("Output is now LED\n");
			make_change = 1;
			rx_flag = 0;
		}
		/*	
		Changes frequency	
		*/	
		else if (!(strncmp((char *)frase, inc_f, 10)))
		{
			freq += FREQ_INC;
			if (freq > MAX_BUZ_FRQ)
				freq = MAX_BUZ_FRQ;
			usart_transmit("Increased FREQUENCY\nIt is now: ");
			make_change = 1;
			rx_flag = 0;
		}
		else if (!(strncmp((char *)frase, dec_f, 10)))
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
		else if (!(strncmp((char *)frase, inc_b,10)))
		{
			spb += SPB_INC;
			if (spb > SPB_MAX)
				spb = SPB_MAX;
			usart_transmit("Increased BPS\nIt is now: ");
			make_change = 1;
			rx_flag = 0;
		}
		else if (!(strncmp((char *)frase, dec_b, 10)))
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
			aux = (char *)frase + 9; //walks up to the tenth position to start from the beggining of the string to be converted
			morse_convert(aux);
			delay_t0(2000);
			inp_sel = 'T';
			rx_flag = 0;
			break;
	}
}