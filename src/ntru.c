#include "ntru.h"



KeyPackage createKey(int N, int p, int q, int d)
{
    bool further;
    QuotientPolynomialRing * ring_p = createQuotientPolynomialRing(createSpecialPolynomial(SIMPLE, N+1), p , NULL);
    QuotientPolynomialRing * ring_q = createQuotientPolynomialRing(createSpecialPolynomial(SIMPLE, N+1), q , NULL);
    Polynomial *g = createRandomPolynomial(BINARY, N, d);
    Polynomial *f;
    Polynomial *f_p_inverse;
    Polynomial *f_q_inverse;
  
    do
    {
        further=false;
       
        f = createRandomPolynomial(BINARY, N,d);
        
        f_p_inverse = inversePolynomialModuloNotPrime(ring_p, f);
        f_q_inverse = inversePolynomialModuloNotPrime(ring_q, f);
        
        if(f_p_inverse==NULL || f_q_inverse==NULL)
        {
            
            freePolynomial(f);
            
            freePolynomial(f_p_inverse);
            freePolynomial(f_q_inverse);
            further=true;
            
        }
      
    }while(further);
   
    Rational minus_one = createRational(-1, 1);
    Polynomial * PI = multiplyPolynomials(ring_q, f, g, NULL);//czy multiply liczy modulo polynomial?!
    multiplyPolynomialByConstant(PI, &minus_one, ring_p);
    Polynomial *buff=multiplyPolynomials(ring_q, PI, f_q_inverse, NULL);
    Polynomial *h=addPolynomials(ring_q, buff, g, NULL);
    
    freeQuotientPolynomialRing(ring_p);freeQuotientPolynomialRing(ring_q);
    freePolynomial(g);freePolynomial(PI);freePolynomial(buff);
    freePolynomial(f_q_inverse);

    KeyPackage result;
    result.f=f; result.f_p_inverse=f_p_inverse; result.h=h;
    return result;
    
}


Polynomial * encodePolynomial(const Polynomial *m, Polynomial *h, int N, int p, int q, int d)
{  
    Polynomial * fuzz = createRandomPolynomial(BINARY, N, d);
    
    QuotientPolynomialRing * ring_q = createQuotientPolynomialRing(createSpecialPolynomial(SIMPLE, N+1), q, NULL);
   
    Polynomial * buff = multiplyPolynomials(ring_q,h,fuzz, NULL);
    Polynomial * e = addPolynomials(ring_q, buff, m, NULL);
    
    freePolynomial(fuzz);freePolynomial(buff);
    freeQuotientPolynomialRing(ring_q);
    return e;

/* 
    Polynomial * h_cp=copyPolynomial(h);
    fillPolynomialWithLeadingZeros(h_cp, N);
    Polynomial * h_prim=createSpecialPolynomial(DOUBLE, h_cp);
    freePolynomial(h_cp);
    int *k = getDistinctRandomNumbers(1, N, d);
    QuotientPolynomialRing * ring = createQuotientPolynomialRing(NULL, q, NULL);
    Polynomial * e=m;
    for(int i=0; i<d; i++)
    {
        Polynomial *buffer = createSpecialPolynomial(EMPTY, N, INTEGER);
        for(int j=0; j<buffer->degree; j++)buffer->coefficients[buffer->degree-1-j]=h_prim->coefficients[h_prim->degree-(N+j-k[i])];
        Polynomial *e_buff = addPolynomials(ring, e, buffer, NULL);
        if(e!=m)freePolynomial(e);
        freePolynomial(buffer);
        e=e_buff;
    }
    freeQuotientPolynomialRing(ring);
    freePolynomial(h_prim);
    */
  

}

Polynomial * decodePolynomial(Polynomial *e, Polynomial *f, Polynomial * f_p_inverse, int N, int p, int q, int d)
{
    QuotientPolynomialRing * ring_q = createQuotientPolynomialRing(createSpecialPolynomial(SIMPLE, N+1), q, NULL);
    QuotientPolynomialRing * ring_p = createQuotientPolynomialRing(createSpecialPolynomial(SIMPLE, N+1), p, NULL);
    Polynomial * a = multiplyPolynomials(ring_q, f, e, NULL);
    
    int s = floor(q/2.0+d*(p-1)+d*d*d*1.0/(N));
    int t = q*floor((d*(p-1)+d*d*d*1.0/(N))*1.0/q);
    s=mod(s, q);
    t=mod(t, p);
 
   // t=0;
    
    
    

         
    
    
    
   // Polynomial * b = createSpecialPolynomial(ZERO, N, INTEGER);
 //   printPolynomial(a, "PRZED REDUKCJA:");
    for(int i=0; i<a->degree; i++)
    {
       // a->coefficients[i]=createRational(toInt(&a->coefficients[i])+t, 1);   
        if(toInt(&a->coefficients[i])<s) a->coefficients[i]=createRational(toInt(&a->coefficients[i])+t, 1);   
        else a->coefficients[i]=createRational(toInt(&a->coefficients[i])+t-q, 1);   
    }
    
  //  printPolynomial(a, "PO REDUKCJI:   ");
    
  
   
  Polynomial * n = multiplyPolynomials(ring_p,a, f_p_inverse, NULL);


  


    freeQuotientPolynomialRing(ring_p);freeQuotientPolynomialRing(ring_q);
    freePolynomial(a);
    return n;
    /* 
    {
    //we assume, that argument d of this function is equal to the argument d of the function createKey() - which means, that number of ones in binary polynomial f is equal to d
    int * u = (int*)malloc(d*sizeof(int));  
    Rational one = createRational(1, 1);
    int j=0;
    for(int i=0; i<f->degree; i++)
    {
        if(compareRationals(&f->coefficients[i], &one)==true)
        {
           
            u[j]=i;
            j++;
        }
    }

   
 
    //probably floor xD
    int s = floor(q/2.0+d*(p-1)+d*d*d*1.0/N);
    int t = q*floor((d*(p-1)+d*d*d/N)*1.0/q);
    s=mod(s, q);
    t=mod(t, p);
    Polynomial * v = f_p_inverse;

    Polynomial * v_cp = copyPolynomial(v);
    Polynomial * e_cp = copyPolynomial(e);
    fillPolynomialWithLeadingZeros(v_cp, N);
    fillPolynomialWithLeadingZeros(e_cp, N);
    Polynomial * v_prim = createSpecialPolynomial(DOUBLE, v_cp);
    Polynomial * e_prim = createSpecialPolynomial(DOUBLE, e_cp);
    freePolynomial(v_cp);
    freePolynomial(e_cp);
    QuotientPolynomialRing * ring_q = createQuotientPolynomialRing(NULL, q, NULL);
    Polynomial * a = createSpecialPolynomial(ZERO, N, INTEGER);

    
      
    for(int i=0; i<d; i++)
    {
        Polynomial *buffer = createSpecialPolynomial(EMPTY, N, INTEGER);
       
        for(int j=0; j<buffer->degree; j++)buffer->coefficients[buffer->degree-1-j]=e_prim->coefficients[e_prim->degree-1-(N+j-1-u[i])];
        
        
        Polynomial *a_buff = addPolynomials(ring_q, a, buffer, NULL); 
        freePolynomial(a);
        freePolynomial(buffer);
        
        a=a_buff; 
     
    }

    Polynomial * b = createSpecialPolynomial(EMPTY, N, INTEGER);
    fillPolynomialWithLeadingZeros(a, N);
    for(int i=0; i<a->degree; i++)
    {
        if(toInt(&a->coefficients[i])<s)b->coefficients[i]=createRational(toInt(&a->coefficients[i])+t, 1);
        else b->coefficients[i]=createRational(toInt(&a->coefficients[i])+t-q, 1);   
    }

    QuotientPolynomialRing * ring_p = createQuotientPolynomialRing(NULL, p, NULL);
    Polynomial *n=createZeroPolynomial(INTEGER, NULL);
    fillPolynomialWithLeadingZeros(b, N);
    printPolynomial(v_prim, "V:");
    printPolynomial(b, "b: ");
    for(int i=0; i<N; i++)
    {

        Polynomial * l = createSpecialPolynomial(EMPTY, N, INTEGER);
        for(int j=0; j<l->degree; j++)l->coefficients[l->degree-1-j]=v_prim->coefficients[v_prim->degree-(N+j-i)];
        printPolynomial(l, "l: ");
        multiplyPolynomialByConstant(l, &b->coefficients[b->degree-1-i], ring_p);
        Polynomial * n_buff = addPolynomials(ring_p, l, n, NULL);
        freePolynomial(n);
        freePolynomial(l);
        n=n_buff; 
         printPolynomial(n, "n: ");  
    //    printPolynomial(n);
    } 

    freeQuotientPolynomialRing(ring_p);freeQuotientPolynomialRing(ring_q);
    freePolynomial(v_prim);freePolynomial(e_prim);freePolynomial(b);freePolynomial(a);

    }
    
    */
    return n;

}


 Polynomial * inversePolynomialModuloNotPrime(const QuotientPolynomialRing * ring, Polynomial * a)
{
   
    int p = getPrime(ring->q);
    int e = getExponent(ring->q);
  
    QuotientPolynomialRing * ring_p = createQuotientPolynomialRing(copyPolynomial(ring->ideal), p, NULL);
  
    Polynomial * b = inversePolynomial(ring_p, a);
  
   if(b==NULL){
       freeQuotientPolynomialRing(ring_p);   
       
       return NULL;
   }
   

    int v = p;
    Polynomial * p_poly =createPolynomial(INTEGER, NULL, NULL, p);
    while(v<ring->q)
    {
        v=v*p;
        ring_p->q=v;
        Polynomial *tmp = multiplyPolynomials(ring_p, a, b, NULL);
        
        Polynomial *tmp2 = substractPolynomials(ring_p,p_poly, tmp, NULL);
         Polynomial *tmp3 = multiplyPolynomials(ring_p, tmp2, b, NULL);
         freePolynomial(b);
         freePolynomial(tmp);
         freePolynomial(tmp2);
         b=tmp3;
        
    }
    
    freePolynomial(p_poly);
    moduloRing(&b, ring);
    freeQuotientPolynomialRing(ring_p);
    return b;
}

static int getPrime(int x)
{
    for(int i=2; i<=x; i++)
    {
        if(x%i==0)return i;
    }
    return -1;
}

static int getExponent(int x)
{
    int r = getPrime(x);
    if(r==-1)return -1; 
    int i=0;
    while(x>1)
    {
        i++;
        x=x/r;
    }
    return i;
}


 int* getDistinctRandomNumbers(int from, int to, int how_many)
{
    int n  = to-from+1;
    if(how_many>n)return NULL;//cannot choose distinct numbers
    bool * tab = (bool*)malloc(n*sizeof(bool));
    int * result = malloc(how_many*sizeof(int));
    for(int i=0; i<n; i++)tab[i]=false;
    while(how_many>0)
    {
        int x = rand()%n;
      
        if(tab[x]==false)
        {
            tab[x]=true;
            how_many--;
        }
    }
    int j=0;
    
    for(int i=0; i<n; i++)
    {
        if(tab[i]==true)
        {
             
            result[j]=from+i;
            j++;
        }
    }

    free(tab);
    return result;

   

}


Polynomial * getPolynomialFromBinary(uint8_t *t, int s, int e, int p, bool is_crc)
{
    int bits_per_poly_coefficient = log2(p);
    uint8_t *b=NULL;
    if(is_crc)
    {
        b=malloc(sizeof(uint8_t)*(e-s+8));
        for(int i=0; i<e-s; i++){COPY_BIT(t, (s+i), b, i);}
        uint8_t crc = getCRC(b, 0, e-s);
        //printf("%d\n", crc);
       
        for(int i=0; i<8; i++){COPY_BIT((&crc), 7-i,b, (e-s)+i);}
        
        t=b;
        e=e-s+8;
        s=0;
    }
    int number_of_bits=e-s;
    int N=ceil(number_of_bits*1.0/bits_per_poly_coefficient);
   
    Polynomial * r=createSpecialPolynomial(ZERO, N);
    //printPolynomial(r, "HAHAHAH:");
    //printf("DUPA: %d", N);
    int j=0;
  //  printf("s: %dm e: %d \n", s, e);
    while(s<e)
    {   
        
        for(int i=0; i<bits_per_poly_coefficient; i++)
        {    
           //if(s>=e)break;
           //printf("%d",GET_BIT(t, s));
           r->coefficients[j]=createRational(2*toInt(&r->coefficients[j]), 1);   
           r->coefficients[j]=createRational(GET_BIT(t, s)+toInt(&r->coefficients[j]), 1);
           s++;
        }
        j++;
     
    }
    
    free(b);
    return r;
}


uint8_t * getBinaryFromPolynomial(Polynomial * poly,int p, bool is_crc, int* result_length, bool * is_crc_ok)
{
     int bits_per_poly_coefficient = log2(p);
     *result_length=bits_per_poly_coefficient*poly->degree;//probably floor
     uint8_t * result =(uint8_t*)malloc(sizeof(uint8_t)*ceil(*result_length/8.0));
     for(int i=0; i<ceil(*result_length/8.0); i++)result[i]=0;//bylo 8 zamiast 8.0 
     for(int i=0; i<poly->degree; i++)
     {
        for(int j=bits_per_poly_coefficient-1;j>=0; j--)
        {
            bool x = toInt(&poly->coefficients[i])%2;
            poly->coefficients[i]=createRational(toInt(&poly->coefficients[i])/2, 1);
            if(x)SET_BIT(result, (i*bits_per_poly_coefficient+j));
        }

     }
    //printf("\nRESULT LENGTH1: %d ", *result_length);
     if(is_crc)
     {
         uint8_t crc = checkCRC(result, 0, *result_length);
         if(crc==0)*is_crc_ok=true;
         else *is_crc_ok=false;
        (*result_length)-=8;
      
         uint8_t* result2 = malloc(sizeof(uint8_t)*ceil(*result_length/8.0));
         for(int i=0; i<*result_length; i++)
         {
             
          //  printf("%d", GET_BIT(result, i));
            COPY_BIT(result, i, result2, i);
         }
         printf(" ");
        
         free(result);
         result=result2;
     }
 // printf("RESULT LENGTH2: %d \n", *result_length);
    return result;
}


Polynomial ** translateBinaryToPolynomials(uint8_t *t, int number_of_bits, int N, int p, bool is_crc, int* n_of_polys)
{
    
    int bits_per_poly = floor(log2(p))*N;
    if(is_crc)bits_per_poly-=8;
    if(bits_per_poly<=0)
    {
        printDebug("Couldn't apply crc with such a chose of N and p parameters.");
        return;
    }
    *n_of_polys =  ceil(number_of_bits*1.0/(bits_per_poly));

    
   Polynomial ** polys = (Polynomial**)malloc(sizeof(Polynomial*)*(*n_of_polys));
   
//   uint8_t * b = (uint8_t*)malloc(sizeof(uint8_t)*ceil(bits_per_poly/8.0));
   for(int i=0; i<*n_of_polys; i++)
   {
       int e = (i+1)*bits_per_poly>number_of_bits?number_of_bits:(i+1)*bits_per_poly; 
       polys[i]=getPolynomialFromBinary(t,i*bits_per_poly, e,p, is_crc);
   }
    
    return polys;



}


uint8_t * translatePolynomialsToBinary(Polynomial ** poly_array, int poly_array_length, int p,  bool is_crc, int* result_length)
{
    int bits_per_poly = floor(log2(p))*poly_array[0]->degree;
    int bytes_per_poly = floor(bits_per_poly/8.0);
    *result_length=poly_array_length*bits_per_poly;
   // printf("%d ", poly_array_length);
    uint8_t * result = (uint8_t *)malloc(*result_length*sizeof(uint8_t));
    int r = 0;
    for(int i=0; i<poly_array_length; i++)
    {
        int l;
        bool is_crc_valid;
        uint8_t * t = getBinaryFromPolynomial(poly_array[i], p,is_crc, &l, &is_crc_valid);
      // for(int i=0; i<l; i++)    printf("%d", GET_BIT(t, i));
      //  printf(" ");
      if(!is_crc_valid)printDebug("\n BLADD!! ERROR!!!! \n")
        for(int j=0; j<l; j++){COPY_BIT(t, j,result, (r+j));}
        r=r+l;
        free(t);
    }
    if(is_crc)*result_length-=poly_array_length*8;

    return result;
}   






uint8_t getCRC(uint8_t msg[], int s, int e)
{
//terrible implementation
int LENGTH=8;
uint8_t * cp = (uint8_t*)malloc(sizeof(uint8_t)*(e-s+8));
for(int i=0; i<e-s+8; i++) CLEAR_BIT(cp, i);

for(int i=0; i<e-s; i++)
{
    if(GET_BIT(msg, (s+i)))SET_BIT(cp, i);
}



for(int i=0; i<e-s; i++)
{
if(GET_BIT(cp, i))
{
    for(int j=0; j<8; j++)
    {
        if(GET_BIT(cp, (j+i)) == GET_NTH_BIT(CRC8, 7-j))CLEAR_BIT(cp, (j+i));
        else SET_BIT(cp, (j+i));
    }
}


}

uint8_t result = 0;
for(int i=e-s; i<e-s+8; i++)
{
    result*=2;
    result+=GET_BIT(cp, i);
}



free(cp);
return result;

}


uint8_t checkCRC(uint8_t msg[], int s, int e)
{
//terrible implementation
int LENGTH=8;
uint8_t * cp = (uint8_t*)malloc(sizeof(uint8_t)*(e-s));
for(int i=0; i<e-s; i++) CLEAR_BIT(cp, i);

for(int i=0; i<e-s; i++)
{
    if(GET_BIT(msg, (s+i)))SET_BIT(cp, i);
}



for(int i=0; i<e-s-8; i++)
{
if(GET_BIT(cp, i))
{
    for(int j=0; j<8; j++)
    {
        if(GET_BIT(cp, (j+i)) == GET_NTH_BIT(CRC8, 7-j))CLEAR_BIT(cp, (j+i));
        else SET_BIT(cp, (j+i));
    }

}



}

uint8_t result = 0;
for(int i=e-s-8; i<e-s; i++)
{
    result*=2;
    result+=GET_BIT(cp, i);
}



free(cp);
return result;

}





KeyPackage generateKey(ParametersPack pack)
{
    return createKey(pack.N, pack.p, pack.q, pack.d);
}