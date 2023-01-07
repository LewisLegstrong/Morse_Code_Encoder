#include "mod_mode.h"
#include "usart_init.h"
#include "morse.h"

/*******************************Terminal Modifiable funciotns************************************/
void mode_change(void)
{
	unsigned char *aux;
	aux = frase;
	while (*aux)
	{
		//changes Input method
		if (!(strncmp(aux, inp_m, 10))) //INPUT change to MESSAGE
			input_selection('M');
		else if (!(strcmp(aux, inp_t)))
			input_selection('T');

		/*	Changes output between LED and Buzzer */
		else if (!(strcmp(aux, out_l))) 
			out_sel = 'L';
		else if (!(strcmp(aux, out_b)))
			out_sel = 'B';

		/*	Changes frequency	*/	
		else if (!(strcmp(aux, inc_f)))
		{
			freq += FREQ_INC;
			if (freq > MAX_BUZ_FRQ)
				freq = MAX_BUZ_FRQ;
		}
		else if (!(strcmp(aux, dec_f)))
		{
			freq -= FREQ_INC;
			if (freq < MIN_BUZ_FRQ)
				freq = MIN_BUZ_FRQ;
		}

		/*	Changes BPS (by changing the seconds per beat, it changes BPS)	*/	
		else if (!(strcmp(aux, inc_b)))
		{
			freq += SPB_INC;
			if (freq > SPB_MAX)
				freq = SPB_MAX;
		}
		else if (!(strcmp(aux, dec_b)))
		{
			spb -= SPB_INC;
			if (freq < SPB_MIN)
				freq = SPB_MIN;
		}
	}
}

void input_selection(char inp_sel)
{
	unsigned char *aux;

	aux = frase;
	switch (inp_sel)
	{
		case 'T':
			adc_read();
			//sends to selected Output 
			delay_t0(5);
			break;
	
		case 'M':
			aux += 10; //walks up ten positions to start from the beggining of the string to be converted
			morse_convert(aux);
			break;
	}
}