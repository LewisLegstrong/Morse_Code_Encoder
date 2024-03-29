#ifndef MODE_MOD_H
#define MODE_MOD_H

#include <avr/io.h>
#include <string.h>

#include "usart_init.h"
#include "morse.h"

extern const char inp_m[120];
extern const char inp_t[10]; //Change Input to Temp
extern const char out_l[10];
extern const char out_b[10];
extern const char inc_f[10];
extern const char inc_b[10];
extern const char dec_f[10];
extern const char dec_b[10];

void mode_change(void);
void input_selection(char inp_sel);

#endif