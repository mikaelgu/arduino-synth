#ifndef __WC_H__
#include "wc.h"
#endif

#ifndef __WC_BASICWAVE_H__
#include "wc_basicwave.h"
#endif

#ifndef __WC_MORPHWAVE_H__
#include "wc_morphwave.h"
#endif

#ifndef __WC_CROSSFADE_H__
#include "wc_crossfade.h"
#endif

#ifndef __WC_COMPRESS_H__
#include "wc_compress.h"
#endif

unsigned char
wc_mw_pulse(unsigned char x, unsigned char t) {
	unsigned char limit = WC_SAMPLES_HALF -
	                      (x >> 1);

	return t >= limit ? WC_AMP_ZERO : WC_MAX_AMP;
}

unsigned char
wc_mw_square_sine(unsigned char x, unsigned char t) {
	return wc_crossfade(wc_wave_square(t),
	                    wc_wave_sine(t),
	                    x);
}

unsigned char
wc_mw_saw_square(unsigned char x, unsigned char t) {
	return wc_crossfade(wc_wave_saw(t),
	                    wc_wave_square(t),
	                    x);
}

unsigned char
wc_mw_triangle_square(unsigned char x, unsigned char t) {
	return wc_crossfade(wc_wave_triangle(t),
	                    wc_wave_square(t),
	                    x);
}

unsigned char
wc_mw_shark_triangle(unsigned char x, unsigned char t) {
	return wc_crossfade(wc_wave_shark(t),
	                    wc_wave_triangle(t),
	                    x);
}

unsigned char
wc_mw_rounded_square_square(unsigned char x, unsigned char t) {
	return wc_crossfade(wc_wave_rounded_square(t),
	                    wc_wave_square(t),
	                    x);
}

unsigned char
wc_mw_pwm_saw(unsigned char x, unsigned char t) {
	t = wc_amp_64_clipping(t, (unsigned short) x << 2);
	return wc_wave_saw(t);
}

unsigned char
wc_mw_dual_saw(unsigned char x, unsigned char t) {
	return wc_compress_soft_add(wc_wave_saw(t),
	                            wc_wave_saw(t - x));
}

unsigned char
wc_mw_quad_saw(unsigned char x, unsigned char t) {
	unsigned char v[2];

	v[0] = wc_compress_soft_add(wc_wave_saw(t),
	                            wc_wave_saw(t - x));

	v[1] = wc_compress_soft_add(wc_wave_saw(t + x),
	                            wc_wave_saw(t - (x>>1)));

	return wc_compress_soft_add(v[0],
	                            v[1]);
}

unsigned char
wc_mw_bento(unsigned char x, unsigned char t) {
	unsigned char v[2];

	WC_TABLE_BEG(x>>6)
		WC_TABLE_ENT_T(0, wc_wave_sine)
		WC_TABLE_ENT_T(1, wc_wave_triangle90)
		WC_TABLE_ENT_T(2, wc_wave_saw)
		WC_TABLE_ENT_T(3, wc_wave_square)
		WC_TABLE_DEF_T(wc_wave_sine)
	WC_TABLE_END

	return wc_crossfade(v[0], v[1],  x << 2);
}

unsigned char
wc_mw_extra_synth(unsigned char x, unsigned char t) {
	unsigned char v[2];

	WC_TABLE_BEG(x>>6)
		WC_TABLE_ENT_T(0, wc_wave_shark90)
		WC_TABLE_ENT_T(1, wc_wave_half_sine_saw)
		WC_TABLE_ENT_T(2, wc_wave_ramp180)
		WC_TABLE_ENT_T(3, wc_wave_half_sine)
		WC_TABLE_DEF_T(wc_wave_shark90)
	WC_TABLE_END

	return wc_crossfade(v[0], v[1],  x << 2);
}


