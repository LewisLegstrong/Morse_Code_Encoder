#include <string.h>

#include "io_init.h"
#include "timer_init.h"
#include "usart_init.h"
#include "mode_mod.h"
#include "morse.h"

// volatile unsigned int freq = MIN_BUZ_FRQ;
volatile unsigned int freq = MIN_BUZ_FRQ;
volatile float bps = BPS_MAX;

void startandsetup(void) //Initializes all that's required
{
	io_config(); //Setup of GPIO
	usart_init(BAUD); //Setup of USART
	adc_init(); //Setup for ADC
	timer0_init();	//Setup for delay
	usart_transmit("Inicio com sucesso\n");
}

int main(void)
{
	float curr_bps = bps; //stores the bps value due to LED way of working(Check LED Output for further info)
	startandsetup();
	sei();

	while (1)
	{
		if (out_sel == 'L' && bps < 500)
		{		
			curr_bps = bps; 
			bps = 500;
		}
		else if (out_sel == 'B')
			bps = curr_bps;
		if (rx_flag)
		{
			mode_change();
			delay_t0(1000);
		}	
		else
		{
			input_selection('T');
			delay_t0(5000);
		}
	}
	return (0);
}
