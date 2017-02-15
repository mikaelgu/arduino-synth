#ifndef __WC_H__
#include "wc.h"
#endif

#ifndef __WC_COMPRESS_H__
#include "wc_compress.h"
#endif

unsigned char atan_array[128] = {
	   0,   2,   4,   6,   8,  10,  12,  14,
	  16,  18,  20,  22,  24,  26,  28,  30,
	  32,  34,  36,  37,  39,  41,  43,  44,
	  46,  48,  50,  51,  53,  54,  56,  57,
	  59,  60,  62,  63,  65,  66,  67,  69,
	  70,  71,  73,  74,  75,  76,  77,  79,
	  80,  81,  82,  83,  84,  85,  86,  87,
	  88,  89,  90,  91,  91,  92,  93,  94,
	  95,  96,  96,  97,  98,  99,  99, 100,
	 101, 101, 102, 103, 103, 104, 105, 105,
	 106, 107, 107, 108, 108, 109, 109, 110,
	 110, 111, 111, 112, 112, 113, 113, 114,
	 114, 115, 115, 116, 116, 116, 117, 117,
	 118, 118, 119, 119, 119, 120, 120, 120,
	 121, 121, 121, 122, 122, 122, 123, 123,
	 123, 124, 124, 124, 125, 125, 125, 126
};

unsigned char
wc_compress_soft_255_127(unsigned char v) {
	unsigned char idx = v >> 1;
	unsigned char res;

	res = atan_array[idx];
	res += atan_array[idx + (v & 1)];
	res >>= 1;

	return res;
}

unsigned char
wc_compress_soft_add(unsigned char a, unsigned char b) {
	signed short t = (short) a + b;
	t -= (short) WC_AMP_ZERO << 1;
	unsigned char r = WC_AMP_ZERO;

	if (t == 0) {
		// Nothing
	} else if (t > 0) {
		r += wc_compress_soft_255_127(t);
	} else {
		r -= wc_compress_soft_255_127(-t);
	}

	return r;
}
