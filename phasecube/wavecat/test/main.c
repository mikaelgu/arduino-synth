
#include <stdio.h>
#include <stdlib.h>

#include "wc.h"
#include "wc_main.h"

int main(int argc, char **argv) {
	//int i;
	//for (i = 200; i < 201; i++) {
	//	printf("%3d, ", (unsigned char) wc_amp_64_clipping(i, 1));
	//}
	//printf("\n");
	//return 0;

	int x = 0, y = 0, z = 0, pdwave = 0, pdamount = 0, t;
	if (argc != 4 && argc != 5 && argc != 6) {
		printf("%s x y z", argv[0]);
		return -1;
	}

	x = atoi(argv[1]);
	y = atoi(argv[2]);
	z = atoi(argv[3]);

	if (argc == 6) {
		pdwave = atoi(argv[4]);
		pdamount = atoi(argv[5]);
	}

	if (argc == 5) {
		y <<= 8;
		z <<= 8;
	}

	printf("\"(%d,%d,%d)\"",x,y,z);
	for (t = 0; t < WC_SAMPLES; t++) {
		printf(", %3d", wc_gen(x,y,z,pdwave,pdamount,t));
	}
	printf("\n");

	return 0;
}
