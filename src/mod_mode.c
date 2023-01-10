#include "mod_mode.h"

const char inp_m[10] = "$INP:MSG:";
const char inp_t[10] = "$INP:TMP$";
const char out_l[10] = "$OUT:LED$";
const char out_b[10] = "$OUT:BUZ$";
const char inc_f[10] = "$INC:FRQ$";
const char inc_b[10] = "$INC:BPS$";
const char dec_f[10] = "$DEC:FRQ$";
const char dec_b[10] = "$DEC:BPS$";

/*******************************Terminal Modifiable funciotns************************************/
void mode_change(void)
{
	char *aux;
	aux = (char*)frase;
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
	int temp = 0;

	aux = (unsigned char*)frase;
	switch (inp_sel)
	{
		case 'T':
			temp = adc_read(PC0);
			timer1_init(freq);
			timer1_off();
			usart_transmit(temp);
			delay_t0(5);
			break;
	
		case 'M':
			aux += 10; //walks up ten positions to start from the beggining of the string to be converted
			morse_convert(aux);
			inp_sel = 'T';
			rx_flag = 0;
			break;
	}
}