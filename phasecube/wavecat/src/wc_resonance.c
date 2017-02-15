#ifndef __WC_H__
#include "wc.h"
#endif

#ifndef __WC_BASICWAVE_H__
#include "wc_basicwave.h"
#endif

#ifndef __WC_RESONANCE_H__
#include "wc_resonance.h"
#endif

#ifndef __WC_CROSSFADE_H__
#include "wc_crossfade.h"
#endif

unsigned char
wc_triangle_resonance_wave(unsigned char idx, unsigned char t) {
	unsigned char v = 0;
	if (idx > 1) {
		v = wc_wave_triangle(t * idx);
	}
	return v;
}

unsigned char
wc_add_triangle_resonance(unsigned char wave, unsigned char idx, unsigned char t) {
	return wc_greater(wave, wc_triangle_resonance_wave(idx, t));
}


unsigned char wc_resonant_saw(unsigned char idx, unsigned char t) {
	return wc_add_triangle_resonance(wc_wave_saw(t), idx, t);
}

unsigned char wc_resonant_sine(unsigned char idx, unsigned char t) {
	return wc_add_triangle_resonance(wc_wave_sine(t), idx, t);
}

unsigned char
wc_resonant_saw_table(unsigned char x, unsigned char t) {
	unsigned char v[2];
	unsigned char idx = (x >> 4) + 1,
	              mix = x << 4;

	v[0] = wc_resonant_saw(idx, t);
	v[1] = wc_resonant_saw(idx + 1, t);

	return wc_crossfade(v[0], v[1], mix);
}

unsigned char
wc_resonant_sine_table(unsigned char x, unsigned char t) {
	unsigned char v[2];
	unsigned char idx = (x >> 4) + 1,
	              mix = x << 4;

	v[0] = wc_resonant_sine(idx, t);
	v[1] = wc_resonant_sine(idx + 1, t);

	return wc_crossfade(v[0], v[1], mix);
}


