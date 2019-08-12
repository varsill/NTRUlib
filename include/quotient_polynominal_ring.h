#ifndef _quotient_polynominal_ring_H_
#define _quotient_polynominal_ring_H_

#include "polynominal.h"



typedef enum {INTEGER, REAL} Type;


QuotientPolynominalRing * createQuotientPolynominalRing(Polynominal *, Type, int*);
void freeQuotientPolynominalRing(QuotientPolynominalRing *);



#endif
