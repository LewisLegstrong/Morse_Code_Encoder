#include "mod_mode.h"

const char inp_m[120] = "$INP:MSG:"; //change input to Message
const char inp_t[10] = "$INP:TMP$"; //Change input to Temperature
const char out_l[10] = "$OUT:LED$";	//Change Output to LED	
const char out_b[10] = "$OUT:BUZ$";	//Change Output to Buzzer
const char inc_f[10] = "$INC:FRQ$"; //Increment frequency Values
const char inc_b[10] = "$INC:BPS$";	//Increment Beats per Second values
const char dec_f[10] = "$DEC:FRQ$"; //Decrement frequency values
const char dec_b[10] = "$DEC:BPS$";	//Decrement BEats per Second Values

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

		/*	
		Changes output between LED and Buzzer 
		*/
		else if (!(strcmp(aux, out_l))) 
			out_sel = 'L';
		else if (!(strcmp(aux, out_b)))
			out_sel = 'B';

		/*	
		Changes frequency	
		*/	
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

		/*	
		Changes BPS (by changing the seconds per beat, it changes BPS)	
		*/	
		else if (!(strcmp(aux, inc_b)))
		{
			spb += SPB_INC;
			if (spb > SPB_MAX)
				spb = SPB_MAX;
		}
		else if (!(strcmp(aux, dec_b)))
		{
			spb -= SPB_INC;
			if (spb < SPB_MIN)
				spb = SPB_MIN;
		}
	}
}

void input_selection(char inp_sel)
{
	unsigned char *aux;
	char temp[6];

	aux = (unsigned char*)frase;
	switch (inp_sel)
	{
		case 'T':
			adc_read(temp);
			timer1_init(freq);
			timer1_off();
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