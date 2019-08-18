#include "quotient_polynominal_ring.h"

QuotientPolynominalRing * createQuotientPolynominalRing(Polynominal *ideal, int *error)
{
    SET_ERROR(error, OK);
    if(ideal==NULL)
    {
        SET_ERROR(error, UNITIALIZED_POLYNOMINALS);
        return NULL;
    }
    
    QuotientPolynominalRing *ring = (QuotientPolynominalRing*)malloc(sizeof(QuotientPolynominalRing));
    ring->ideal=ideal;
    return ring;
}
void freeQuotientPolynominalRing(QuotientPolynominalRing *ring)
{   
    if(ring!=NULL)freePolynominal(ring->ideal);
    free(ring);
    
}