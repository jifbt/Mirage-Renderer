/* Name: fractalBarnsleyFern.h v0.0.0
 * Date: 2021-09-03
 * Intro: Render Barnsley ferns.
 * Note: Use OMP by defining the macro _FRACTAL_USE_OMP.
 */
#ifndef _FRACTALBARNSLEYFERN_H
#define _FRACTALBARNSLEYFERN_H 0x000000

#include <stdlib.h>
#include "bmpEncoder.h"
#include "bmpLine.h"
#include "bmpPalette.h"

#ifdef _FRACTAL_USE_OMP
#include <omp.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void fractalBarnsleyFern(char* path, int32_t width, int32_t height, 
					uint32_t clrUsed, PALETTE palette, LINE lineX, LINE lineY, 
					uint32_t repeat, uint32_t choice, double affine[][6], 
					double x, double y) {
	int32_t i, j, k;
	double t;
	uint32_t absHeight, rowSize, pixelArraySize, offBits, size;
	BMP bmp = BMPInit(width, height, 8, clrUsed, palette, &absHeight, &rowSize, 
		&pixelArraySize, &offBits, &size);
	lineReverse(lineX);
	lineReverse(lineY);
	while(repeat--) {
		i = (int32_t) lineSubstitute(lineX, x);
		j = (int32_t) lineSubstitute(lineY, y);
		if(i>=0 && i<width && j>=0 && j<absHeight) {
			k = rowSize * i + j + offBits;
			if(bmp[k] < clrUsed) {
				++bmp[k];
			}
		}
		i = rand() % choice;
		t = affine[i][0] * x +  affine[i][1] * y + affine[i][2];
		y = affine[i][3] * x +  affine[i][4] * y + affine[i][5];
		x = t;
	}
	BMPsave(bmp, path);
}

#ifdef __cplusplus
}
#endif

#endif
