#ifndef _polynominal_H_
#define _polynominal_H_

#include "quotient_polynominal_ring.h"

typedef struct{

} Polynominal;

typedef struct{

}QuotientPolynominalRing;


Polynominal * createPolynominal(int,int*, ...);

void freePolynominal(Polynominal *);
_Bool comparePolynominals(QuotientPolynominalRing *, Polynominal *, Polynominal *);
Polynominal * addPolynominals(QuotientPolynominalRing *, Polynominal *, Polynominal *, int*);
Polynominal * substractPolynominals(QuotientPolynominalRing *, Polynominal *, Polynominal *, int*);
Polynominal * multiplyPolynominals(QuotientPolynominalRing *, Polynominal *, Polynominal *, int*);
Polynominal * dividePolynominals(QuotientPolynominalRing *, Polynominal *, Polynominal *, Polynominal *, int*);
Polynominal * inversePolynominal(QuotientPolynominalRing *, Polynominal *, int *);


#endif
