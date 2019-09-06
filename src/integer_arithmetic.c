#include "integer_arithmetic.h"
int ExtendedIntegerGCD(int a, int b, int* u, int*v)
{
    int s = 0;    int old_s=1;
    int t= 1;    int old_t = 0;
    int r = b;    int old_r = a;
    int q,x;
    while(r !=0)
    {
        q=(int)old_r/(int)r;//div
        x=old_r;old_r=r;r=x-q*r;
        x=old_s;old_s=s;s=x-q*s;
        x=old_t;old_t=t;t=x-q*t;
    }

    if(u!=NULL)*u=old_s;
    if(v!=NULL)*v=old_t;
    return old_r;
}


int invertInteger(int x, int N)
{
        int a, b;
        if(ExtendedIntegerGCD(x, N, &a, &b)!=1)return -1; //x and q are not coprime - cannot calculate inverse
        return mod(a, N);
}




unsigned int mod(int x, int N)
{
     return (x % N + N) %N;
}

int divideInteger(int a, int b, int N)
{
    int inverse = invertInteger(b, N);
    if(inverse<0)return -1;//couldn't get inverse of b - probably b is not coprime with q
    return mod(inverse*a, N);

}


