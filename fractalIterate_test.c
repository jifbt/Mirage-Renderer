/* Name: fractalIterate_test.c v0.0.0
 * Date: 2021-09-03
 * Intro: Render basic Mandelbrot and Julia Set (at point -0.4+0.6i) bitmaps.
 			See output at mandelbrotSet.bmp and juliaSet.bmp.(File is big; *.zip
			on Github.)
 */
#include "fractalIterate.h"
const int a = 16384;
int main() {
	fractalMandelbrotSet("mandelbrotSet.bmp", a, a, 119, gradWMBCFGYRK119,
		lineTwoPoints(0.0, -2, a, 2), lineTwoPoints(0.0, -2, a, 2));
	fractalJuliaSet("juliaSet.bmp", a, a, 119, gradWMBCFGYRK119,
		lineTwoPoints(0.0, -2, a, 2), lineTwoPoints(0.0, -2, a, 2), -0.4, 0.6);
	return 0;
}
