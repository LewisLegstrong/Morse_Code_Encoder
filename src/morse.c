#include "morse.h"

unsigned char out_sel = 'L'; //At the start, the default OUTPUT is the LED
// Defines Morse Caracters: Dot, Dash and also defines Space between letters
void morse_dot(void) //Creates the Dot output
{
	timer1_init(freq);
	delay_t0(bps);
	
	timer1_off();
	delay_t0(bps);
}

void morse_dash(void) //Creates the dash output
{
	timer1_init(freq);
	for (int i = 0; i < 3; i++) //3x the beat time 
		delay_t0(bps);
	
	timer1_off();
	delay_t0(bps);
}

void morse_space(void) //Creates the space in between words
{
	for (int i = 0; i < 2; i++) //2x the beat time
		delay_t0(bps);
}

/*********************************************************************
 * 						Biblioteca Conversão 						 *
 * 								Morse								 *
 *********************************************************************/

//Converts the phrase to morse Code to be sent to an LED or Buzzer
//Could have been achieved with a matrix that calls the DASH/DOT functions
void morse_convert(char *phrasetoconvert)
{
	int i = 0;

	while (phrasetoconvert[i] != '\0')
	{
		int j = 0;
		switch (phrasetoconvert[i])
		{
			case 'a':
			case 'A':
				morse_dot();
				morse_dash();
				morse_space();
				break;

			case 'b':
			case 'B':
				morse_dash();
				morse_dot();
				morse_dot();
				morse_dot();
				morse_space();
				break;

			case 'c':
			case 'C':
				morse_dash();
				morse_dot();
				morse_dash();
				morse_dot();
				morse_space();
				break;

			case 'd':
			case 'D':
				morse_dash();
				morse_dot();
				morse_dot();
				morse_space();
				break;

			case 'e':
			case 'E':
				morse_dot();
				morse_space();
				break;

			case 'f':
			case 'F':
				morse_dot();
				morse_dot();
				morse_dash();
				morse_dot();
				morse_space();
				break;

			case 'g':
			case 'G':
				morse_dash();
				morse_dash();
				morse_dot();
				morse_space();
				break;

			case 'h':
			case 'H':
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dot();
				morse_space();
				break;

			case 'i':
			case 'I':
				morse_dot();
				morse_dot();
				morse_space();
				break;

			case 'j':
			case 'J':
				morse_dot();
				morse_dash();
				morse_dash();
				morse_dash();
				morse_space();
				break;

			case 'k':
			case 'K':
				morse_dash();
				morse_dot();
				morse_dash();
				morse_space();
				break;

			case 'l':
			case 'L':
				morse_dot();
				morse_dash();
				morse_dot();
				morse_dot();
				morse_space();
				break;

			case 'm':
			case 'M':
				morse_dash();
				morse_dash();
				morse_space();
				break;

			case 'n':
			case 'N':
				morse_dash();
				morse_dot();
				morse_space();
				break;

			case 'o':
			case 'O':
				morse_dash();
				morse_dash();
				morse_dash();
				morse_space();
				//TESTE
				usart_transmit("Transmited 'O'\n");
				break;

			case 'p':
			case 'P':
				morse_dot();
				morse_dash();
				morse_dash();
				morse_dot();
				morse_space();
				break;

			case 'q':
			case 'Q':
				morse_dash();
				morse_dash();
				morse_dot();
				morse_dash();
				morse_space();
				break;

			case 'r':
			case 'R':
				morse_dot();
				morse_dash();
				morse_dot();
				morse_space();
				break;

			case 's':
			case 'S':
				morse_dot();
				morse_dot();
				morse_dot();
				morse_space();
				//TESTE
				usart_transmit("Transmited 'S'\n");
				break;

			case 't':
			case 'T':
				morse_dash();
				morse_space();
				break;

			case 'u':
			case 'U':
				morse_dot();
				morse_dot();
				morse_dash();
				morse_space();
				break;

			case 'v':
			case 'V':
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dash();
				morse_space();
				break;

			case 'w':
			case 'W':
				morse_dot();
				morse_dash();
				morse_dash();
				morse_space();
				break;

			case 'x':
			case 'X':
				morse_dash();
				morse_dot();
				morse_dot();
				morse_dash();
				morse_space();
				break;

			case 'y':
			case 'Y':
				morse_dash();
				morse_dot();
				morse_dash();
				morse_dash();
				morse_space();
				break;

			case 'z':
			case 'Z':
				morse_dash();
				morse_dash();
				morse_dot();
				morse_dot();
				morse_space();
				break;

		//			Números			//

			case '1':
				morse_dot();
				morse_dash();
				morse_dash();
				morse_dash();
				morse_dash();
				morse_space();
				break;

			case '2':
				morse_dot();
				morse_dot();
				morse_dash();
				morse_dash();
				morse_dash();
				morse_space();
				break;

			case '3':
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dash();
				morse_dash();
				morse_space();
				break;

			case '4':
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dash();
				morse_space();
				break;

			case '5':
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dot();
				morse_space();
				break;

			case '6':
				morse_dash();
				morse_dot();
				morse_dot();
				morse_dot();
				morse_dot();
				morse_space();
				break;

			case '7':
				morse_dash();
				morse_dash();
				morse_dot();
				morse_dot();
				morse_dot();
				morse_space();
				break;

			case '8':
				morse_dash();
				morse_dash();
				morse_dash();
				morse_dot();
				morse_dot();
				morse_space();
				break;

			case '9':
				morse_dash();
				morse_dash();
				morse_dash();
				morse_dash();
				morse_dot();
				morse_space();
				break;

			case '0':
				morse_dash();
				morse_dash();
				morse_dash();
				morse_dash();
				morse_dash();
				morse_space();
				break;

			case 32:
				while(j++ < 3)
					morse_space();
				break;
		}
		i++;
	}
	timer1_off();
}
