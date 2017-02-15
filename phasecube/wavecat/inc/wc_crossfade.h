#ifndef __WC_CROSSFADE_H__
#define __WC_CROSSFADE_H__

static inline unsigned short
wc_crossfade16(unsigned short v1, unsigned short v2, unsigned char pos) {
	unsigned int v1i = v1,
	             v2i = v2;
	v1i *= ((unsigned short) 256 - pos);
	v2i *= (pos + (unsigned short) 1);
	v1i += v2i;
	v1i >>= 8;
	return (unsigned short) v1i;
}

static inline unsigned char
wc_crossfade(unsigned char v1, unsigned char v2, unsigned char pos) {
	unsigned short v1s = v1,
	               v2s = v2;
	v1s *= ((unsigned short) 256 - pos);
	v2s *= (pos + (unsigned short) 1);
	v1s += v2s;
	v1s >>= 8;
	return (unsigned char) v1s;
}

static inline unsigned char
wc_crossfade4(unsigned char v1, unsigned char v2, unsigned char pos) {
	unsigned short t = v1;
	if (pos) {
		t += v2;

		if (pos == 1) {
			t += v1 << 1;
		} else if (pos == 2) {
			t <<= 1;
		} else if (pos == 3) {
			t += v2 << 1;
		}

		t >>= 2;
	}

	return t;
}

#endif
