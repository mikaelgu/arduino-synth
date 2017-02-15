#ifndef __WC_H__
#include "wc.h"
#endif

#ifndef __WC_BASICWAVE_H__
#include "wc_basicwave.h"
#endif

#ifndef __WC_CROSSFADE_H__
#include "wc_crossfade.h"
#endif

#ifndef __WC_SINETABLES_H__
#include "wc_sinetables.h"
#endif

unsigned char
wc_wave_sine(unsigned char pos) {
	if (pos >= 192) {
		return 127 - wc_table_sine256[255 - pos];
	} else if (pos >= 128) {
		return 127 - wc_table_sine256[pos - 128];
	} else if (pos >= 64) {
		return 127 + wc_table_sine256[127 - pos];
	} else {
		return 127 + wc_table_sine256[pos];
	}
}

unsigned char
wc_wave_half_sine(unsigned char pos) {
	return wc_wave_sine(pos >> 1);
}

unsigned char
wc_wave_half_sine_saw(unsigned char pos) {
	if (pos >= 128) {
		return 255 - (pos - 128);
	} else {
		return 127 + wc_table_sine256[pos >> 1];
	}
}

unsigned char
wc_wave_ramp(unsigned char pos) {
	return pos;
}

unsigned char
wc_wave_ramp180(unsigned char pos) {
	return wc_wave_ramp(pos + 128);
}

unsigned char
wc_wave_saw(unsigned char pos) {
	return WC_MAX_AMP - pos;
}

unsigned char
wc_wave_square(unsigned char pos) {
	return pos < WC_SAMPLES_HALF ? WC_MAX_AMP : 0;
}

unsigned char
wc_wave_shark(unsigned char pos) {
	return pos < WC_SAMPLES_HALF ? pos << 1 : (WC_MAX_AMP - pos );
}

unsigned char
wc_wave_shark90(unsigned char pos) {
	return wc_wave_shark(pos + 64);
}


unsigned char
wc_wave_triangle(unsigned char pos) {
	return pos < WC_SAMPLES_HALF ?
	         pos << 1 :
	         (WC_MAX_AMP - ((pos - WC_SAMPLES_HALF) << 1)); 
}

unsigned char
wc_wave_triangle90(unsigned char pos) {
	return wc_wave_triangle(pos + 64);
}

unsigned char
wc_wave_rounded_square(unsigned char pos) {
	if (pos >= 192) {
		return WC_AMP_MAX_NEG;
	} else if (pos >= 128) {
		return WC_MAX_AMP - (wc_table_sine256[pos - 128] << 1);
	} else if (pos >= 64) {
		return WC_AMP_MAX_POS;
	} else {
		return wc_table_sine256[pos] << 1;
	}
}

unsigned char
wc_wave_sine_squared(unsigned char pos) {
	pos >>= 1;

	pos &= 63;
	if (pos >= 32)
		return wc_table_sine64_squared[63 - pos];
	else
		return wc_table_sine64_squared[pos];
}
