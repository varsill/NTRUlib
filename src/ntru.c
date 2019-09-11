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


Polynomial * encodePolynomial(const Polynomial *m, Polynomial *h, int N, int q, int d)
{

    Polynomial * h_cp=copyPolynomial(h);
    fillPolynomialWithLeadingZeros(h_cp, N);
    Polynomial * h_prim=createSpecialPolynomial(DOUBLE, h_cp);
    freePolynomial(h_cp);
    int *k = getDistinctRandomNumbers(1, N, d);
    QuotientPolynomialRing * ring = createQuotientPolynomialRing(NULL, q, NULL);
    Polynomial * e=m;
    for(int i=0; i<d; i++)
    {
        Polynomial *buffer = createSpecialPolynomial(EMPTY, N, INTEGER);
        for(int j=0; j<buffer->degree; j++)buffer->coefficients[buffer->degree-1-j]=h_prim->coefficients[h_prim->degree-(N+j-k[i])];
        Polynomial *e_buff = addPolynomials(ring, e, buffer, NULL);
        if(e!=m)freePolynomial(e);
        freePolynomial(buffer);
        e=e_buff;
    }
    freeQuotientPolynomialRing(ring);
    freePolynomial(h_prim);
    return e;

}

Polynomial * decodePolynomial(Polynomial *e, Polynomial *f, Polynomial * f_p_inverse, int N, int p, int q, int d)
{
    //we assume, that argument d of this function is equal to the argument d of the function createKey() - which means, that number of ones in binary polynomial f is equal to d
    int * u = (int*)malloc(d*sizeof(int));  
    Rational one = createRational(1, 1);
    int j=0;
    for(int i=0; i<f->degree; i++)
    {
        if(compareRationals(&f->coefficients[i], &one)==true)
        {
           
            u[j]=i;
            j++;
        }
    }

   
 
    //probably floor xD
    int s = floor(q/2.0+d*(p-1)+d*d*d*1.0/N);
    int t = q*floor((d*(p-1)+d*d*d/N)*1.0/q);
    s=mod(s, q);
    t=mod(t, p);
    Polynomial * v = f_p_inverse;

    Polynomial * v_cp = copyPolynomial(v);
    Polynomial * e_cp = copyPolynomial(e);
    fillPolynomialWithLeadingZeros(v_cp, N);
    fillPolynomialWithLeadingZeros(e_cp, N);
    Polynomial * v_prim = createSpecialPolynomial(DOUBLE, v_cp);
    Polynomial * e_prim = createSpecialPolynomial(DOUBLE, e_cp);
    freePolynomial(v_cp);
    freePolynomial(e_cp);
    QuotientPolynomialRing * ring_q = createQuotientPolynomialRing(NULL, q, NULL);
    Polynomial * a = createSpecialPolynomial(ZERO, N, INTEGER);

    
      
    for(int i=0; i<d; i++)
    {
        Polynomial *buffer = createSpecialPolynomial(EMPTY, N, INTEGER);
       
        for(int j=0; j<buffer->degree; j++)buffer->coefficients[buffer->degree-1-j]=e_prim->coefficients[e_prim->degree-1-(N+j-1-u[i])];
        
        
        Polynomial *a_buff = addPolynomials(ring_q, a, buffer, NULL); 
        freePolynomial(a);
        freePolynomial(buffer);
        
        a=a_buff; 
     
    }

    Polynomial * b = createSpecialPolynomial(EMPTY, N, INTEGER);
    fillPolynomialWithLeadingZeros(a, N);
    for(int i=0; i<a->degree; i++)
    {
        if(toInt(&a->coefficients[i])<s)b->coefficients[i]=createRational(toInt(&a->coefficients[i])+t, 1);
        else b->coefficients[i]=createRational(toInt(&a->coefficients[i])+t-q, 1);   
    }

    QuotientPolynomialRing * ring_p = createQuotientPolynomialRing(NULL, p, NULL);
    Polynomial *n=createZeroPolynomial(INTEGER, NULL);
    fillPolynomialWithLeadingZeros(b, N);
    printPolynomial(v_prim, "V:");
    printPolynomial(b, "b: ");
    for(int i=0; i<N; i++)
    {

        Polynomial * l = createSpecialPolynomial(EMPTY, N, INTEGER);
        for(int j=0; j<l->degree; j++)l->coefficients[l->degree-1-j]=v_prim->coefficients[v_prim->degree-(N+j-i)];
        printPolynomial(l, "l: ");
        multiplyPolynomialByConstant(l, &b->coefficients[b->degree-1-i], ring_p);
        Polynomial * n_buff = addPolynomials(ring_p, l, n, NULL);
        freePolynomial(n);
        freePolynomial(l);
        n=n_buff; 
         printPolynomial(n, "n: ");  
    //    printPolynomial(n);
    } 

    freeQuotientPolynomialRing(ring_p);freeQuotientPolynomialRing(ring_q);
    freePolynomial(v_prim);freePolynomial(e_prim);freePolynomial(b);freePolynomial(a);
    return n;

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


 int* getDistinctRandomNumbers(int from, int to, int how_many)
{
    int n  = to-from+1;
    if(how_many>n)return NULL;//cannot choose distinct numbers
    bool * tab = (bool*)malloc(n*sizeof(bool));
    int * result = malloc(how_many*sizeof(int));
    for(int i=0; i<n; i++)tab[i]=false;
    while(how_many>0)
    {
        int x = rand()%n;
      
        if(tab[x]==false)
        {
            tab[x]=true;
            how_many--;
        }
    }
    int j=0;
    
    for(int i=0; i<n; i++)
    {
        if(tab[i]==true)
        {
             
            result[j]=from+i;
            j++;
        }
    }

    free(tab);
    return result;

   

}