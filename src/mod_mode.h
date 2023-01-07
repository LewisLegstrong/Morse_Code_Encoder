#ifndef MOD_MODE_H
#define MOD_MODE_H

const char inp_m[10] = "$INP:MSG:";
const char inp_t[10] = "$INP:TMP$";
const char out_l[10] = "$OUT:LED$";
const char out_b[10] = "$OUT:BUZ$";
const char inc_f[10] = "$INC:FRQ$";
const char inc_b[10] = "$INC:BPS$";
const char dec_f[10] = "$DEC:FRQ$";
const char dec_b[10] = "$DEC:BPS$";

void mode_change(void);
void input_selection(char inp_sel)

#endif