#include "polynominal.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "quotient_polynominal_ring.h"

#ifdef DEBUG_MEMORY
#include "debug_memory.h"
#endif




Polynominal * _createPolynominal(unsigned int _degree,Type _type, int* error,  ...)
{
    SET_ERROR(error, OK);
    Polynominal *p = (Polynominal*) malloc(sizeof(Polynominal));
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
    repairPolynominal(p);
    if(isPolynominalValid(p, true)==false)SET_ERROR(error, WRONG_POLYNOMINAL_COEFFICIENTS);
    return p;

}


Polynominal * createZeroPolynominal(Type _type, int* error)
{
    SET_ERROR(error, OK);
    Polynominal *p = (Polynominal*) malloc(sizeof(Polynominal));
    p->degree=0;
    p->type=_type;
    p->coefficients=NULL;
    return p;
}


void freePolynominal(Polynominal * p)
{
    if(p==NULL)return;
    if(p->coefficients!=NULL) free(p->coefficients);
    free(p);
    
}


bool comparePolynominals(const QuotientPolynominalRing *ring,const Polynominal *p1, const Polynominal *p2, int* error)
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

    Polynominal rest1;
    Polynominal rest2;
    if(ring->ideal!=NULL)
    {
        dividePolynominals(NULL, p1, ring->ideal, &rest1, NULL);
        dividePolynominals(NULL, p2, ring->ideal, &rest2, NULL);
        moduloInteger(&rest1, ring->q, NULL);
        moduloInteger(&rest2, ring->q, NULL); 
        return comparePolynominals(NULL,&rest1, &rest2, NULL);
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


Polynominal * addPolynominals(const QuotientPolynominalRing * ring, const Polynominal * p1,const Polynominal * p2, int* error)
{
    SET_ERROR(error, OK);
    if(p1==NULL || p2==NULL)
    {
        SET_ERROR(error,  UNITIALIZED_POLYNOMINALS);
        return NULL;   
    }

    unsigned int smaller_degree;
    Polynominal * result = (Polynominal*)malloc(sizeof(Polynominal));
   
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
    repairPolynominal(result);
    return result;
    
}


Polynominal * substractPolynominals(const QuotientPolynominalRing *ring, const Polynominal *p1, const Polynominal *p2, int *error)
{
     
   SET_ERROR(error, OK);
    if(p1==NULL || p2==NULL)
    {
        SET_ERROR(error,  UNITIALIZED_POLYNOMINALS);
        return NULL;   
    }

    unsigned int smaller_degree;
    Polynominal * result = (Polynominal*)malloc(sizeof(Polynominal));
   
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
    repairPolynominal(result);
    repairPolynominal(result);
    return result;

}


Polynominal * multiplyPolynominals(const QuotientPolynominalRing * ring, const Polynominal *p1, const Polynominal *p2, int *error)
{
    SET_ERROR(error, OK);
    if(p1==NULL || p2==NULL)
    {
        SET_ERROR(error, UNITIALIZED_POLYNOMINALS);
        return NULL;   
    }
    if(p1->degree==0||p2->degree==0)return createZeroPolynominal(INTEGER, NULL); //DO NAPRAWY
    Polynominal *result=(Polynominal*)malloc(sizeof(Polynominal));
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

    if(ring!=NULL)
    {   
       
        moduloRing(&result, ring);
    }
    repairPolynominal(result);
    return result;

}


Polynominal * dividePolynominals(const QuotientPolynominalRing *ring, const Polynominal *p1, const Polynominal *p2, Polynominal *rest, int *error)
{
    
    SET_ERROR(error, OK);
    if(p1==NULL || p2==NULL) 
    {
        SET_ERROR(error,UNITIALIZED_POLYNOMINALS);
        return NULL;   
    }
    Polynominal *result = (Polynominal*)malloc(sizeof(Polynominal));
    
    if(p1->type==INTEGER && p2->type==INTEGER) result->type=INTEGER;
    else result->type=REAL;
    
    result->degree=p1->degree-p2->degree+1;
    result->coefficients=(float*)malloc(sizeof(float)*result->degree);

  /*  
    if(rest==NULL)
    {
        rest=(Polynominal*)malloc(sizeof(Polynominal));
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
    
    Polynominal *bufor = (Polynominal*)malloc(sizeof(Polynominal));
    bufor->degree=p1->degree;
    bufor->type=p1->type;
    bufor->coefficients=(float*)malloc(sizeof(float)*bufor->degree);
    
    memcpy(bufor->coefficients, p1->coefficients, bufor->degree*sizeof(float));
   
    for(int i=bufor->degree-1; i>=0; i--)
    {
        if(i<p2->degree-1)break;
        result->coefficients[i-p2->degree+1]=bufor->coefficients[i]/p2->coefficients[p2->degree-1];
        for(int j=0; j<p2->degree; j++)    
        {
            bufor->coefficients[j+(i-p2->degree+1)]-=result->coefficients[i-p2->degree+1]*p2->coefficients[j];
        }
    }
    if(save_rest==true)
    {
        rest->degree=bufor->degree;
        rest->type=bufor->type;
        if(rest->coefficients==NULL)rest->coefficients=(float*)malloc(sizeof(float)*rest->degree);
        memcpy(rest->coefficients, bufor->coefficients, bufor->degree*sizeof(float));
        repairPolynominal(rest);
    }

    freePolynominal(bufor);
    
    if(ring!=NULL)
    {   
        moduloRing(&result, ring);
    }
    repairPolynominal(result);
    return result;

}


void printPolynominal(const Polynominal* poly, const char* text)
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


static bool isPolynominalValid(Polynominal *p, bool check_type)
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


void moduloPolynominal(Polynominal ** divident,const Polynominal * divisor, int* error)
{
    SET_ERROR(error, OK);
    if(divident==NULL)SET_ERROR(error, UNITIALIZED_POLYNOMINALS);
    if(*divident==NULL || divisor==NULL)
    {
        SET_ERROR(error, UNITIALIZED_POLYNOMINALS);
        return;   
    }
    Polynominal * rest;
   
    rest=(Polynominal*)malloc(sizeof(Polynominal));
    rest->coefficients=(float*)malloc(sizeof(float)*(divisor->degree-1));
    
    rest->degree=divisor->degree-1;
    
    rest->type=(*divident)->type;
    Polynominal * garbage = dividePolynominals(NULL, *divident, divisor, rest, error);
    freePolynominal(*divident);
    freePolynominal(garbage);
    *divident=rest;
    rest=NULL;
    repairPolynominal(*divident);
}


static void moduloRing(Polynominal **poly, const QuotientPolynominalRing *ring)
{
    if(ring==NULL)return;
    moduloPolynominal(poly, ring->ideal, NULL);
   
    moduloInteger(*poly, ring->q, NULL);
    repairPolynominal(*poly);
}


static void moduloInteger(Polynominal *poly, int q, int *error)
{
    SET_ERROR(error, OK);
         
    if(q<0) return;
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
        poly->coefficients[i]=((int)poly->coefficients[i])%q;
    }
}


static Polynominal* copyPolynominal(const Polynominal* p)
{
    Polynominal *result = (Polynominal*)malloc(sizeof(Polynominal));
    result->degree=p->degree;
    result->type=p->type;
    result->coefficients=(float*)malloc(result->degree*sizeof(float));
    memcpy(result->coefficients, p->coefficients, sizeof(float)*result->degree);
    return result;
}


static void repairPolynominal(Polynominal* p)
{
    int i = p->degree-1;
    //while(i<p->degree&&p->coefficients[i]==0)i--;
    while(i>=0&&p->coefficients[i]==0)i--;
    p->degree=i+1;
}

#define P -1

#define DEBUG printf("elo"); fflush(stdout);
 Polynominal* extendecEuclid(const Polynominal *a,const Polynominal *b, Polynominal **u_ref, Polynominal **v_ref)
{
   
    *u_ref = createPolynominal(INTEGER, NULL, 1);
    Polynominal *d  = copyPolynominal(a);
    Polynominal *zero = createZeroPolynominal(INTEGER, NULL);
    Polynominal *v1;
    Polynominal *v3;
    
    if(comparePolynominals(NULL, b, zero, NULL))
    {
        *v_ref=zero;
        return d;
    }
    else
    {
        v1=createZeroPolynominal(INTEGER, NULL);
        v3=copyPolynominal(b);    
    }
    QuotientPolynominalRing *ring = createQuotientPolynominalRing(NULL, P, NULL);
    Polynominal *q;
    Polynominal *t1;
    Polynominal *t3;
    while(true)
    {
      
        if(comparePolynominals(NULL,v3, zero, NULL))
        {
            
             Polynominal *x1=multiplyPolynominals(ring, a, *u_ref, NULL);
            
             Polynominal *x2=substractPolynominals(ring, d, x1, NULL);
              
             Polynominal *x3=dividePolynominals(ring, x2, b, NULL, NULL);   
            
             *v_ref=x3;
           
             freePolynominal(x1);
             freePolynominal(x2);
             freePolynominal(zero);
             
             freePolynominal(v1);
            freePolynominal(v3);
           freePolynominal(t1);
            freePolynominal(t3);
            
             free(ring);

            

        
             return d;
        }
        t3=(Polynominal*)malloc(sizeof(Polynominal));
        q=dividePolynominals(ring, d, v3, t3, NULL);
     
        Polynominal *x = multiplyPolynominals(ring, q, v1, NULL);
        freePolynominal(q);
        t1=substractPolynominals(ring, *u_ref, x, NULL);
        
        freePolynominal(x);
        freePolynominal(*u_ref);
        
        *u_ref=v1;
        freePolynominal(d);
        
        d=v3;
        v1=t1;
        v3=t3;

    


    }
}






Polynominal* extendedEuclid(const Polynominal *a,const Polynominal *b, Polynominal **u_ref, Polynominal **v_ref)
{
  //pause();
  
    Polynominal *r0 = copyPolynominal(a);Polynominal *r1=copyPolynominal(b);  
    Polynominal * s0= createPolynominal(INTEGER, NULL, 1); Polynominal *s1=createZeroPolynominal(INTEGER, NULL);
    Polynominal *t0=createZeroPolynominal(INTEGER, NULL); Polynominal * t1= createPolynominal(INTEGER, NULL, 1);
    Polynominal *zero = createZeroPolynominal(INTEGER, NULL);
    Polynominal *r2, *s2, *t2, *x, *q;
    while(comparePolynominals(NULL, r1, zero, NULL)==false)
    {
        
        q = dividePolynominals(NULL, r0, r1,NULL, NULL);
      
        
        x = multiplyPolynominals(NULL, q, r1, NULL);
        r2=substractPolynominals(NULL, r0,x, NULL);
        
        freePolynominal(x);

        x = multiplyPolynominals(NULL, q, s1, NULL);
        s2=substractPolynominals(NULL, s0,x, NULL);
        freePolynominal(x);

        x = multiplyPolynominals(NULL, q, t1, NULL);
        t2=substractPolynominals(NULL, t0,x, NULL);
        freePolynominal(x);
        
        freePolynominal(q);
        freePolynominal(r0);freePolynominal(s0);freePolynominal(t0);
        r0=r1;s0=s1;t0=t1;
        r1=r2;s1=s2;t1=t2;
    }

    Polynominal *g = r0;
    *u_ref=s0;
    *v_ref=t0;

    freePolynominal(r1);freePolynominal(s1);freePolynominal(t1);
    freePolynominal(r2);freePolynominal(s2);freePolynominal(t2);
    freePolynominal(zero);


    return g;
}






