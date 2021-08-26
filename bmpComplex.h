/* Name: bmpComplex.h v0.0.0
 * Date: 2021-08-26
 * Intro: Define complex operations used in fractal rendering.
 */
#ifndef _BMPCOMPLEX
#define _BMPCOMPLEX 0x000000

#ifdef __cplusplus
extern "C" {
#endif

typedef double COMPLEX[2];
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

#ifdef __cplusplus
}
#endif

#endif
