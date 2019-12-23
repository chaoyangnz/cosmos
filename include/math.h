#ifndef C_MATH_H
#define C_MATH_H

#include "compiler.h"

#define	M_E		2.7182818284590452354	/* e */
#define	M_LOG2E		1.4426950408889634074	/* log 2e */
#define	M_LOG10E	0.43429448190325182765	/* log 10e */
#define	M_LN2		0.69314718055994530942	/* log e2 */
#define	M_LN10		2.30258509299404568402	/* log e10 */
#define	M_PI		3.14159265358979323846	/* pi */
#define	M_PI_2		1.57079632679489661923	/* pi/2 */
#define	M_PI_4		0.78539816339744830962	/* pi/4 */
#define	M_1_PI		0.31830988618379067154	/* 1/pi */
#define	M_2_PI		0.63661977236758134308	/* 2/pi */
#define	M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
#define	M_SQRT2		1.41421356237309504880	/* sqrt(2) */
#define	M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */

#define	MAXFLOAT	((float)3.40282346638528860e+38)
#define HUGE_VAL	1e500			/* positive infinity */

extern int signgam;

double acos(double x) PURE;
double asin(double x) PURE;
double atan(double x) PURE;
double atan2(double y, double x) PURE;
double ceil(double x) PURE;
double cos(double x) PURE;
double cosh(double x) PURE;
double exp(double x) PURE;
double fabs(double x) PURE;
double floor(double x) PURE;
double fmod(double x, double y) PURE;
double frexp(double value, int *exp);
double ldexp(double value, int exp) PURE;
double log(double x) PURE;
double log10(double x) PURE;
double modf(double value, double *iptr);
double pow(double x, double y) PURE;
double sin(double x) PURE;
double sinh(double x) PURE;
double sqrt(double x) PURE;
double tan(double x) PURE;
double tanh(double x) PURE;

double erf(double x) PURE;
double erfc(double x) PURE;
double gamma(double x);
double hypot(double x, double y) PURE;
double j0(double x) PURE;
double j1(double x) PURE;
double jn(int n, double x) PURE;
double lgamma(double x);
double y0(double x) PURE;
double y1(double x) PURE;
double yn(int n, double x) PURE;
int isnan(double x) PURE;

double acosh(double x) PURE;
double asinh(double x) PURE;
double atanh(double x) PURE;
double cbrt(double x) PURE;
double expm1(double x) PURE;
int ilogb(double x) PURE;
double log1p(double x) PURE;
double logb(double x) PURE;
double nextafter(double x, double y) PURE;
double remainder(double x, double y) PURE;
double rint(double l) PURE;
double scalb(double x, double n) PURE;

#endif //C_MATH_H
