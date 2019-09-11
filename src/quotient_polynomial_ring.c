#include "quotient_polynomial_ring.h"
extern int elements_allocated;
QuotientPolynomialRing * createQuotientPolynomialRing(Polynomial *ideal, int q, int *error)
{
    SET_ERROR(error, OK);

    
    QuotientPolynomialRing *ring = (QuotientPolynomialRing*)malloc(sizeof(QuotientPolynomialRing));
    ring->ideal=ideal;
    ring->q=q;
    return ring;
}
void freeQuotientPolynomialRing(QuotientPolynomialRing *ring)
{   
   
    if(ring==NULL)return;
    
    freePolynomial(ring->ideal);
    free(ring);
    
}

