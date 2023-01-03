#ifndef MORSE_H
#define MORSE_H

#include <stdio.h>
#include <avr/io.h>

#include "timer_init.h"

void morse_convert(void);
void morse_dot(void);
void morse_dash(void);
void morse_space(void);

#endif