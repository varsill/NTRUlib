#include "rationals.h"



Rational _createRational1(double f)
{
    long n,d;
    Rational r;
    approximate(f, &n, &d);
    r.nominator=n;
    r.denominator=d;
    reduceRational(&r);
    return r;
}


Rational _createRational2(long n, long d)
{
    Rational r;
    r.nominator=n;
    r.denominator=d;
    reduceRational(&r);
    return r;
}


bool compareRationals(const Rational *a, const Rational *b)
{
    if(a->nominator==b->nominator && a->denominator==b->denominator)return true;
    Rational a_copy=*a;
    Rational b_copy=*b;
    reduceRational(&a_copy);
    reduceRational(&b_copy);
    if(a->nominator==b->nominator && a->denominator==b->denominator)return true;
    return false;
}


Rational addRationals(const Rational *a, const Rational *b)
{
    Rational r;
    int lcm=getLCM(a->denominator, b->denominator);
  //  printf("LCM: %d \n" , lcm);
    r.denominator=lcm;
    r.nominator=a->nominator*lcm/a->denominator+b->nominator*lcm/b->denominator;
    reduceRational(&r);
    return r;
}


Rational substractRationals(const Rational *a, const Rational *b)
{
    Rational r;
    int lcm=getLCM(a->denominator, b->denominator);
    r.denominator=lcm;
    r.nominator=a->nominator*lcm/a->denominator-b->nominator*lcm/b->denominator;
    reduceRational(&r);
    return r;
}


Rational multiplyRationals(const Rational *a, const Rational *b)
{
    Rational r;
    r.nominator=a->nominator*b->nominator;
    r.denominator=a->denominator*b->denominator;
    reduceRational(&r);
    return r;
}


Rational divideRationals(const Rational *a, const Rational *b)
{
    Rational r;
    r.nominator=a->nominator*b->denominator;
    r.denominator=a->denominator*b->nominator;
    reduceRational(&r);
    return r;
}


Rational inverseRational(const Rational *a)
{
    Rational r;
    r.denominator=a->nominator;
    r.nominator=a->denominator;
    reduceRational(&r);
    return r;
}


void printRational(const Rational *a)
{
    printf("%d/%d \n", a->nominator, a->denominator);
    fflush(stdout);
}


void approximate(double x, long *numerator, long *denominator)
{
    long gcd_ = ExtendedIntegerGCD(round(x * ACCURACY), ACCURACY, NULL, NULL);

    *denominator = ACCURACY / gcd_;
    *numerator = round(x * ACCURACY) / gcd_;
}


static void reduceRational(Rational *x)
{
    if(x->nominator<0 && x->denominator<0)
    {
        x->nominator*=-1;
        x->denominator*=-1;
    }
    else if (x->denominator<0)
    {
        x->nominator*=-1;
        x->denominator*=-1;
    }

    int gcd = ExtendedIntegerGCD(x->nominator, x->denominator, NULL, NULL);

    x->nominator/=gcd;
    x->denominator/=gcd;

}


static int getLCM(int a, int b)
{
    int gcd = ExtendedIntegerGCD(a, b, NULL, NULL);
    return a*b/gcd;
}