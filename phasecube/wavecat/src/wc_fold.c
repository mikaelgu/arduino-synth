#ifndef __WC_H__
#include "wc.h"
#endif

#ifndef __WC_FOLD_H__
#include "wc_fold.h"
#endif

#ifndef __WC_BASICWAVE_H__
#include "wc_basicwave.h"
#endif

#ifndef __WC_CROSSFADE_H__
#include "wc_crossfade.h"
#endif

unsigned short
wc_fold_amp(unsigned short in, unsigned char amp) {
	unsigned short val = in;

	if (amp & 1)
		val += in>>1;

	amp /= 2;
	val += in * amp;

	return val;
}

unsigned char
wc_fold(unsigned char in, unsigned char offset, unsigned char amp) {
	unsigned short val = (unsigned short) in + offset;

	if (val == WC_AMP_ZERO) {
		//Do nothing
	}
	else if (val > WC_AMP_ZERO) {
		val -= WC_AMP_ZERO;
		val = wc_fold_amp(val, amp);

		if (val <= 128) {
			val += WC_AMP_ZERO;
		}
		else {
			val -= 128;
			if (!(val & 256))
				val = 255 - (val & 0xFF);
		}
	}
	else { // val < WC_AMP_ZERO
		val = WC_AMP_ZERO - val;
		val = wc_fold_amp(val, amp);
		if (val <= WC_AMP_ZERO) {
			val = WC_AMP_ZERO - val;
		} else {
			val -= WC_AMP_ZERO;
			if (val & 256)
				val = 255 - (val & 0xFF);
		}
	}

	return (unsigned char) val;
}

unsigned char
wc_fold_sine(unsigned char offset, unsigned char amp, unsigned char t) {
	return wc_fold(wc_wave_sine(t), offset, amp);
}

unsigned char
wc_fold_triangle(unsigned char offset, unsigned char amp, unsigned char t) {
	return wc_fold(wc_wave_triangle(t), offset, amp);
}

unsigned char
wc_fold_sine_table(unsigned char x, unsigned char t) {
	unsigned char v[2];
	unsigned char amp = (x >> 4),
	              mix = x << 4;

	v[0] = wc_fold_sine(0, amp, t);
	v[1] = wc_fold_sine(0, amp + 1, t);

	return wc_crossfade(v[0], v[1], mix);
}

