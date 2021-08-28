/* Name: bmpComplex.h v0.0.1
 * Date: 2021-08-28
 * Intro: Define complex operations used in fractal rendering.
 * Upadte: Redefine COMPLEX from array to pointer. Add function complexNew,
 *			complexConjugate and complexReciprocal.
 */
#ifndef _BMPCOMPLEX
#define _BMPCOMPLEX 0x000000

#include <malloc.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef double* COMPLEX;
COMPLEX complexNew() {
	return (COMPLEX)malloc(sizeof(double) * 2);
}
inline double complexNorm(COMPLEX u) {
	return u[0] * u[0] + u[1] * u[1];
}
inline void complexCopy(COMPLEX u, COMPLEX v) {
	u[0] = v[0];
	u[1] = v[1];
}
inline void complexAdd(COMPLEX u, COMPLEX v) {
	u[0] += v[0];
	u[1] += v[1]; 
}
inline void complexMult(COMPLEX u, COMPLEX v) {
	COMPLEX w;
	w[0] = u[0] * v[0] - u[1] * v[1];
	w[1] = u[0] * w[1] + u[1] * w[0];
	complexCopy(u, w);
}
inline void complexConjugate(COMPLEX u) {
	u[1] = -u[1];
}
inline void complexReciprocal(COMPLEX u) {
	double norm = complexNorm(u);
	u[0] /= norm;
	u[1] /= -norm;
}

#ifdef __cplusplus
}
#endif

#endif
