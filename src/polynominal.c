#include "polynominal.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>





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
    if(isPolynominalValid(p, true)==false)SET_ERROR(error, WRONG_POLYNOMINAL_COEFFICIENTS);
    return p;

}

void freePolynominal(Polynominal * p)
{
    if(p==NULL)return;
    free(p->coefficients);
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
    
    dividePolynominals(NULL, p1, ring->ideal, &rest1, NULL);
    dividePolynominals(NULL, p2, ring->ideal, &rest2, NULL);
    
    return comparePolynominals(NULL, &rest1, &rest2, NULL);
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
        moduloPolynominal(&result, ring->ideal, NULL);
        
    }
    
    return result;
    
}


Polynominal * substractPolynominals(const QuotientPolynominalRing *ring, const Polynominal *p1, const Polynominal *p2, int *error)
{
     
    SET_ERROR(error, OK);
    if(p1==NULL || p2==NULL)
    {
        SET_ERROR(error, UNITIALIZED_POLYNOMINALS);
        return NULL;   
    }
    
   Polynominal *p2_negation = (Polynominal *)malloc(sizeof(Polynominal));
    p2_negation->coefficients=(float*)malloc(p2->degree*sizeof(float));
    p2_negation->type=p2->type;
    p2_negation->degree=p2->degree;
    for(int i=0; i<p2->degree; i++)p2_negation->coefficients[i]= p2->coefficients[i]*(-1.0);
   
    Polynominal *result=addPolynominals(ring, p1, p2_negation, error);
    
    freePolynominal(p2_negation);
    
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

    Polynominal *result=(Polynominal*)malloc(sizeof(Polynominal));
    result->degree=p1->degree+p2->degree-1;
    result->coefficients=(float*)malloc((result->degree)*sizeof(float));
    if(p1->type==INTEGER && p2->type==INTEGER) result->type=INTEGER;
    else result->type=REAL;

    for(int k=0; k<result->degree; k++)
    {
        result->coefficients[k]=0;
        for(int i=MAX((k-p2->degree+1), 0); i<p1->degree; i++)
        {
            result->coefficients[k]+=p1->coefficients[i]*p2->coefficients[k-i];
        }
    }


    if(ring!=NULL)
    {   
        moduloPolynominal(&result, ring->ideal, NULL);
    }
    
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
   
    if(rest==NULL)rest=(Polynominal*)malloc(sizeof(Polynominal));
    
    rest->coefficients=(float*)malloc(sizeof(float)*p2->degree-1);
    rest->degree=result->degree;
    rest->type=result->type;

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

    rest->degree=bufor->degree;
    rest->type=bufor->type;
    memcpy(rest->coefficients, bufor->coefficients, bufor->degree*sizeof(float));
    repairPolynominal(rest);
  
    freePolynominal(bufor);
    return result;

}
void printPolynominal(const Polynominal* poly)
{
    if(poly==NULL) return;
    printf("POLYNOMIAN: ");
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
    rest->coefficients=(float*)malloc(sizeof(float)*divisor->degree-1);
    rest->degree=divisor->degree;
    rest->type=(*divident)->type;
    dividePolynominals(NULL, *divident, divisor, rest, NULL);
    freePolynominal(*divident);
    *divident=rest;
    rest=NULL;
    repairPolynominal(*divident);
}


static void repairPolynominal(Polynominal* p)
{
    int i = p->degree-1;
    while(i<p->degree&&p->coefficients[i]==0)i--;
    p->degree=i+1;
;}