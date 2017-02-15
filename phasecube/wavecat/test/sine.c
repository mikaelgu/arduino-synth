#include <math.h>
#include <stdio.h>

void sine_array(unsigned char *name, unsigned int steps, unsigned int amp, unsigned char square) {
	int i;
	printf("unsigned char %s[%d] = {", name, steps/4);
	for (i = 0; i < steps/4; i++) {
		float radians = i * M_PI * 2 / steps;
		float result;
		result = sinf(radians);

		if (square)
			result *= result;

		if (i % 8 == 0)
			printf("\n\t");
		printf (" %3u%", (unsigned int) (amp * result));
		if (i != steps/4 - 1)
			printf(",");
	}
	printf ("\n};\n");
}

void atan_array(void) {
	//=ATAN((A1/256)*(PI()*0.8))*(106)
	int i;

	printf("unsigned char atan_array[%d] = {", 256/2);

	for (i = 0; i < 256; i += 2) {
		float r = i * M_PI * 0.8 / 256;
		float res = atanf(r) * 106;

		if (i % 16 == 0)
			printf("\n\t");
		printf (" %3u%", (unsigned int) (res));
		if (i != 254)
			printf(",");

	}
	printf ("\n};\n");

}

int main(void) {
	sine_array("wc_table_sine256", 256, 127, 0);
	//sine_array("wc_table_sine64_100", 64, 127, 0);	
	//sine_array("wc_table_sine64_75", 64, 127 * 0.75, 0);	
	//sine_array("wc_table_sine64_50", 64, 127 * 0.5, 0);	
	//sine_array("wc_table_sine64_25", 64, 127 * 0.25, 0);	
	//sine_array("wc_table_sine64_13", 64, 127 * 0.125, 0);	
	sine_array("wc_table_sine64_squared", 128, 255, 0);	

	atan_array();
}

