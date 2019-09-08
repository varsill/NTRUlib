#ifndef _ntru_H_
#define _ntru_H_


#include <stdbool.h>
#include "config.h"
#include "polynomial.h"
#include "quotient_polynomial_ring.h"

typedef struct 
{
    Polynomial *f;
    Polynomial *h;
    Polynomial *f_p_inverse;
} KeyPackage;


KeyPackage createKey(int N, int p, int q, int d);
static Polynomial * inversePolynomialModuloNotPrime(const QuotientPolynomialRing * ring, Polynomial * p);
static int getPrime(int x);
static int getExponent(int x);

#endif