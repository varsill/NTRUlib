#include "polynomial.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "quotient_polynomial_ring.h"


Polynomial * _createPolynomial(unsigned int _degree, Type _type,QuotientPolynomialRing* ring, int* error,  ...)
{
    SET_ERROR(error, OK);
    Polynomial *p = (Polynomial*) malloc(sizeof(Polynomial));
    p->degree=_degree;
    p->type=_type;
    p->coefficients=(float*)malloc(_degree*sizeof(float));
    p->coefficients[0]=-12;
    va_list coefficients_list;
   
    va_start(coefficients_list, error);
    if(_degree>0)
    {
        if(_type==REAL)
        {
            double b = va_arg(coefficients_list, double);
        
            if(b==0)SET_ERROR(error, WRONG_POLYNOMINAL_COEFFICIENTS);
            p->coefficients[_degree-1]=b;
            for(int i=1; i<_degree; i++) p->coefficients[_degree-i-1]=va_arg(coefficients_list, double);
           
        }
        else if(_type==INTEGER)
        {
            int b = va_arg(coefficients_list, int);
        
            if(b==0)SET_ERROR(error, WRONG_POLYNOMINAL_COEFFICIENTS);
            p->coefficients[_degree-1]=b;
            for(int i=1; i<_degree; i++)p->coefficients[_degree-i-1]=va_arg(coefficients_list, int);
            
            
        }
    }   
    va_end(coefficients_list);
    repairPolynomial(p);
    if(isPolynomialValid(p, true)==false)SET_ERROR(error, WRONG_POLYNOMINAL_COEFFICIENTS);
    moduloRing(&p, ring);
    return p;

}


Polynomial * createZeroPolynomial(Type _type, int* error)
{
    SET_ERROR(error, OK);
    Polynomial *p = (Polynomial*) malloc(sizeof(Polynomial));
    p->degree=0;
    p->type=_type;
    p->coefficients=NULL;
    return p;
}


void freePolynomial(Polynomial * p)
{
    if(p==NULL)return;
    if(p->coefficients!=NULL) free(p->coefficients);
    free(p);
    
}


bool comparePolynomials(const QuotientPolynomialRing *ring,const Polynomial *p1, const Polynomial *p2, int* error)
{
    SET_ERROR(error, OK);
    if(p1==NULL || p2==NULL)
    {
        SET_ERROR(error, UNITIALIZED_POLYNOMINALS);
        return false;   
    }
    
    if(ring==NULL)
    {
        if(p1->degree != p2->degree)return false;    
        for(int i=0; i<p1->degree; i++) if(p1->coefficients[i] != p2->coefficients[i]) return false;    
        return true;
    }

    Polynomial rest1;
    Polynomial rest2;
    if(ring->ideal!=NULL)
    {
        dividePolynomials(NULL, p1, ring->ideal, &rest1, NULL);
        dividePolynomials(NULL, p2, ring->ideal, &rest2, NULL);
        moduloInteger(&rest1, ring->q, NULL);
        moduloInteger(&rest2, ring->q, NULL); 
        return comparePolynomials(NULL,&rest1, &rest2, NULL);
    }
   
    if(ring->q>0 && p1->type==INTEGER && p2->type == INTEGER){
        for(int i=0; i<p1->degree; i++) if((int)p1->coefficients[i]%ring->q != (int)p2->coefficients[i]%ring->q) return false;   
        return true;
    }
    else 
    {
        SET_ERROR(error, WRONG_POLYNOMINAL_COEFFICIENTS);
        return false;
    }
    
}


Polynomial * addPolynomials(const QuotientPolynomialRing * ring, const Polynomial * p1,const Polynomial * p2, int* error)
{
    SET_ERROR(error, OK);
    if(p1==NULL || p2==NULL)
    {
        SET_ERROR(error,  UNITIALIZED_POLYNOMINALS);
        return NULL;   
    }

    unsigned int smaller_degree;
    Polynomial * result = (Polynomial*)malloc(sizeof(Polynomial));
   
    if(p1->type==INTEGER && p2->type==INTEGER) result->type=INTEGER;
    else result->type=REAL;
   
    if(p1->degree<=p2->degree) 
    {
        smaller_degree=p1->degree;
        result->degree=p2->degree;
        result->coefficients=(float*)malloc(p2->degree*sizeof(float));
        for(int i=0; i<result->degree; i++) result->coefficients[i]=p2->coefficients[i];
        for(int i=smaller_degree-1; i>=0; i--) result->coefficients[i]+=p1->coefficients[i];
    }
    else 
    {
        smaller_degree=p2->degree;
        result->degree=p1->degree;
        result->coefficients=(float*)malloc(p1->degree*sizeof(float));
        for(int i=0; i<result->degree; i++) result->coefficients[i]=p1->coefficients[i];
        for(int i=smaller_degree-1; i>=0; i--) result->coefficients[i]+=p2->coefficients[i];
    }

    if(ring!=NULL)
    {   
       moduloRing(&result, ring);
        
    }
    repairPolynomial(result);
    return result;
    
}


Polynomial * substractPolynomials(const QuotientPolynomialRing *ring, const Polynomial *p1, const Polynomial *p2, int *error)
{
     
   SET_ERROR(error, OK);
    if(p1==NULL || p2==NULL)
    {
        SET_ERROR(error,  UNITIALIZED_POLYNOMINALS);
        return NULL;   
    }

    unsigned int smaller_degree;
    Polynomial * result = (Polynomial*)malloc(sizeof(Polynomial));
   
    if(p1->type==INTEGER && p2->type==INTEGER) result->type=INTEGER;
    else result->type=REAL;
   
    if(p1->degree<=p2->degree) 
    {
        smaller_degree=p1->degree;
        result->degree=p2->degree;
        result->coefficients=(float*)malloc(p2->degree*sizeof(float));
        for(int i=0; i<result->degree; i++) result->coefficients[i]=p2->coefficients[i]*(-1.0);
        for(int i=smaller_degree-1; i>=0; i--) result->coefficients[i]+=p1->coefficients[i];
    }
    else 
    {
        smaller_degree=p2->degree;
        result->degree=p1->degree;
        result->coefficients=(float*)malloc(p1->degree*sizeof(float));
        for(int i=0; i<result->degree; i++) result->coefficients[i]=p1->coefficients[i];
        for(int i=smaller_degree-1; i>=0; i--) result->coefficients[i]-=p2->coefficients[i];
    }

    if(ring!=NULL)
    {   
        moduloRing(&result, ring);
    }
    repairPolynomial(result);
   
    return result;

}


Polynomial * multiplyPolynomials(const QuotientPolynomialRing * ring, const Polynomial *p1, const Polynomial *p2, int *error)
{
    SET_ERROR(error, OK);
    if(p1==NULL || p2==NULL)
    {
        SET_ERROR(error, UNITIALIZED_POLYNOMINALS);
        return NULL;   
    }
    if(p1->degree==0||p2->degree==0)return createZeroPolynomial(INTEGER, NULL); //DO NAPRAWY
    Polynomial *result=(Polynomial*)malloc(sizeof(Polynomial));
    result->degree=p1->degree+p2->degree-1;
    result->coefficients=(float*)malloc((result->degree)*sizeof(float));
    if(p1->type==INTEGER && p2->type==INTEGER) result->type=INTEGER;
    else result->type=REAL;
    
    for(int k=0; k<result->degree; k++)
    {
        result->coefficients[k]=0;
 //       for(int i=MAX((k-p2->degree+1), 0); i<p1->degree; i++)
        for(int i=0; i<=k; i++)
        {
            result->coefficients[k]+=(p1->coefficients[i]*p2->coefficients[k-i]);
        }
    }
  // printPolynomial(result, "PRZED MODULO:");
    moduloRing(&result, ring);
   // printPolynomial(result, "PO MODULO:");
   // repairPolynomial(result);
    return result;

}


void multiplyPolynomialByConstant(Polynomial *poly, float c, QuotientPolynomialRing* ring)
{
    for(int i=0; i<poly->degree; i++)
    {
        poly->coefficients[i]*=c;
    }
    if(ring==NULL)return;
    moduloInteger(poly, ring->q, NULL);
}


Polynomial * dividePolynomials(const QuotientPolynomialRing *ring, const Polynomial *p1, const Polynomial *p2, Polynomial *rest, int *error)
{
    
    SET_ERROR(error, OK);
    if(p1==NULL || p2==NULL) 
    {
        SET_ERROR(error,UNITIALIZED_POLYNOMINALS);
        return NULL;   
    }
    Polynomial *result = (Polynomial*)malloc(sizeof(Polynomial));
     
    if(p1->type==INTEGER && p2->type==INTEGER) result->type=INTEGER;
    else result->type=REAL;
   
    result->degree=p1->degree-p2->degree+1;
    result->coefficients=NULL;
    printf("STOPIEN: %d \n", result->degree);
    if(result->degree>0)
    {
        
    //   printf("STOPIEN: %d \n", result->degree);fflush(stdout);
        result->coefficients=(float*)malloc(sizeof(float)*result->degree);
        
    }
    else
    {
        Polynomial *result_buf=createZeroPolynomial(result->type, NULL);
        freePolynomial(result);
        result=result_buf; 
        
    } 
  /*  
    if(rest==NULL)
    {
        rest=(Polynomial*)malloc(sizeof(Polynomial));
        rest->coefficients=NULL;
    }
    if(rest->coefficients==NULL)rest->coefficients=(float*)malloc(sizeof(float)*(p2->degree-1));
    rest->degree=result->degree;
    rest->type=result->type;
*/
    bool save_rest;
    if(rest==NULL)
    {
        save_rest=false;
    }
    else
    {   
        save_rest=true;
        
    }
    
    Polynomial *bufor = (Polynomial*)malloc(sizeof(Polynomial));
    bufor->degree=p1->degree;
    bufor->type=p1->type;
    bufor->coefficients=(float*)malloc(sizeof(float)*bufor->degree);
    
    memcpy(bufor->coefficients, p1->coefficients, bufor->degree*sizeof(float));
     
    if(ring==NULL || ring->q<=0)//division in Q[x] polynomials ring
    {
        
        for(int i=bufor->degree-1; i>=0; i--)
        {
            
            if(i<p2->degree-1)break;
            result->coefficients[i-p2->degree+1]=bufor->coefficients[i]/p2->coefficients[p2->degree-1];
            for(int j=0; j<p2->degree; j++)    
            {
                bufor->coefficients[j+(i-p2->degree+1)]-=result->coefficients[i-p2->degree+1]*p2->coefficients[j];
            }
        }
          
    
    }
    else//division in Z_n[x] polynomials ring, where n is ring->q
    {
          
        for(int i=bufor->degree-1; i>=0; i--)
        { 
        
            if(i<p2->degree-1)break; 
        // printf("%d %d ", i, p2->degree);
            result->coefficients[i-p2->degree+1]=divideInteger(bufor->coefficients[i], p2->coefficients[p2->degree-1], ring->q);
            for(int j=0; j<p2->degree; j++)    
            {
                bufor->coefficients[j+(i-p2->degree+1)]-=mod((result->coefficients[i-p2->degree+1]*p2->coefficients[j]), ring->q);
            }
        }
    }
    
    if(save_rest==true)
    {
        
        rest->degree=bufor->degree;
        rest->type=bufor->type;
        if(rest->coefficients==NULL)rest->coefficients=(float*)malloc(sizeof(float)*rest->degree);
        memcpy(rest->coefficients, bufor->coefficients, bufor->degree*sizeof(float));
   //     repairPolynomial(rest);
     
        moduloRing(&rest, ring);
          
    }
   
    freePolynomial(bufor);
  
    moduloRing(&result, ring);
    
   // repairPolynomial(result);
    return result;

}


void moduloPolynomial(Polynomial ** divident,const Polynomial * divisor, int* error)
{
    SET_ERROR(error, OK);
    if(divident==NULL)SET_ERROR(error, UNITIALIZED_POLYNOMINALS);
    if(*divident==NULL || divisor==NULL)
    {
        SET_ERROR(error, UNITIALIZED_POLYNOMINALS);
        return;   
    }
    Polynomial * rest;
   
    rest=(Polynomial*)malloc(sizeof(Polynomial));
    rest->coefficients=(float*)malloc(sizeof(float)*(divisor->degree-1));
    
    rest->degree=divisor->degree-1;
    
    rest->type=(*divident)->type;
    Polynomial * garbage = dividePolynomials(NULL, *divident, divisor, rest, error);
    freePolynomial(*divident);
    freePolynomial(garbage);
    *divident=rest;
    rest=NULL;
    repairPolynomial(*divident);
}


Polynomial* extendedEuclid(const QuotientPolynomialRing* ring, const Polynomial *a,const Polynomial *b, Polynomial **u_ref, Polynomial **v_ref)
{
  //pause();
   
    Polynomial *r0 = copyPolynomial(a);Polynomial *r1=copyPolynomial(b);  
    Polynomial * s0= createPolynomial(INTEGER,ring, NULL, 1); Polynomial *s1=createZeroPolynomial(INTEGER, NULL);
    Polynomial *t0=createZeroPolynomial(INTEGER, NULL); Polynomial * t1= createPolynomial(INTEGER, ring, NULL, 1);
    Polynomial *zero = createZeroPolynomial(INTEGER, NULL);
    Polynomial *r2, *s2, *t2, *x, *q;
    r2=s2=t2=x=q=NULL;
   
    while(comparePolynomials(NULL, r1, zero, NULL)==false)
    {
        //  printf("elo");fflush(stdout);
       // pause();
        q = dividePolynomials(ring, r0, r1,NULL, NULL);
       
        //pause();
      //  printf("cotam");fflush(stdout);
        x = multiplyPolynomials(ring, q, r1, NULL); 
        r2=substractPolynomials(ring, r0,x, NULL);
        printPolynomial(r0, "r0 ");
        printPolynomial(r1, "r1 ");
        printPolynomial(r2, "r2 ");
        printPolynomial(q, "q ");
        printPolynomial(x, "x ");
        freePolynomial(x);

        x = multiplyPolynomials(ring, q, s1, NULL);
        s2=substractPolynomials(ring, s0,x, NULL);
        freePolynomial(x);

        x = multiplyPolynomials(ring, q, t1, NULL);
        t2=substractPolynomials(ring, t0,x, NULL);
        freePolynomial(x);
        
        freePolynomial(q);
        freePolynomial(r0);freePolynomial(s0);freePolynomial(t0);
        r0=r1;s0=s1;t0=t1;
        r1=r2;s1=s2;t1=t2;
        
    }

   
   

    freePolynomial(r1);freePolynomial(s1);freePolynomial(t1);
   // freePolynomial(r2);freePolynomial(s2);freePolynomial(t2);
    freePolynomial(zero);
    //printf("%d", gcdOfPolynomialCoefficients(r0));
    float inverse = inverseOfNumber(r0->coefficients[r0->degree-1], ring);
    multiplyPolynomialByConstant(r0,inverse, ring);
    multiplyPolynomialByConstant(s0,inverse, ring);
    multiplyPolynomialByConstant(t0,inverse, ring);
    
    *u_ref=s0;
    *v_ref=t0;
    return r0;
}



Polynomial * invertPolynomial(const QuotientPolynomialRing* ring, Polynomial* poly)
{
    Polynomial *one = createPolynomial(INTEGER, NULL, NULL, 1);
    Polynomial * a;
    Polynomial * b;
    
    Polynomial *gcd = extendedEuclid(ring,poly, ring->ideal, &a, &b);
//   printPolynomial(gcd, "gcd: ");
    if(comparePolynomials(NULL, gcd, one,NULL)!=true)return NULL;//Polynomials are not coprime - poly inversion does not exist
    
    freePolynomial(gcd);
    freePolynomial(one);
    freePolynomial(b);
   // freePolynomial(a);
   // printPolynomial(a, "a ");
   // printf("%d ", (int)a);fflush(stdout);
    return a;

}


void _printPolynomialWithExtraMessage(const Polynomial* poly, const char* text)
{
    if(poly==NULL) 
    {
        printf(text);
        printf("NO_POLY\n");
        fflush(stdout);
        return;
    }
    printf(text);
    for(int i=poly->degree-1; i>=0; i--)
    {
        printf("%f ",poly->coefficients[i]);        
    }
    printf("\n");
    fflush(stdout);
}


void _printPolynomial(const Polynomial * poly)
{
    _printPolynomialWithExtraMessage(poly, "");
}



static bool isPolynomialValid(Polynomial *p, bool check_type)
{
    if(p->coefficients[p->degree-1]==0) return false;
    if(check_type && p->type==INTEGER)
    {
        for(int i=0; i<p->degree; i++)
        {
            if(p->coefficients[i] != (int)p->coefficients[i])return false;
        }
    }
    return true;

}


static void moduloRing(Polynomial **poly, const QuotientPolynomialRing *ring)
{
   
    if(ring==NULL) 
    {
       
        return;
    }
   // moduloPolynomial(poly, ring->ideal, NULL);
  //  pause();
    moduloInteger(*poly, ring->q, NULL);
  //  pause();
    repairPolynomial(*poly);
}


static void moduloInteger(Polynomial *poly, int q, int *error)
{
    SET_ERROR(error, OK);
      
    if(q<=0) return;
    if(poly==NULL)
    {
         SET_ERROR(error, UNITIALIZED_POLYNOMINALS);
         return;
    } 
    if(poly->type==REAL)
    {
        SET_ERROR(error, WRONG_POLYNOMINAL_COEFFICIENTS);
        return;
    } 
    for(int i=0; i<poly->degree; i++)
    {
        
        poly->coefficients[i]=mod((int)poly->coefficients[i],q);   
    }
}


static Polynomial* copyPolynomial(const Polynomial* p)
{
    Polynomial *result = (Polynomial*)malloc(sizeof(Polynomial));
    result->degree=p->degree;
    result->type=p->type;
    result->coefficients=(float*)malloc(result->degree*sizeof(float));
    memcpy(result->coefficients, p->coefficients, sizeof(float)*result->degree);
    return result;
}


static void repairPolynomial(Polynomial* p)
{
    if(p->type==REAL)
    {
    //    for(int i=0; i<p->degree; i++)p->coefficients[i]=roundf(1000*p->coefficients[i])/1000;//round to 3th decimal 
    }
    int i = p->degree-1;
    //while(i<p->degree&&p->coefficients[i]==0)i--;
    while(i>=0&&p->coefficients[i]==0)i--;
    p->degree=i+1;
   

}


static float inverseOfNumber(float number, QuotientPolynomialRing*ring)
{
    if(ring==NULL||ring->q<=0)return 1.0/number;
    else return invertInteger(number, ring->q);   
}