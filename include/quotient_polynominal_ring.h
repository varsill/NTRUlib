#ifndef _quotient_polynominal_ring_H_
#define _quotient_polynominal_ring_H_

#include "polynominal.h"
#include "stdlib.h"

QuotientPolynominalRing * createQuotientPolynominalRing(Polynominal *,int, int*);
void freeQuotientPolynominalRing(QuotientPolynominalRing *);

void * my_malloc(int);
void my_free(void*);


#endif
