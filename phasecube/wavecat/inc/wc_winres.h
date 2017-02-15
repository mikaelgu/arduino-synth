#ifndef __WC_WINRES_H__
#define __WC_WINRES_H__

/*
 * Windowed resonance
 *
 * m is the amplification of t when calculating the resonance frequence
 * in steps of 1/16.
 *
 */

unsigned char wc_winres_sine(unsigned char m, unsigned char t);
unsigned char wc_winres_saw(unsigned char m, unsigned char t);
unsigned char wc_winres_wave(wc_wave_t wave, unsigned char m, unsigned char t);

#endif
