#ifndef __WC_H__
#define __WC_H__

#define WC_SAMPLES 256
#define WC_SAMPLE_LAST (WC_SAMPLES - 1)
#define WC_SAMPLES_HALF (WC_SAMPLES / 2)
#define WC_MAX_AMP 255

#define WC_AMP_MAX_POS 255
#define WC_AMP_ZERO 127
#define WC_AMP_MAX_NEG 0

typedef unsigned char (*wc_bank_t)(unsigned char x, unsigned char y, unsigned char t);
typedef unsigned char (*wc_table_t)(unsigned char x, unsigned char t);
typedef unsigned char (*wc_wave_t)(unsigned char t);

#define WC_TABLE_BEG(key) \
	{ \
	unsigned char i = 0; \
	switch (key) {

#define WC_TABLE_ENT_XT(nbr, func) \
	case nbr: \
	v[i++] = (func)(x, t); \
	if (i == 2) \
		break;

#define WC_TABLE_ENT_T(nbr, func) \
	case nbr: \
	v[i++] = (func)(t); \
	if (i == 2) \
			break;
#define WC_TABLE_DEF_XT(func) \
	default: \
	v[i] = (func)(x, t); \
		break;

#define WC_TABLE_DEF_T(func) \
	default: \
	v[i] = (func)(t); \
		break;

#define WC_TABLE_END \
	}}

static inline unsigned char wc_greater(unsigned char v1, unsigned char v2) {
	return v1 > v2 ? v1 : v2;
}

static inline unsigned char wc_amp_sixteenths(unsigned char in, unsigned char m) {
	unsigned char val, t, mask;
	val = t = in;

	for (mask = 0x08; mask > 0; mask >>= 1) {
		if (m & mask) {
			t >>= 1;
			val += t;
		}
	}

	m >>= 4;
	val += in * m;

	return val;
}

static inline unsigned char wc_amp_64_clipping(unsigned char in, unsigned short m) {
	unsigned char t, mask;
	unsigned short val;
	val = t = in;

	for (mask = 0x20; mask > 0; mask >>= 1) {
		t >>= 1;
		if (m & mask) {
			val += t;
		}
	}

	m >>= 6;
	val += in * m;

	if (0xFF00 & val)
		val = 0xFF;

	return val;
}

#endif
