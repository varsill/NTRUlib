#include "quotient_polynominal_ring.h"

QuotientPolynominalRing * createQuotientPolynominalRing(Polynominal *ideal, int q, int *error)
{
    SET_ERROR(error, OK);

    
    QuotientPolynominalRing *ring = (QuotientPolynominalRing*)malloc(sizeof(QuotientPolynominalRing));
    ring->ideal=ideal;
    ring->q=q;
    return ring;
}
void freeQuotientPolynominalRing(QuotientPolynominalRing *ring)
{   
    if(ring!=NULL)freePolynominal(ring->ideal);
    free(ring);
    
}