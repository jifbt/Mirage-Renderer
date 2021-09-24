/* Name: fractal.c v0.0.1
 * Date: 2021-09-24
 * Intro: Render fractals.
 * Update: Functions fractalJuliaSet and fractalMandelbrotSet no longer
 		generate wrong range (0, clrUsed] but right [0, clrUsed).
 */
#include "fractal.h"
#if _FRACTAL_H != 0x000000
#error fractal.h version not supported
#endif

void fractalBarnsleyFern(char* path, int32_t width, int32_t height, uint32_t clrUsed, PALETTE palette, LINE lineX, LINE lineY, uint32_t repeat, uint32_t branch, uint32_t choice, double affine[][6], double x, double y) {
	int32_t i;
	uint32_t absHeight, rowSize, pixelArraySize, offBits, size;
	BMP bmp = BMPInit(width, height, 8, clrUsed, palette, &absHeight, &rowSize, &pixelArraySize, &offBits, &size);
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
		double p=x, q=y, t;
		for(j=0; j<repeat; ++j) {
			m = lineSubstitute(lineY, q);
			n = lineSubstitute(lineX, p);
			if(m>=0 && m<width && n>=0 && n<absHeight) {
				o = rowSize * m + n + offBits;
				/* A hack for not using critical to increase efficiency. */
				if(bmp[o] < clrUsed - 1) {
					++bmp[o];
				}
				if(bmp[o] == (uint32_t)clrUsed) {
					--bmp[o];
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

void fractalJuliaSet(char* path, int32_t width, int32_t height, uint32_t clrUsed, PALETTE palette, LINE lineX, LINE lineY, double x, double y) {
	int32_t i;
	uint32_t absHeight, rowSize, pixelArraySize, offBits, size;
	BMP bmp = BMPInit(width, height, 8, clrUsed, palette, &absHeight, &rowSize, &pixelArraySize, &offBits, &size);
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
			bmp[rowSize * i + j + offBits] = k - 1;
		}
	}
	BMPsave(bmp, path);
}

void fractalLogisticMap(char* path, int32_t width, int32_t height, uint32_t clrUsed, PALETTE palette, LINE lineX, LINE lineY, uint32_t preRepeat, uint32_t repeat) {
	int32_t i;
	uint32_t absHeight, rowSize, pixelArraySize, offBits, size;
	BMP bmp = BMPInit(width, height, 8, clrUsed, palette, &absHeight, &rowSize, &pixelArraySize, &offBits, &size);
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

void fractalMandelbrotSet(char* path, int32_t width, int32_t height, uint32_t clrUsed, PALETTE palette, LINE lineX, LINE lineY) {
	int32_t i;
	uint32_t absHeight, rowSize, pixelArraySize, offBits, size;
	BMP bmp = BMPInit(width, height, 8, clrUsed, palette, &absHeight, &rowSize, &pixelArraySize, &offBits, &size);
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
			bmp[rowSize * i + j + offBits] = k - 1;
		}
	}
	BMPsave(bmp, path);
}

