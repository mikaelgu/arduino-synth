#ifndef __WC_BASICWAVE_H__
#define __WC_BASICWAVE_H__

unsigned char wc_wave_sine(unsigned char pos);

unsigned char wc_wave_ramp(unsigned char pos);
unsigned char wc_wave_ramp180(unsigned char pos);

unsigned char wc_wave_saw(unsigned char pos);

unsigned char wc_wave_square(unsigned char pos);

unsigned char wc_wave_shark(unsigned char pos);
unsigned char wc_wave_shark90(unsigned char pos);

unsigned char wc_wave_triangle(unsigned char pos);
unsigned char wc_wave_triangle90(unsigned char pos);

unsigned char wc_wave_half_sine(unsigned char pos);
unsigned char wc_wave_half_sine_saw(unsigned char pos);

unsigned char wc_wave_rounded_square(unsigned char pos);

unsigned char wc_wave_sine_squared(unsigned char pos);

#endif
