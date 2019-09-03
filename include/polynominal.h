#ifndef _polynominal_H_
#define _polynominal_H_


#include "config.h"
#include <stdbool.h>
//#include "quotient_polynominal_ring.h"

#define MAX(a, b) a>b?a:b

#define createPolynominal(type, ring, error, ...) _createPolynominal(PP_NARG(__VA_ARGS__), type, ring, error, __VA_ARGS__)

#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

#define SET_ERROR(error, flag) if(error!=NULL)*error=flag

typedef enum {INTEGER, REAL} Type;

typedef struct{
    unsigned int degree;
    float* coefficients;
    Type type;
} Polynominal;

typedef struct{
    Polynominal *ideal;
    int q;
}QuotientPolynominalRing;


Polynominal * _createPolynominal(unsigned int, Type,QuotientPolynominalRing*, int*, ...);
Polynominal * createZeroPolynominal(Type, int *);
void freePolynominal(Polynominal *);
bool comparePolynominals(const QuotientPolynominalRing *, const Polynominal *, const Polynominal *, int *);
Polynominal * addPolynominals(const QuotientPolynominalRing *, const Polynominal *, const Polynominal *, int*);
Polynominal * substractPolynominals(const QuotientPolynominalRing *, const Polynominal *, const Polynominal *, int*);
Polynominal * multiplyPolynominals(const QuotientPolynominalRing *, const Polynominal *, const Polynominal *, int*);
Polynominal * dividePolynominals(const QuotientPolynominalRing *, const Polynominal *, const Polynominal *,Polynominal *, int*);
void multiplyPolynominalByConstant(Polynominal *poly, float c, QuotientPolynominalRing* ring);
void printPolynominal(const Polynominal*, const char *);

static bool isPolynominalValid(Polynominal*, bool);
void moduloPolynominal(Polynominal ** , const Polynominal *, int *error);
static void moduloRing(Polynominal**, const QuotientPolynominalRing*);
static void moduloInteger(Polynominal*, int , int*);
static void repairPolynominal(Polynominal *);
static Polynominal* copyPolynominal(const Polynominal* );
Polynominal* invertPolynominal(Polynominal* poly, QuotientPolynominalRing* ring);
Polynominal* extendedEuclid(const Polynominal *,const Polynominal *, Polynominal **, Polynominal **, const QuotientPolynominalRing* );
int invertInteger(int, int);
int ExtendedIntegerGCD(int a, int b, int* i, int*v);
unsigned int mod(int x, int N);
int divideInteger(int a, int b, int N);
int gcdOfPolynomialCoefficients(Polynominal* poly);
float inverseOfNumber(float number, QuotientPolynominalRing*ring);
#endif


 