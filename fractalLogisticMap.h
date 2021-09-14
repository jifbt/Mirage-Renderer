/* Name: fractalLogisticMap.h v0.0.0
 * Date: 2021-09-14
 * Intro: Render logistic map.
 * Update: Rename filename.
 * Note: Use OMP by defining macro _FRACTAL_USE_OMP.
 */
#ifndef _FRACTALLOGISTICMAP_H
#define _FRACTALLOGISTICMAP_H 0x000000

#include "bmpEncoder.h"
#include "bmpLine.h"

#ifdef _FRACTAL_USE_OMP
#include <omp.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void fractalFeigenbaumGraph(char* path, int32_t width, int32_t height,
					uint32_t clrUsed, PALETTE palette, LINE lineX, LINE lineY, 
					uint32_t preRepeat, uint32_t repeat) {
	int32_t i;
	uint32_t absHeight, rowSize, pixelArraySize, offBits, size;
	BMP bmp = BMPInit(width, height, 8, clrUsed, palette, &absHeight, &rowSize, 
		&pixelArraySize, &offBits, &size);
	lineReverse(lineX); 
#ifdef _FRACTAL_USE_OMP
#pragma omp parallel for
#endif
	for(i=0; i<absHeight; ++i) {
		double x = lineSubstitute(lineY, i);
		double y = 0.5;
		int32_t j, k, o;
		for(k=0; k<preRepeat; ++k) {
			y *= (1 - y) * x;
		}
		for(k=0; k<repeat; ++k) {
			y *= (1 - y) * x;
			j = lineSubstitute(lineX, y);
			if(0<=j && j<width) {
				o = rowSize * i + j + offBits;
				if(bmp[o] < clrUsed - 1) {
					++bmp[o];
				}
			}
		}
	}
	BMPsave(bmp, path);
}

#ifdef __cplusplus
}
#endif

#endif
