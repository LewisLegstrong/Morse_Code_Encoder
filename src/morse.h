#ifndef MORSE_H
#define MORSE_H

#include <stdio.h>
#include <avr/io.h>

#include "timer_init.h"
#include "usart_init.h"

extern unsigned char out_sel;

void morse_convert(char *phrasetoconvert);
void morse_dot(void);
void morse_dash(void);
void morse_space(void);

#endif