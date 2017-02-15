#ifndef __WC_H__
#include "wc.h"
#endif

#ifndef __WC_CROSSFADE_H__
#include "wc_crossfade.h"
#endif

#ifndef __WC_BASICWAVE_H__
#include "wc_basicwave.h"
#endif

#ifndef __WC_WINRES_H__
#include "wc_winres.h"
#endif

static unsigned char
wc_winres_env(unsigned char t) {
	if (t < WC_SAMPLES_HALF) {
		return WC_MAX_AMP;
	}
	return WC_MAX_AMP - ((t - WC_SAMPLES_HALF) << 1);
}

static unsigned char
wc_winres_amp_env(unsigned char v, unsigned char t) {
	return wc_crossfade(WC_AMP_ZERO, v, wc_winres_env(t));
}

unsigned char
wc_winres_sine(unsigned char m, unsigned char t) {
	unsigned char v = wc_wave_sine(wc_amp_sixteenths(t, m));

	v = wc_winres_amp_env(v, t);

	return v;
}

unsigned char
wc_winres_saw(unsigned char m, unsigned char t) {
	unsigned char v = wc_wave_saw(wc_amp_sixteenths(t, m));

	v = wc_winres_amp_env(v, t);

	return v;
}

unsigned char
wc_winres_wave(wc_wave_t wave, unsigned char m, unsigned char t) {
	unsigned char v = wave(wc_amp_sixteenths(t, m));

	v = wc_winres_amp_env(v, t);

	return v;
}
