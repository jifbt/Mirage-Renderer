/* Name: fractalIterate_test.c v0.0.0
 * Date: 2021-09-03
 * Intro: 
 */
#include "fractalIterate.h"
const int a = 16384;
int main() {
	fractalMandelbrotSet("mandelbrotSet.bmp", a, a, 119, gradWMBCFGYRK119,
		lineTwoPoints(0.0, -2, a, 2), lineTwoPoints(0.0, -2, a, 2));
	fractalJuliaSet("juliaSet.bmp", a, a, 119, gradWMBCFGYRK119,
		lineTwoPoints(0.0, -2, a, 2), lineTwoPoints(0.0, -2, a, 2), -0.4, 0.6);
}
