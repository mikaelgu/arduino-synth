#ifndef __WC_FM_H__
#define __WC_FM_H__

unsigned char wc_fm_2op(unsigned char x, unsigned char t);
unsigned char wc_fm_mod(unsigned char a, unsigned char t);
unsigned char wc_fm_car(unsigned char phase, unsigned char t);

unsigned char wc_fm_square(unsigned char x, unsigned char t);
unsigned char wc_fm_saw(unsigned char x, unsigned char t);
unsigned char wc_fm_wave(wc_wave_t wave, unsigned char x, unsigned char t);

unsigned char wc_fm_2op_fuzzy(unsigned char x, unsigned char t);
unsigned char wc_fm_mod_fuzzy(unsigned char a, unsigned char t);

#endif
