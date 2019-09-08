#include "ntru.h"



KeyPackage createKey(int N, int p, int q, int d)
{
    bool further;
    QuotientPolynomialRing * ring_p = createQuotientPolynomialRing(createSpecialPolynomial(SIMPLE, N), p , NULL);
    QuotientPolynomialRing * ring_q = createQuotientPolynomialRing(createSpecialPolynomial(SIMPLE, N), q , NULL);
    Polynomial *g = createRandomPolynomial(BINARY, N, d);
    Polynomial *f;
    Polynomial *f_p_inverse;
    Polynomial *f_q_inverse;
  
    do
    {
        further=false;
       
        f = createRandomPolynomial(BINARY, N,d);
        
        f_p_inverse = inversePolynomialModuloNotPrime(ring_p, f);
       
        f_q_inverse = inversePolynomialModuloNotPrime(ring_q, f);
         
      //  printPolynomial(f, "f: ");
     //   printPolynomial(f_p_inverse, "f_p_inverse: ");
      //  printPolynomial(f_q_inverse, "f_q_inverse: ");
       // pause();
        if(f_p_inverse==NULL || f_q_inverse==NULL)
        {
            
            freePolynomial(f);
            
            freePolynomial(f_p_inverse);
            freePolynomial(f_q_inverse);
            further=true;
            
        }
      
    }while(further);
 
    Polynomial * F = multiplyPolynomials(ring_p, f, g, NULL);//czy multiply liczy modulo polynomial?!
    QuotientPolynomialRing * ring_p_without_poly = createQuotientPolynomialRing(NULL, p, NULL);
    QuotientPolynomialRing * ring_q_without_poly = createQuotientPolynomialRing(NULL, q, NULL);
    Rational minus_one = createRational(-1, 1);
    multiplyPolynomialByConstant(F, &minus_one, ring_p_without_poly);
    Polynomial * h_buf = multiplyPolynomials(ring_q, F, f_q_inverse, NULL);
    Polynomial * h = addPolynomials(ring_q_without_poly, h_buf, g, NULL);

	Polynomial * r = multiplyPolynomials(ring_q, f, f_q_inverse, NULL);
	//printPolynomial(r,"WINNO BYC 1:");

    freePolynomial(r);


    freeQuotientPolynomialRing(ring_p);freeQuotientPolynomialRing(ring_q);
    freeQuotientPolynomialRing(ring_p_without_poly);freeQuotientPolynomialRing(ring_q_without_poly);
    freePolynomial(g);
    freePolynomial(f_q_inverse);
    freePolynomial(h_buf);
    freePolynomial(F);
    KeyPackage result = {f, h, f_p_inverse};
    return result;
    
}


static Polynomial * inversePolynomialModuloNotPrime(const QuotientPolynomialRing * ring, Polynomial * a)
{
    
    int p = getPrime(ring->q);
    int e = getExponent(ring->q);
 
    QuotientPolynomialRing * ring_p = createQuotientPolynomialRing(copyPolynomial(ring->ideal), p, NULL);
    Polynomial * b = inversePolynomial(ring_p, a);
   if(b==NULL){
       freeQuotientPolynomialRing(ring_p);   
       return NULL;
   }
   /* 
    int n=p;
    while(n<=e)
    {  
        ring_p->q=pow(p, n);
   
        Polynomial * buffer = multiplyPolynomials(ring_p, b, b, NULL);
        Polynomial * buffer2 = multiplyPolynomials(ring_p, a, buffer, NULL);
        Rational p_rat = createRational(p, 1);
       multiplyPolynomialByConstant(b, &p_rat, ring_p); 
        Polynomial * buffer3=substractPolynomials(ring_p, b, buffer2, NULL);
 
        freePolynomial(b); b=buffer3;
        freePolynomial(buffer);freePolynomial(buffer2);
        n=n*p;
    }
   */

    int v = p;
    Polynomial * p_poly =createPolynomial(INTEGER, NULL, NULL, p);
    while(v<ring->q)
    {
        v=v*p;
        ring_p->q=v;
        Polynomial *tmp = multiplyPolynomials(ring_p, a, b, NULL);
        
        Polynomial *tmp2 = substractPolynomials(ring_p,p_poly, tmp, NULL);
         Polynomial *tmp3 = multiplyPolynomials(ring_p, tmp2, b, NULL);
         freePolynomial(b);
         freePolynomial(tmp);
         freePolynomial(tmp2);
         b=tmp3;
    }
    freePolynomial(p_poly);
    moduloRing(&b, ring);
    freeQuotientPolynomialRing(ring_p);
    return b;
}

static int getPrime(int x)
{
    for(int i=2; i<=x; i++)
    {
        if(x%i==0)return i;
    }
    return -1;
}

static int getExponent(int x)
{
    int r = getPrime(x);
    if(r==-1)return -1; 
    int i=0;
    while(x>1)
    {
        i++;
        x=x/r;
    }
    return i;
}