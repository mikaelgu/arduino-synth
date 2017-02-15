#ifndef __WC_H__
#include "wc.h"
#endif

#ifndef __WC_BASICWAVE_H__
#include "wc_basicwave.h"
#endif

#ifndef __WC_FM_H__
#include "wc_fm.h"
#endif

#ifndef __WC_CROSSFADE_H__
#include "wc_crossfade.h"
#endif

unsigned char wc_fm_wave(wc_wave_t wave, unsigned char x, unsigned char t) {
	return wave(wc_fm_mod(x, t) + t);
}

unsigned char wc_fm_2op(unsigned char x, unsigned char t) {
	return wc_fm_car(wc_fm_mod(x, t), t);
}

unsigned char wc_fm_mod(unsigned char a, unsigned char t) {
	if (a >= 128) {
		return wc_crossfade16(wc_wave_sine(t),
		                      ((unsigned short) wc_wave_sine(t)) << 3,
		                      (a - 128) << 1);
	} else {
		return wc_crossfade(0, wc_wave_sine(t), a << 1);
	}
}


unsigned char wc_fm_car(unsigned char phase, unsigned char t) {
	return wc_wave_sine(t + phase);
}

unsigned char wc_fm_2op_fuzzy(unsigned char x, unsigned char t) {
	return wc_fm_car(wc_fm_mod_fuzzy(x, t), t);

}

unsigned char wc_fm_mod_fuzzy(unsigned char a, unsigned char t) {
	return wc_crossfade(127, wc_wave_sine(t), a) << 3;
}

unsigned char wc_fm_square(unsigned char x, unsigned char t) {
	return wc_wave_square(wc_fm_mod(x, t) + t);
}
unsigned char wc_fm_saw(unsigned char x, unsigned char t) {
	return wc_wave_saw(wc_fm_mod(x, t) + t);
}

