/* Name: bmpLine_test.c v0.0.0
 * Date: 2021-08-28
 * Intro: Test bmpLine.h. Using line y=3x+5 generate by different ways
 *			and substitude x=10. The output is 35.000000 repeating 5 times.
 */
#include <stdio.h>
#include "bmpLine.h"
int main() {
	LINE line;
	line = lineSlopeIntercept(3, 5);
	printf("%lf\n", lineSubstitute(line, 10.0));
	line = lineStandard(6.0, -2.0, -10.0);
	printf("%lf\n", lineSubstitute(line, 10.0));
	line = lineTwoPoints(1.0, 8.0, 2.0, 11.0);
	printf("%lf\n", lineSubstitute(line, 10.0));
	line = lineSlopePoint(3.0, 3.0, 14.0);
	printf("%lf\n", lineSubstitute(line, 10.0));
	line = lineSlopeIntercept(1.0/3.0, -5.0/3.0);
	lineReverse(line);
	printf("%lf\n", lineSubstitute(line, 10.0));
}
