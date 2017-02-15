#ifndef __WC_MORPHWAVE_H__
#define __WC_MORPHWAVE_H__

unsigned char wc_mw_pulse(unsigned char x, unsigned char t);
unsigned char wc_mw_square_sine(unsigned char x, unsigned char t);
unsigned char wc_mw_saw_square(unsigned char x, unsigned char t);
unsigned char wc_mw_triangle_square(unsigned char x, unsigned char t);
unsigned char wc_mw_shark_triangle(unsigned char x, unsigned char t);
unsigned char wc_mw_rounded_square_square(unsigned char x, unsigned char t);
unsigned char wc_mw_pwm_saw(unsigned char x, unsigned char t);
unsigned char wc_mw_dual_saw(unsigned char x, unsigned char t);
unsigned char wc_mw_quad_saw(unsigned char x, unsigned char t);
unsigned char wc_mw_bento(unsigned char x, unsigned char t);
unsigned char wc_mw_extra_synth(unsigned char x, unsigned char t);

#endif
