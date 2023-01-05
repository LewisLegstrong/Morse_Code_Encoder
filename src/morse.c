#include "morse.h"
#include "timer_init.h"
#include "usart_init.h"

// Defines Morse Caracters: Dot, Dash and also defines Space between words
void morse_dot(void)
{
	timer1_init(freq);
	delay_t0(spb);
	
	timer1_off();
	delay_t0(spb);
}

void morse_dash(void)
{
	timer1_init(freq);
	for (int i = 0; i < 3; i++) //3x the beat time 
		delay_t0(spb);
	
	timer1_off();
	delay_t0(spb);
}

void morse_space(void)
{
	for (int i = 0; i < 2; i++) //2x the baet time
		delay_t0(spb);
}

//Converts the phrase to morse Code to be sent to an LED or Buzzer
void morse_convert(void)
{
	int i = 0;
	while (frase[i] != '\0')
	{
		switch (frase[i++])
		{
			case 'a':
			case 'A':
				morse_dot();
				morse_dash();
				break;

			case 'b':
			case 'B':
				morse_dash();
				morse_dot();
				morse_dot();
				morse_dot();
				break;

			case 'c':
			case 'C':
				morse_dash();
				morse_dot();
				morse_dash();
				morse_dot();
				break;

			case 'd':
			case 'D':
				morse_dash();
				morse_dot();
				morse_dot();
				break;

			case 'e':
			case 'E':
				morse_dot();
				break;

			case 'f':
			case 'F':
				morse_dot();
				morse_dot();
				morse_dash();
				morse_dot();
				break;

			case 'g':
			case 'G':
				morse_dash();
				morse_dash();
				morse_dot();
				break;

			case 'h':
			case 'H':
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dot();
				break;

			case 'i':
			case 'I':
				morse_dot();
				morse_dot();
				break;

			case 'j':
			case 'J':
				morse_dot();
				morse_dash();
				morse_dash();
				morse_dash();
				break;

			case 'k':
			case 'K':
				morse_dash();
				morse_dot();
				morse_dash();
				break;

			case 'l':
			case 'L':
				morse_dot();
				morse_dash();
				morse_dot();
				morse_dot();
				break;

			case 'm':
			case 'M':
				morse_dash();
				morse_dash();
				break;

			case 'n':
			case 'N':
				morse_dash();
				morse_dot();
				break;

			case 'o':
			case 'O':
				morse_dash();
				morse_dash();
				morse_dash();
				break;

			case 'p':
			case 'P':
				morse_dot();
				morse_dash();
				morse_dash();
				morse_dot();
				break;

			case 'q':
			case 'Q':
				morse_dash();
				morse_dash();
				morse_dot();
				morse_dash();
				break;

			case 'r':
			case 'R':
				morse_dot();
				morse_dash();
				morse_dot();
				break;

			case 's':
			case 'S':
				morse_dot();
				morse_dot();
				morse_dot();
				break;

			case 't':
			case 'T':
				morse_dash();
				break;

			case 'u':
			case 'U':
				morse_dot();
				morse_dot();
				morse_dash();
				break;

			case 'v':
			case 'V':
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dash();
				break;

			case 'w':
			case 'W':
				morse_dot();
				morse_dash();
				morse_dash();
				break;

			case 'x':
			case 'X':
				morse_dash();
				morse_dot();
				morse_dot();
				morse_dash();
				break;

			case 'y':
			case 'Y':
				morse_dash();
				morse_dot();
				morse_dash();
				morse_dash();
				break;

			case 'z':
			case 'Z':
				morse_dash();
				morse_dash();
				morse_dot();
				morse_dot();
				break;

//			Números			//

			case '1':
				morse_dot();
				morse_dash();
				morse_dash();
				morse_dash();
				morse_dash();
				break;

			case '2':
				morse_dot();
				morse_dot();
				morse_dash();
				morse_dash();
				morse_dash();
				break;

			case '3':
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dash();
				morse_dash();
				break;

			case '4':
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dash();
				break;

			case '5':
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dot();
				break;

			case '6':
				morse_dash();
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dot();
				break;

			case '7':
				morse_dash();
				morse_dash();
				morse_dot();
				morse_dot();
				morse_dot();
				break;

			case '8':
				morse_dash();
				morse_dash();
				morse_dash();
				morse_dot();
				morse_dot();
				break;

			case '9':
				morse_dash();
				morse_dash();
				morse_dash();
				morse_dash();
				morse_dot();
				break;

			case '0':
				morse_dash();
				morse_dash();
				morse_dash();
				morse_dash();
				morse_dash();
				break;

			case ' ':
				morse_space();
				break;
		}
	}
}
