#ifndef _quotient_polynominal_ring_H_
#define _quotient_polynominal_ring_H_

#include "polynominal.h"
#include "stdlib.h"

QuotientPolynominalRing * createQuotientPolynominalRing(Polynominal *, int*);
void freeQuotientPolynominalRing(QuotientPolynominalRing *);



#endif
