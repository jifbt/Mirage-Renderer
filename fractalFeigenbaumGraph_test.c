/* Name: fractalFeigenbaumGraph_test.c v0.0.0
 * Date: 2021-09-08
 * Intro: Render Feigenbaum graph. See output at feigenbaumGraph.bmp.
 *		(File is big; *.zip on Github.)
 */
#include "fractalFeigenbaumGraph.h"
#include "bmpPalette.h"
const int a = 8192;
int main() {
	fractalFeigenbaumGraph("feigenbaumGraph.bmp", a, a, 256, gradWK256,
		lineTwoPoints(0, 0, a, 1), lineTwoPoints(0, 3, a, 4), 256, 1048576);
	return 0;
}
