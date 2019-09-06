#ifndef _rationals_h_
#define _rationals_h_
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "integer_arithmetic.h"
#define ACCURACY 100000

#define GET_FUNCTION(_1, _2, NAME, ...) NAME
#define createRational(...) GET_FUNCTION(__VA_ARGS__, _createRational2, _createRational1)(__VA_ARGS__)

typedef struct 
{
    long nominator;
    long denominator;
} Rational;


Rational _createRational1(double f);
Rational _createRational2(long n, long d);
bool compareRationals(const Rational *a, const Rational *b);
Rational addRationals(const Rational *a, const Rational *b);
Rational substractRationals(const Rational *a, const Rational *b);
Rational multiplyRationals(const Rational *a, const Rational *b);
Rational divideRationals(const Rational *a, const Rational *b);
Rational inverseRational(const Rational *a);
void printRational(const Rational *a);

static void approximate(double x, long *num, long *denom);
static void reduceRational(Rational *x);
static int getLCM(int a, int b);
#endif