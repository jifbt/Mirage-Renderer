/* Name: bmpEncoder.c v2.1.0
 * Date: 2021-08-22
 * Intro: Tiny source to encode BMPs. Simplified for ease and efficiency.
 * Update: Split .hs into header and source.
 */
#include "bmpEncoder.h"
#if _BMPENCODER_H != 0x020100
#error bmpEncoder.h version not support
#endif

BMP BMPInit(int32_t width, int32_t height, uint16_t colorDepth, uint32_t clrUsed, PALETTE palette, uint32_t* absHeight, uint32_t* rowSize, uint32_t* pixelArraySize, uint32_t* offBytes, uint32_t* size) {
	if(colorDepth==0 || (colorDepth>8 && colorDepth!=16 && colorDepth!=24 && colorDepth!=32)) {
		mirageErrno = BMP_INVALID_COLOR_DEPTH;
		return NULL;
	} else if(colorDepth<=8 && clrUsed==0) {
		mirageErrno = BMP_MANDATORY_PALETTE;
		return NULL;
	}
	uint32_t _absHeight = abs(height);
	uint32_t _rowSize = (colorDepth * width + 31) >> 3 & ~3;
	uint32_t _pixelArraySize = _rowSize * _absHeight;
	uint32_t _offBytes = 0x36 + (clrUsed << 2);
	uint32_t _size = _pixelArraySize + _offBytes;
	if(absHeight != NULL) *absHeight = _absHeight;
	if(rowSize != NULL) *rowSize = _rowSize;
	if(pixelArraySize != NULL) *pixelArraySize = _pixelArraySize;
	if(offBytes != NULL) *offBytes = _offBytes;
	if(size != NULL) *size = _size;
	BMP bmp = (BMP) malloc(_size);
	memcpy(bmp, _bmpHeader, 0x36);
	if(clrUsed) memcpy(bmp + 0x36, palette, clrUsed << 2);
	*(uint32_t*)(bmp + 0x02) = _size;
	*(uint32_t*)(bmp + 0x0a) = _offBytes;
	*(int32_t*)(bmp + 0x12) = width;
	*(int32_t*)(bmp + 0x16) = height;
	*(uint16_t*)(bmp + 0x1c) = colorDepth;
	*(uint32_t*)(bmp + 0x2e) = clrUsed;
	return bmp;
}

void BMPsave(BMP bmp, const char* path) {
	FILE* file = fopen(path, "wb");
	fwrite(bmp, (size_t)*(uint32_t*)(bmp + 0x02), 1, file);
	fclose(file);
}
