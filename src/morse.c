#include "morse.h"

void morse_dot(void)
{
	timer1_init(200/*requires frequency value to enter here //volatile int freq*/);
	delay_t0(2); /*To be Determined the time in s*/
	timer1_off();
}

void morse_dash(void)
{
	timer1_init(200/*requires frequency value to enter here //volatile int freq*/);
	delay_t0(2); /*To be Determined the time in s*/
	timer1_off();
}

void morse_space(void)
{
	timer1_init(200/*requires frequency value to enter here //volatile int freq*/);
	delay_t0(2); /*To be Determined the time in s*/
	timer1_off();
}