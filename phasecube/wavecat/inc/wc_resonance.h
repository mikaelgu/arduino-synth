#ifndef __WC_RESONANCE_H__
#define __WC_RESONANCE_H__

unsigned char wc_add_triangle_resonance(unsigned char wave, unsigned char idx, unsigned char t);

unsigned char wc_resonant_saw(unsigned char idx, unsigned char t);
unsigned char wc_resonant_sine(unsigned char idx, unsigned char t);

unsigned char wc_resonant_saw_table(unsigned char x, unsigned char t);
unsigned char wc_resonant_sine_table(unsigned char x, unsigned char t);
	
#endif
