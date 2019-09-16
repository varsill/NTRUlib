#ifndef _ntru_H_
#define _ntru_H_


#include <stdbool.h>
#include "config.h"
#include "polynomial.h"
#include "quotient_polynomial_ring.h"
#include <stdint.h>
#include <math.h>

#define WIDTH  (8 * sizeof(crc))
#define TOPBIT (1 << (WIDTH - 1))
#define POLYNOMIAL 0xD8  

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

static KeyPackage createKey(int N, int p, int q, int d);
KeyPackage generateKey(ParametersPack pack);
Polynomial * inversePolynomialModuloNotPrime(const QuotientPolynomialRing * ring, Polynomial * p);
Polynomial * encodePolynomial(const Polynomial *m, Polynomial *h, int N, int p, int q, int d);
Polynomial * decodePolynomial(Polynomial *e, Polynomial *f, Polynomial * f_p_inverse, int N, int p, int q, int d);

Polynomial * getPolynomialFromBinary(uint8_t *t, int length, int p);

uint8_t * getBinaryFromPolynomial(Polynomial * p, int* result_length);

Polynomial ** translateBinaryToPolynomials(uint8_t *t, int lenght, int N, int p, bool use_crc, int* poly_array_lenght);
uint8_t *translatePolynomialsToBinary(Polynomial ** poly_array, int poly_array_length, int p, bool use_crc,  int* result_length);

crc generateCRC(crc msg[], int N);
bool checkCRC(crc msg[], int N, crc x);

static int getPrime(int x);
static int getExponent(int x);
int * getDistinctRandomNumbers(int from, int to, int how_many);

#endif