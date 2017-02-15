#ifndef __WC_H__
#include "wc.h"
#endif

#ifndef __WC_MAIN_H__
#include "wc_main.h"
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

#ifndef __WC_FM_H__
#include "wc_fm.h"
#endif

#ifndef __WC_RESONANCE_H__
#include "wc_resonance.h"
#endif

#ifndef __WC_FOLD_H__
#include "wc_fold.h"
#endif

#ifndef __WC_WINRES_H__
#include "wc_winres.h"
#endif

#ifndef __WC_VOSIM_H__
#include "wc_vosim.h"
#endif

#ifndef __WC_AMP_H__
#include "wc_amp.h"
#endif


unsigned char default_bank(unsigned char x, unsigned char y, unsigned char t) {
	(void) x;
	(void) y;
	(void) t;

	return 0;
}

#if 0
static wc_table_t cube[17][17] = {
	/* 0 */ {},
	/* 1 */ {},
	/* 2 */ {},
	/* 3 */ {},
	/* 4 */ {},
	/* 5 */ {},
	/* 6 */ {},
	/* 7 */ {},
	/* 8 */ {},
	/* 9 */ {},
	/* A */ {},
	/* B */ {},
	/* C */ {},
	/* D */ {},
	/* E */ {},
	/* F */ {},
	/* 0 */ {},
};
#endif

unsigned char
wc_bank0(unsigned char x,
         unsigned char y,
         unsigned char t) {
	unsigned char v[2];

	WC_TABLE_BEG(y >> 4)
		WC_TABLE_ENT_XT(0, wc_mw_bento)
		WC_TABLE_ENT_XT(1, wc_mw_pulse)
		WC_TABLE_ENT_XT(2, wc_fm_2op)
		WC_TABLE_ENT_XT(3, wc_mw_square_sine)
		WC_TABLE_ENT_XT(4, wc_mw_extra_synth)
		WC_TABLE_ENT_XT(5, wc_fm_2op_fuzzy)
		WC_TABLE_ENT_XT(6, wc_resonant_saw_table)
		WC_TABLE_ENT_XT(7, wc_resonant_sine_table)
		WC_TABLE_ENT_XT(8, wc_fold_sine_table)
		WC_TABLE_ENT_XT(9, wc_winres_sine)
		WC_TABLE_ENT_XT(10, wc_winres_saw)
		WC_TABLE_ENT_XT(11, wc_fm_square)
		WC_TABLE_ENT_XT(12, wc_fm_saw)
		WC_TABLE_ENT_XT(13, wc_fold_sine_table)
		WC_TABLE_ENT_XT(14, wc_mw_triangle_square)
		WC_TABLE_ENT_XT(15, wc_vosim)
		WC_TABLE_ENT_XT(16, wc_mw_pwm_saw)
		WC_TABLE_DEF_XT(wc_mw_bento)
	WC_TABLE_END

	return wc_crossfade(v[0], v[1], (y & 0xF) << 4);
}

unsigned char
wc_bank1(unsigned char x,
         unsigned char y,
         unsigned char t) {
	unsigned char v[2];

	WC_TABLE_BEG(y >> 4)
		WC_TABLE_ENT_XT(0, wc_mw_quad_saw)
		WC_TABLE_ENT_XT(1, wc_mw_shark_triangle)
		WC_TABLE_ENT_XT(2, wc_mw_dual_saw)
		WC_TABLE_ENT_XT(3, wc_amp_sine)
		WC_TABLE_ENT_XT(4, wc_mw_pwm_saw)
		WC_TABLE_ENT_XT(5, wc_mw_rounded_square_square)
		WC_TABLE_ENT_XT(6, wc_amp_sine)
		WC_TABLE_ENT_XT(7, wc_amp_sine)
		WC_TABLE_ENT_XT(8, wc_amp_sine)
		WC_TABLE_ENT_XT(9, wc_amp_sine)
		WC_TABLE_ENT_XT(10, wc_amp_sine)
		WC_TABLE_ENT_XT(11, wc_amp_sine)
		WC_TABLE_ENT_XT(12, wc_amp_sine)
		WC_TABLE_ENT_XT(13, wc_amp_sine)
		WC_TABLE_ENT_XT(14, wc_amp_sine)
		WC_TABLE_ENT_XT(15, wc_amp_sine)
		WC_TABLE_ENT_XT(16, wc_amp_sine)
		WC_TABLE_DEF_XT(wc_mw_quad_saw)
	WC_TABLE_END

	return wc_crossfade(v[0], v[1], (y & 0xF) << 4);
}



static wc_bank_t banks[17] = {
	/* 0 */ wc_bank0,
	/* 1 */ wc_bank1,
	/* 2 */ default_bank,
	/* 3 */ default_bank,
	/* 4 */ default_bank,
	/* 5 */ default_bank,
	/* 6 */ default_bank,
	/* 7 */ default_bank,
	/* 8 */ default_bank,
	/* 9 */ default_bank,
	/* A */ default_bank,
	/* B */ default_bank,
	/* C */ default_bank,
	/* D */ default_bank,
	/* E */ default_bank,
	/* F */ default_bank,
	/* wrapp */ wc_bank0,
};

unsigned char
wc_gen(unsigned char x,
       unsigned char y,
       unsigned char z,
       unsigned char pdwave,
       unsigned char pdamount,
       unsigned char t) {
	unsigned char v[2];

	unsigned char idx = z >> 4,
	              mix = z << 4;

	// Phase distortion
	t = wc_crossfade(t,
	                 wc_mw_bento(pdwave, t),
	                 pdamount);

	// Wave calculation
	v[0] = banks[idx](x, y, t);
	v[1] = banks[idx + 1](x, y, t);

	return wc_crossfade(v[0], v[1], mix);
}

