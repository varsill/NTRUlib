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
 Polynomial * inversePolynomialModuloNotPrime(const QuotientPolynomialRing * ring, Polynomial * p);
Polynomial * encodePolynomial(const Polynomial *m, Polynomial *h, int N, int q, int d);
Polynomial * decodePolynomial(Polynomial *e, Polynomial *f, Polynomial * f_p_inverse, int N, int p, int q, int d);
static int getPrime(int x);
static int getExponent(int x);
int * getDistinctRandomNumbers(int from, int to, int how_many);

#endif