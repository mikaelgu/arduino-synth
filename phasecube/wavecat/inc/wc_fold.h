#ifndef __WC_FOLD_H__
#define __WC_FOLD_H__

unsigned short wc_fold_amp(unsigned short in, unsigned char amp);
unsigned char wc_fold(unsigned char in, unsigned char offset, unsigned char amp);

unsigned char wc_fold_sine(unsigned char offset, unsigned char amp, unsigned char t);

unsigned char wc_fold_triangle(unsigned char offset, unsigned char amp, unsigned char t);

unsigned char wc_fold_sine_table(unsigned char x, unsigned char t);

#endif
