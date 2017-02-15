#ifndef __WC_H__
#include "wc.h"
#endif

#ifndef __WC_BASICWAVE_H__
#include "wc_basicwave.h"
#endif

#ifndef __WC_VOSIM_H__
#include "wc_vosim.h"
#endif

unsigned char
wc_vosim(unsigned char f, unsigned char t) {
	unsigned short fs =  64 + ((unsigned short) f << 1);
	t = wc_amp_64_clipping(t, fs);
	return wc_wave_sine_squared(t);
}

