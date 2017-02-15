#ifndef __WC_H__
#include "wc.h"
#endif

#ifndef __WC_BASICWAVE_H__
#include "wc_basicwave.h"
#endif

#ifndef __WC_AMP_H__
#include "wc_amp.h"
#endif

#ifndef __WC_CROSSFADE_H__
#include "wc_crossfade.h"
#endif

#ifndef __WC_COMPRESS_H__
#include "wc_compress.h"
#endif

unsigned char wc_amp_soft(unsigned char v, unsigned char amp) {
	return wc_compress_soft_add(v,
	                            wc_crossfade(WC_AMP_ZERO, v, amp));
}

unsigned char
wc_amp_sine(unsigned char x, unsigned char t) {
	unsigned char v;

	v = wc_wave_sine(t);
	v = wc_amp_soft(v, x);

	return v;
}

