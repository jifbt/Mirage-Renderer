/* Name: fractalIterate.h v0.0.0
 * Date: 2021-09-03
 * Intro: Render Mandelbrot and Julia sets.
 * Note: Use OMP by defining the macro _FRACTAL_USE_OMP.
 */
#ifndef _FRACTALITERATE_H
#define _FRACTALITERATE_H 0x000000

#include <assert.h>
#include "bmpEncoder.h"
#include "bmpLine.h"
#include "bmpPalette.h"

#ifdef _FRACTAL_USE_OMP
#include <omp.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void fractalMandelbrotSet(char* path, int32_t width, int32_t height, 
					uint32_t clrUsed, PALETTE palette, LINE lineX, LINE lineY) {
	int32_t i;
	uint32_t absHeight, rowSize, pixelArraySize, offBits, size;
	BMP bmp = BMPInit(width, height, 8, clrUsed, palette, &absHeight, &rowSize, 
		&pixelArraySize, &offBits, &size);
#ifdef _FRACTAL_USE_OMP
#pragma omp parallel for
#endif
	for(i=0; i<width; ++i) {
		int32_t j, k;
		for(j=0; j<height; ++j) {
			double x = lineSubstitute(lineX, j);
			double y = lineSubstitute(lineY, i);
			double m = 0.0;
			double n = 0.0;
			double t;
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
	int32_t i;
	uint32_t absHeight, rowSize, pixelArraySize, offBits, size;
	BMP bmp = BMPInit(width, height, 8, clrUsed, palette, &absHeight, &rowSize, 
		&pixelArraySize, &offBits, &size);
#ifdef _FRACTAL_USE_OMP
#pragma omp parallel for
#endif
	for(i=0; i<width; ++i) {
		int32_t j, k;
		for(j=0; j<height; ++j) {
			double m = lineSubstitute(lineX, j);
			double n = lineSubstitute(lineY, i);
			double t;
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
