/* Name: fractal.h v0.0.0
 * Date: 2021-09-21
 * Intro: Render fractals.
 * Update: Combine fractals into one header and one source.
 * Note: Use OMP by defining macro _FRACTAL_USE_OMP.
 */
#ifndef _FRACTAL_H
#define _FRACTAL_H 0x000000

#include <time.h>
#include "bmpEncoder.c"
#include "mathLinearFunctions.c"

#ifdef _FRACTAL_USE_OMP
#include <omp.h>
#endif

#ifdef _FRACTAL_USE_MT19937
#include "mt19937ar/mt19937ar.c"
#else
#include <stdlib.h>
#endif

#if _BMPENCODER_H<0x020100 || _BMPENCODER_H>=0x030000
#error bmpEncoder.h version not support
#elif _MATHLINEARFUNCTIONS_H<0x010000 || _MATHLINEARFUNCTIONS_H>=0x020000
#error mathLinearFunctions.h version not support
#endif

#ifdef __cplusplus
extern "C" {
#endif

void fractalBarnsleyFern	(char* path, int32_t width, int32_t height, uint32_t clrUsed, PALETTE palette, LINE lineX, LINE lineY, uint32_t repeat, uint32_t branch, uint32_t choice, double affine[][6], double x, double y);
void fractalJuliaSet		(char* path, int32_t width, int32_t height, uint32_t clrUsed, PALETTE palette, LINE lineX, LINE lineY, double x, double y);
void fractalLogisticMap		(char* path, int32_t width, int32_t height, uint32_t clrUsed, PALETTE palette, LINE lineX, LINE lineY, uint32_t preRepeat, uint32_t repeat);
void fractalMandelbrotSet	(char* path, int32_t width, int32_t height, uint32_t clrUsed, PALETTE palette, LINE lineX, LINE lineY);


#ifdef __cplusplus
}
#endif

#endif
