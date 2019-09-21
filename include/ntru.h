#ifndef _ntru_H_
#define _ntru_H_


#include <stdbool.h>
#include "config.h"
#include "polynomial.h"
#include "quotient_polynomial_ring.h"
#include <stdint.h>
#include <math.h>
#include <memory.h>

#define WIDTH  (8 * sizeof(uint8_t))
#define TOPBIT (1 << (WIDTH - 1))
#define CRC8 0x1D8  

#define SET_BIT(t, i) (t)[(i)/8]|=(1<<((i)%8))
#define CLEAR_BIT(t, i) (t)[(i)/8]&=~(1<<((i)%8))
#define GET_BIT(t, i) (((t)[(i)/8] & (1<<((i)%8)) )>0)
#define GET_NTH_BIT(x, n) ((x & (1<<(n)))>0)
//#define COPY_BIT(a, i, b, j) CLEAR_BIT((b), (j)) ; (b)[(j)/8]|=(GET_BIT((a), (i))<<((i)%8))
#define COPY_BIT(a, i, b, j) {if(GET_BIT(a, i))SET_BIT(b, j); \
                             else CLEAR_BIT(b, j); }
typedef struct 
{
    Polynomial *f;
    Polynomial *h;
    Polynomial *f_p_inverse;
} KeyPackage;

typedef struct 
{
    int N, p, q, d;


    
} ParametersPack;

typedef uint8_t crc;

KeyPackage createKey(int N, int p, int q, int d);
KeyPackage generateKey(ParametersPack pack);
Polynomial * inversePolynomialModuloNotPrime(const QuotientPolynomialRing * ring, Polynomial * p);
Polynomial * encodePolynomial(const Polynomial *m, Polynomial *h, int N, int p, int q, int d);
Polynomial * decodePolynomial(Polynomial *e, Polynomial *f, Polynomial * f_p_inverse, int N, int p, int q, int d);

Polynomial * getPolynomialFromBinary(uint8_t *t, int s, int e, int p, bool is_crc);
uint8_t * getBinaryFromPolynomial(Polynomial * poly,int p,bool is_crc, int* result_length, bool *is_crc_valid);
Polynomial ** translateBinaryToPolynomials(uint8_t *t, int number_of_bits, int N, int p, bool is_crc, int* poly_array_length);
uint8_t *translatePolynomialsToBinary(Polynomial ** poly_array, int poly_array_length, int p,  bool is_crc, int* result_length);

crc getCRC(uint8_t msg[], int s, int e);
uint8_t checkCRC(uint8_t msg[], int s, int e);

static int getPrime(int x);
static int getExponent(int x);
int * getDistinctRandomNumbers(int from, int to, int how_many);

#endif