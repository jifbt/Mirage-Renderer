/* Name: bmpEncoder_test.c v0.0.2
 * Date: 2021-08-28
 * Intro: Render a colorChecker. See output at colorChecker.bmp.
 * Update: Rename bmpTest.c bmpEncoder_test.c
 */
#include "bmpEncoder.h"
#include "bmpPalette.h"
int main() {
	int32_t i, j;
	uint32_t absHeight, rowSize, pixelArraySize, offBits, size;
	BMP bmp = BMPInit(16*6+1, -16*4-1, 8, 25, colorChecker25, &absHeight, &rowSize, 
		&pixelArraySize, &offBits, &size);
	if(bmp == NULL) {
		puts("An error occured");
		return 0;
	}
	for(i=0; i<=16*4; ++i) {
		for(j=0; j<=16*6; ++j) {
			if((i & 15) && (j & 15)) {
				bmp[rowSize * i + j + offBits] = (i >> 4) * 6 + (j >> 4) + 1;
			} else {
				bmp[rowSize * i + j + offBits] = 0;
			}
		}
	}
	BMPsave(bmp, "colorChecker.bmp");
	puts("File created successfully");
	return 0;
}
