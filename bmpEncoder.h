/* Name: bmpEncoder.h v2.0.1
 * Date: 2021-08-22
 * Intro: Tiny lib to encode BMPs. Simplified for ease and efficiency.
 * Update: Fix some fatal bugs after testing.
 */
#ifndef _BMPENCODER_H
#define _BMPENCODER_H 0x020001

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Pre-defined header, 0xff for unknown values. */
uint8_t _bmpHeader[] = (
/* (HEX)0	1	2	3	4	5	6	7	8	9	a	b	c	d	e	f */
	"\x42\x4d\xff\xff\xff\xff\x00\x00\x00\x00\xff\xff\xff\xff\x28\x00"
	"\x00\x00\xff\xff\xff\xff\xff\xff\xff\xff\x01\x00\xff\xff\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xff"
	"\xff\xff\x00\x00\x00\x00"
);

typedef uint8_t* BMP;
typedef uint32_t* PALETTE;

BMP BMPInit(int32_t width, int32_t height, uint16_t bitCount, uint32_t clrUsed, 
			PALETTE palette, uint32_t* absHeight, uint32_t* rowSize, 
			uint32_t* pixelArraySize, uint32_t* offBits, uint32_t* size) {
	if(bitCount!=1 &&bitCount!=2 && bitCount!=4 && bitCount!=8 && bitCount!=16 
		&& bitCount!=24 && bitCount!=32) return NULL;
	else if(bitCount<=8 && clrUsed==0) return NULL;
	uint32_t _absHeight = abs(height);
	uint32_t _rowSize = (bitCount * width + 31) >> 3 & ~3;
	uint32_t _pixelArraySize = _rowSize * _absHeight;
	uint32_t _offBits = 0x36 + (clrUsed << 2);
	uint32_t _size = _pixelArraySize + _offBits;
	if(absHeight != NULL) *absHeight = _absHeight;
	if(rowSize != NULL) *rowSize = _rowSize;
	if(pixelArraySize != NULL) *pixelArraySize = _pixelArraySize;
	if(offBits != NULL) *offBits = _offBits;
	if(size != NULL) *size = _size;
	BMP bmp = (BMP) malloc(_size);
	memcpy(bmp, _bmpHeader, 0x36);
	if(clrUsed) memcpy(bmp + 0x36, palette, clrUsed << 2);
	*(uint32_t*)(bmp + 0x02) = _size;
	*(uint32_t*)(bmp + 0x0a) = _offBits;
	*(int32_t*)(bmp + 0x12) = width;
	*(int32_t*)(bmp + 0x16) = height;
	*(uint16_t*)(bmp + 0x1c) = bitCount;
	*(uint32_t*)(bmp + 0x2e) = clrUsed;
	return bmp;
}

void BMPsave(BMP bmp, char* path) {
	FILE* file = fopen(path, "wb");
	fwrite(bmp, (size_t)*(uint32_t*)(bmp + 0x02), 1, file);
	fclose(file);
}

#ifdef __cplusplus
}
#endif

#endif
