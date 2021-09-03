/* Name: fractalIterate.h v0.0.0
 * Date: 2021-09-03
 * Intro: Render Mandelbrot and Julia sets.
 */
#ifndef _FRACTALITERATE
#define _FRACTALITERATE 0x000000

#include <assert.h>
#include "bmpEncoder.h"
#include "bmpLine.h"
#include "bmpPalette.h"

#ifdef __cplusplus
extern "C" {
#endif

void fractalMandelbrotSet(char* path, int32_t width, int32_t height, 
					uint32_t clrUsed, PALETTE palette, LINE lineX, LINE lineY) {
	int32_t i, j, k;
	uint32_t absHeight, rowSize, pixelArraySize, offBits, size;
	double x, y, m, n, t;
	BMP bmp = BMPInit(width, height, 8, clrUsed, palette, &absHeight, &rowSize, 
		&pixelArraySize, &offBits, &size);
	for(i=0; i<width; ++i) {
		for(j=0; j<height; ++j) {
			x = lineSubstitute(lineX, j);
			y = lineSubstitute(lineY, i);
			m = 0.0;
			n = 0.0;
			for(k=0; k<clrUsed && m*m + n*n < 4.0; ++k) {
				t = m*m - n*n + x;
				n = 2*m*n + y;
				m = t;
			}
			bmp[rowSize * i + j + offBits] = k;
		}
	}
	BMPsave(bmp, path);
}

void fractalJuliaSet(char* path, int32_t width, int32_t height, 
					uint32_t clrUsed, PALETTE palette, LINE lineX, LINE lineY, 
					double x, double y) {
	int32_t i, j, k;
	uint32_t absHeight, rowSize, pixelArraySize, offBits, size;
	double m, n, t;
	BMP bmp = BMPInit(width, height, 8, clrUsed, palette, &absHeight, &rowSize, 
		&pixelArraySize, &offBits, &size);
	for(i=0; i<width; ++i) {
		for(j=0; j<height; ++j) {
			m = lineSubstitute(lineX, j);
			n = lineSubstitute(lineY, i);
			for(k=0; k<clrUsed && m*m + n*n < 4.0; ++k) {
				t = m*m - n*n + x;
				n = 2*m*n + y;
				m = t;
			}
			bmp[rowSize * i + j + offBits] = k;
		}
	}
	BMPsave(bmp, path);
}

#ifdef __cplusplus
}
#endif

#endif
