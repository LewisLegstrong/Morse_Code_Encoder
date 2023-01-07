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
		if (*aux == '$')
		{
			//changes Input method
			if (!(strncmp(aux, inp_m, 10))) //INPUT change to MESSAGE
			{
				aux += 10; //walks up ten positions to start from the beggining of the string to be converted
				morse_convert(aux);
				break;
			}
			else if (!(strncmp(aux, inp_t, 10)))
			{
				itoa(temp);
				/*Trabalha com a ADC, to be verified
				It will spit out the temperature read from sensor fom x to x time*/
			}
			//changes output between LED and Buzzer
			else if (!(strncmp(aux, out_l, 10))) 
				out_sel = 'L';
			else if (!(strncmp(aux, out_b, 10)))
				out_sel = 'B';
			else if (!(strncmp(aux, inc_f, 10)))
			{
				freq += FREQ_INC;
				if (freq > MAX_BUZ_FRQ)
					freq = MAX_BUZ_FRQ;
			}
			else if (!(strncmp(aux, dec_f, 10)))
			{
				freq -= FREQ_INC;
				if (freq < MIN_BUZ_FRQ)
					freq = MIN_BUZ_FRQ;
			}
			else if (!(strncmp(aux, inc_b, 10)))
			{
				freq += SPB_INC;
				if (freq > SPB_MAX)
					freq = SPB_MAX;
			}
			else if (!(strncmp(aux, dec_b, 10)))
			{
				spb -= SPB_INC;
				if (freq < SPB_MIN)
					freq = SPB_MIN;
			}
		}
	}
}
