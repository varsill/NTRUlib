#ifndef _polynomial_H_
#define _polynomial_H_


#include "config.h"
#include <stdbool.h>
#include "integer_arithmetic.h"
#include "rationals.h"
#define MAX(a, b) a>b?a:b

#define createPolynomial(type, ring, error, ...) _createPolynomial(PP_NARG(__VA_ARGS__), type, ring, error, __VA_ARGS__)

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


#define GET_FUNCTION(_1, _2, NAME, ...) NAME
#define printPolynomial(...) GET_FUNCTION(__VA_ARGS__, _printPolynomialWithExtraMessage, _printPolynomial)(__VA_ARGS__)

typedef enum {INTEGER, REAL} Type;

typedef struct{
    int degree;
    Rational* coefficients;
    Type type;
} Polynomial;

typedef struct{
    Polynomial *ideal;
    int q;
}QuotientPolynomialRing;

//PUBLIC FUNCTIONS
Polynomial * _createPolynomial(unsigned int degree, Type type,QuotientPolynomialRing* ring, int* error, ...);
Polynomial * createZeroPolynomial(Type type, int * error);
void freePolynomial(Polynomial * poly);

bool comparePolynomials(const QuotientPolynomialRing * ring, const Polynomial * a, const Polynomial *b, int * error);

Polynomial * addPolynomials(const QuotientPolynomialRing *ring, const Polynomial *a, const Polynomial *b, int* error);
Polynomial * substractPolynomials(const QuotientPolynomialRing *, const Polynomial *, const Polynomial *, int* error);
Polynomial * multiplyPolynomials(const QuotientPolynomialRing *, const Polynomial *, const Polynomial *, int* error);
Polynomial * dividePolynomials(const QuotientPolynomialRing *, const Polynomial *, const Polynomial *,Polynomial *, int* error);
void moduloPolynomial(Polynomial ** , const Polynomial *, int *error);
Polynomial* invertPolynomial(const QuotientPolynomialRing* ring, Polynomial* poly);
Polynomial* extendedEuclid(const QuotientPolynomialRing* ring, const Polynomial *a,const Polynomial *b, Polynomial **u_ref, Polynomial **v_ref );
void multiplyPolynomialByConstant(Polynomial *poly, Rational* c, QuotientPolynomialRing* ring);


void _printPolynomial(const Polynomial* poly);
void _printPolynomialWithExtraMessage(const Polynomial* poly, const char* extra_msg);
//PRIVATE FUNCTIONS
static bool isPolynomialValid(Polynomial* poly, bool check_type);
static void moduloRing(Polynomial**poly_ref, const QuotientPolynomialRing* ring);
static void moduloInteger(Polynomial*poly, int q , int* error);
static void repairPolynomial(Polynomial * poly);
static Polynomial* copyPolynomial(const Polynomial* poly);
static Rational inverseOfNumber(Rational number, QuotientPolynomialRing*ring);



#endif


 