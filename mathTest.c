/* Name: mathTest.c v1.0.0
 * Date: 2021-09-17
 * Intro: Test math*. Using line y=3x+5 generate by different ways
 *			and substitude x=10. The output is 35.000000 repeating 5 times.
 * Update: Rename mathLinearFunctions_test.h to mathTest.c.
 */
#include <stdio.h>
#include "mathLinearFunctions.c"
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
	return 0;
}
