/* Name: mathLinearFunctions.c v1.0.0
 * Date: 2021-09-19
 * Intro: Define linear functions used in fractal rendering.
 * Update: Split .h into header and source.
 * Note: Line in fractal rendering is always pixal to number coordination. 
 */
#include "mathLinearFunctions.h"
#if _MATHLINEARFUNCTIONS_H != 0x010000
#error mathLinearFunctions.h version not support
#endif

LINE lineNew() {
	return (LINE)malloc(sizeof(double) * 2);
}

void lineCopy(LINE dest, LINE src) {
	dest[0] = src[0];
	dest[1] = src[1];
}

void lineReverse(LINE line) {
	line[0] = 1 / line[0];
	line[1] *= -line[0];
}

LINE lineSlopeIntercept(double slope, double intercept) {
	LINE line = lineNew();
	line[0] = slope;
	line[1] = intercept;
	return line;
}

LINE lineStandard(double a, double b, double c) {
	LINE line = lineNew();
	line[0] = -a / b;
	line[1] = c / b;
	return line;
}

LINE lineTwoPoints(double x0, double y0, double x1, double y1) {
	LINE line = lineNew();
	line[0] = (y1-y0) / (x1-x0);
	line[1] = (x1*y0-x0*y1) / (x1-x0);
	return line;
}

LINE lineSlopePoint(double slope, double x, double y) {
	LINE line = lineNew();
	line[0] = slope;
	line[1] = y - slope*x;
	return line;
}

inline double lineSubstitute(LINE line, double x) {
	return line[0] * x + line[1];
}
