#ifndef _quotient_polynomial_ring_H_
#define _quotient_polynomial_ring_H_

#include "polynomial.h"
#include "stdlib.h"
#include "config.h"
QuotientPolynomialRing * createQuotientPolynomialRing(Polynomial *,int, int*);
void freeQuotientPolynomialRing(QuotientPolynomialRing *);




#endif
