/* Name: fractalBarnsleyFern.h v0.0.2
 * Date: 2021-09-07
 * Intro: Render Barnsley ferns.
 * Note: Use OMP by defining macro _FRACTAL_USE_OMP.
 *		Use mt19937 by defining macro _FRACTAL_USE_MT19937
 * Update: Able to use mt19937.
 */
#ifndef _FRACTALBARNSLEYFERN_H
#define _FRACTALBARNSLEYFERN_H 0x000002

#include <time.h>
#include "bmpEncoder.h"
#include "bmpLine.h"
#include "bmpPalette.h"

#ifdef _FRACTAL_USE_OMP
#include <omp.h>
#endif

#ifdef _FRACTAL_USE_MT19937
#include "mt19937ar/mt19937ar.c"
#else
#include <stdlib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void fractalBarnsleyFern(char* path, int32_t width, int32_t height,
					uint32_t clrUsed, PALETTE palette, LINE lineX, LINE lineY,
					uint32_t repeat, uint32_t branch, uint32_t choice,
					float affine[][6], float x, float y) {
	int32_t i;
	uint32_t absHeight, rowSize, pixelArraySize, offBits, size;
	BMP bmp = BMPInit(width, height, 8, clrUsed, palette, &absHeight, &rowSize, 
		&pixelArraySize, &offBits, &size);
	lineReverse(lineX);
	lineReverse(lineY);
#ifdef _FRACTAL_USE_MT19937
	init_genrand(time(NULL));
#else
	srand(time(NULL));
#endif
#ifdef _FRACTAL_USE_OMP
#pragma omp parallel for
#endif
	for(i=0; i<branch; ++i) {
		int32_t j, m, n, o;
		float p=x, q=y, t;
		for(j=0; j<repeat; ++j) {
			m = lineSubstitute(lineY, q);
			n = lineSubstitute(lineX, p);
			if(m>=0 && m<width && n>=0 && n<absHeight) {
				o = rowSize * m + n + offBits;
				if(bmp[o] < clrUsed) {
					++bmp[o];
				}
			}
			
#ifdef _FRACTAL_USE_MT19937
			o = genrand_int32() % choice;
#else
			o = rand() % choice;
#endif
			t = affine[o][0] * p + affine[o][1] * q + affine[o][2];
			q = affine[o][3] * p + affine[o][4] * q + affine[o][5];
			p = t;
		}
	}
	BMPsave(bmp, path);
}

#ifdef __cplusplus
}
#endif

#endif
