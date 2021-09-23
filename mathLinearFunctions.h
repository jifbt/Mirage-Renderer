/* Name: mathLinearFunctions.h v1.0.0
 * Date: 2021-09-19
 * Intro: Define linear functions used in fractal rendering.
 * Update: Split .h into header and source.
 * Note: Line in fractal rendering is always pixal to number coordination. 
 */
#ifndef _MATHLINEARFUNCTIONS_H
#define _MATHLINEARFUNCTIONS_H 0x010000

#include <malloc.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef double* LINE;

LINE lineNew();
void lineCopy(LINE dest, LINE src);
LINE lineSlopeIntercept(double slope, double intercept);
LINE lineStandard(double a, double b, double c);
LINE lineTwoPoints(double x0, double y0, double x1, double y1);
LINE lineSlopePoint(double slope, double x, double y);
void lineReverse(LINE line);
inline double lineSubstitute(LINE line, double x) ;

#ifdef __cplusplus
}
#endif

#endif
