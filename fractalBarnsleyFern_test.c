/* Name: fractalBarnsleyFern_test.c v0.0.0
 * Date: 2021-09-03
 * Intro: Render basic Mandelbrot and Julia Set (at point -0.4+0.6i) bitmaps.
 			See output at mandelbrotSet.bmp and juliaSet.bmp.(File is big; *.zip
			on Github.)
 */
#include "fractalBarnsleyFern.h"
const int a = 16384;
double affine[][6] = {
	{-0.4612054658106728, -0.18421622013526684, 0.8200018614245714,
	0.15062308605687624, 0.41509321981152447, -0.5373931075075806},
	{0.26327130338062843, 0.5142767793873098, -0.8317557319488103,
	-0.30130288141285844, -0.9472499158717338, 0.14965908236378955},
	{0.7567452477825529, 0.11446012746460865, -0.9593268923020173,
	-0.3906129343789404, -0.4944958073044887, 0.8444025798579378},
	{0.5859588616172846, -0.24440463574371707, 0.4884664320542753,
	0.21812280807019113, 0.9922412572329409, -0.027338667080179624}
};
uint32_t _gradWK2[] = {0xffffff, 0x000000};
int main() {
	fractalBarnsleyFern("barnsleyFern.bmp", a, a, 2, _gradWK2,
		lineTwoPoints(0.0, -1, a, 1), lineTwoPoints(0.0, -1, a, 1), 1000000000, 
		4, affine, 0, 0);
	return 0;
}
