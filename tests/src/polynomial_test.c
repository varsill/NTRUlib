#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "quotient_polynomial_ring.h"
#include "polynomial.h"
#include <stdbool.h>
#include "config.h"
#include "hashtable.h"
#include "config.h"

extern int elements_allocated;

START_TEST(generation)
{
	int error;

	Polynomial *poly = createPolynomial(INTEGER,NULL,&error, 2, 3, 0, 2,2, 1);
	
	ck_assert(error==OK);

	freePolynomial(poly);
	
	poly=createPolynomial(INTEGER, &error, 0, 2, 1, 2, 1);

	//ck_assert(error==WRONG_POLYNOMINAL_COEFFICIENTS);
	freePolynomial(poly);

	Polynomial *ideal = createPolynomial(REAL, NULL, &error, 2.5, 3.1, 0, 2.1, 1.4);
	ck_assert(error==OK);

	QuotientPolynomialRing *ring = createQuotientPolynomialRing(ideal,-1, &error);
	ck_assert(error==OK);
	freeQuotientPolynomialRing(ring);

	ideal=createPolynomial(INTEGER,NULL, &error, 2.5, 3, 12, 2);
//	ck_assert(error==WRONG_POLYNOMINAL_COEFFICIENTS);
	freePolynomial(ideal);

	Polynomial *x = createRandomPolynomial(BINARY, 10, 3);
 	ck_assert(x->degree<=10);
	int d = 0;
	Rational one = createRational(1, 1);
	for(int i=0; i<x->degree; i++)
	{
		if(compareRationals(&x->coefficients[i], &one)==true)d++;
	}
	ck_assert(d==3);
	freePolynomial(x);


}
END_TEST

START_TEST(comparison)
{
	int error;
	Polynomial *poly1=createPolynomial(INTEGER,NULL,&error, 2, 3, 0, 2, 1);
    Polynomial *poly2=createPolynomial(INTEGER,NULL,&error, 2, 3, 0, 2, 1);

	ck_assert(comparePolynomials(NULL, poly1, poly2, NULL)==true);

	Polynomial *poly3=createPolynomial(INTEGER,NULL, &error,2, 3, 1, 2);
	
	ck_assert(comparePolynomials(NULL, poly1, poly3, NULL)==false);

	Polynomial *poly4=createPolynomial(REAL,NULL, &error,2.0, 3.0, 0.0, 2.0, 1.0);
	ck_assert(comparePolynomials(NULL, poly1, poly4, NULL)==true);

	Polynomial *poly5 = createPolynomial(INTEGER,NULL,&error, 1, 2, 0, 0);
	Polynomial *poly6 = createPolynomial(INTEGER,NULL,&error, 2, -2, -1);
	Polynomial *ideal = createPolynomial(INTEGER,NULL,&error, 1, 0, 2, 1);
	QuotientPolynomialRing *ring = createQuotientPolynomialRing(ideal,-1, &error);
	ck_assert(comparePolynomials(ring, poly5, poly6, NULL)==true);
	ck_assert(comparePolynomials(ring, poly5,poly1, NULL)==false);
	
 	freePolynomial(poly1);
	freePolynomial(poly2);
 	freePolynomial(poly3);
	freePolynomial(poly4);
 	freePolynomial(poly5);
	freePolynomial(poly6);
	
	freeQuotientPolynomialRing(ring);
}
END_TEST

START_TEST(addition)
{
	
 	Polynomial *poly1 = createPolynomial(INTEGER,NULL,NULL, 2, 3, 1, 2);
	Polynomial *poly2 = createPolynomial(INTEGER, NULL,NULL,2, 1, 0);
	
	Polynomial *result = createPolynomial(INTEGER, NULL,NULL, 2, 5, 2, 2);
	Polynomial * _result = addPolynomials(NULL, poly1, poly2, NULL);
	ck_assert(comparePolynomials(NULL, _result , result, NULL));
	
	
	freePolynomial(poly1);
	freePolynomial(poly2);
	freePolynomial(result);
	freePolynomial(_result);
}
END_TEST

START_TEST(substraction)
{
        Polynomial *poly1 = createPolynomial(INTEGER,NULL,NULL, 2, 1, 2);
        Polynomial *poly2 = createPolynomial(INTEGER,NULL,NULL, 2, 1, 0);
        Polynomial *result = createPolynomial(INTEGER,NULL,NULL, 2);
		Polynomial *_result=substractPolynomials(NULL, poly1, poly2, NULL);
        ck_assert(comparePolynomials(NULL, _result, result, NULL));

		freePolynomial(poly1);
        freePolynomial(poly2);
        freePolynomial(result);
		freePolynomial(_result);
}
END_TEST

START_TEST(multiplication)
{
		Polynomial *poly1 = createPolynomial(INTEGER,NULL,NULL, 2, 1, 2);
        Polynomial *poly2 = createPolynomial(INTEGER,NULL,NULL,2, 1, 0);
        Polynomial *result = createPolynomial(INTEGER,NULL,NULL,4, 4, 5, 2, 0);
		
		Polynomial *_result=multiplyPolynomials(NULL, poly1, poly2, NULL);
		
		QuotientPolynomialRing * ring = createQuotientPolynomialRing(NULL, 3, NULL);
		Polynomial * result_modulo=createPolynomial(INTEGER, NULL,NULL, 1,1,2,2,0);
		
		Polynomial *_result_modulo=multiplyPolynomials(ring, poly1, poly2, NULL);
		
		//printPolynomial(_result_modulo);
        ck_assert(comparePolynomials(NULL, _result, result, NULL)==true);
		ck_assert(comparePolynomials(ring, _result_modulo, result_modulo, NULL)==true);
        freePolynomial(poly1);
        freePolynomial(poly2);
        freePolynomial(result);
		freePolynomial(_result);
		freePolynomial(result_modulo);
		freePolynomial(_result_modulo);
		freeQuotientPolynomialRing(ring);
}
END_TEST

START_TEST(division)
{
	Polynomial *poly1 = createPolynomial(INTEGER,NULL, NULL,1, -4, 2, -3);
    Polynomial *poly2 = createPolynomial(INTEGER,NULL, NULL,1, 2);
    Polynomial *result = createPolynomial(INTEGER,NULL,NULL, 1, -6, 14);
    Polynomial *rest = createPolynomial(INTEGER,NULL, NULL, -31);
	Polynomial *_rest=createZeroPolynomial(INTEGER, NULL);
	Polynomial * _result= dividePolynomials(NULL, poly1, poly2, _rest, NULL);
	
	ck_assert(comparePolynomials(NULL,_result, result, NULL)==true);
	ck_assert(comparePolynomials(NULL, _rest, rest, NULL)==true);
	
	moduloPolynomial(&poly1, poly2, NULL);
	ck_assert(comparePolynomials(NULL, rest, poly1, NULL)==true);
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(result);
	freePolynomial(rest);
	freePolynomial(_result);
	freePolynomial(_rest);
}
END_TEST

START_TEST(inversion)
{
	int error;
	Polynomial *poly = createPolynomial(INTEGER, NULL,NULL, 1, 0, 1);
    Polynomial *expected_result = createPolynomial(INTEGER, NULL,NULL, 7, 6, 7);
	QuotientPolynomialRing *ring = createQuotientPolynomialRing(createPolynomial(INTEGER, NULL,NULL, 1, 0, 2,1), 13, NULL);
	Polynomial * result = inversePolynomial(ring, poly);

	ck_assert(comparePolynomials(ring, expected_result, result, NULL)==true);
	
	freePolynomial(poly);
	freePolynomial(result);
	freePolynomial(expected_result);
	freeQuotientPolynomialRing(ring);

}
END_TEST



Suite * polynomial_suite(void)
{
	Suite * s;
	TCase * tc_comparison;
	TCase * tc_basic_operations;
	TCase * tc_generation;
	s=suite_create("Polynomial testing suite");

	tc_generation=tcase_create("Generate and polynomials");
	tcase_add_test(tc_generation, generation );
	suite_add_tcase(s, tc_generation);
	tc_comparison=tcase_create("Comparing two polynomials");
	tcase_add_test(tc_comparison, comparison);
	suite_add_tcase(s, tc_comparison);

	tc_basic_operations=tcase_create("Basic operations on polynomial");
	tcase_add_test(tc_basic_operations, addition);
	tcase_add_test(tc_basic_operations, substraction);
	tcase_add_test(tc_basic_operations, multiplication);
	tcase_add_test(tc_basic_operations, division);
	tcase_add_test(tc_basic_operations, inversion);
 	suite_add_tcase(s, tc_basic_operations);

	return s;

}



#include "ntru.h"
int main(void)
{START_DEBUG

/* 	printf("%d", invertInteger(2, 8));
	return 1;
	Polynomial * x = createPolynomial(INTEGER, NULL, NULL, 1, 0, 0, 1, 1);
	Polynomial * y = createPolynomial(INTEGER, NULL, NULL, 1, 0, 0,  -1 );

	QuotientPolynomialRing * ring = createQuotientPolynomialRing(NULL, 8, NULL);
	Polynomial *a, *b;
	Polynomial * r = extendedEuclid(ring, x, y, &a, &b);
	if(r==NULL) 
	{printDebug("NO I GIT");}
	
	freePolynomial(x);
	freePolynomial(y);
	//freePolynomial(r);
	//freePolynomial(a);
	//freePolynomial(b);
//	freeQuotientPolynomialRing((ring));STOP_DEBUG
//	return 1;

	srand(time(NULL));
	
	Polynomial * a = createPolynomial(INTEGER, NULL, NULL, 1, 2,3,4,5,6);
	Polynomial *b = createSpecialPolynomial(DOUBLE, a);
	printPolynomial(b);
	freePolynomial(a);freePolynomial(b);
	//printPolynomial(k.f, "f: ");
//	printPolynomial(k.h, "h: ");
//	printPolynomial(k.f_p_inverse, "f_p_inverse: ");*/

srand(time(NULL));
	int N = 10;
	int p = 2;
	int q = 16;
	int d = 5;

	
	KeyPackage keys = createKey(N, p, q, d);

	
//	Polynomial * m = createPolynomial(INTEGER, NULL, NULL, 1, 3, 3, 7, 2, 1, 3, 7);
Polynomial * m = createPolynomial(INTEGER, NULL, NULL, 1, 0, 0, 1, 0, 1, 1);

//fillPolynomialWithLeadingZeros(m, N);
	
	
	Polynomial * e = encodePolynomial(m, keys.h, N, q, d);

	Polynomial * decoded = decodePolynomial(e, keys.f, keys.f_p_inverse, N, p, q, d);
	printPolynomial(decoded);
	freePolynomial(decoded);
	freePolynomial(m);
	freePolynomial(e);

	freePolynomial(keys.f);freePolynomial(keys.f_p_inverse);freePolynomial(keys.h);
	STOP_DEBUG
	return 1;
/* 
Hashtable* h = createHashtable(fun);

insertElement(h, 10002, "xDDD");

removeElement(h, 10002);
insertElement(h, 3, "lels");
printf("%d", insertElement(h, 10002, "lels"));

//printf("%s", h->elements_tab[]);
//printf("%s",h->elements_tab[2].data);



deleteHashtable(h);
	
	return 1;*/

 /*	Polynomial *a1 = createPolynomial(INTEGER, NULL, 4, 4);
	Polynomial *a2 = createPolynomial(INTEGER, NULL, 1, 3);

	Polynomial *result = multiplyPolynomials(ring, a1, a2, NULL);
	result = multiplyPolynomials(ring, a1, a2, NULL);
	result = multiplyPolynomials(ring, a1, a2, NULL);
	result = multiplyPolynomials(ring, a1, a2, NULL);
	printPolynomial(result, "");
	freePolynomial(a1);
	freePolynomial(a2);
	freePolynomial(result);
	//freeQuotientPolynomialRing(ring);
	printf()
	*/
   
	
/*	
	QuotientPolynomialRing * ring = createQuotientPolynomialRing(createPolynomial(INTEGER,NULL, NULL, 1, 2,0,6,1), 211, NULL);
//Polynomial *a = createPolynomial(INTEGER,ring, NULL, 1, 2,0,6,0);
	Polynomial *b = createPolynomial(INTEGER, ring, NULL, 1,2, 0, 6, 0, 2);

	//Polynomial *x  = extendedEuclid(a, b, &u, &v, ring);
	//printf("GCD: %d", gcdOfPolynomialCoefficients(a));
	//Polynomial * x = dividePolynomials(ring, a, b, u, NULL);
	//printPolynomial(a, "");
  //  printPolynomial(x, "FINALE: ");
//	printPolynomial(u, "FIRST:");
//	printPolynomial(v, "SECOND: ");
//	freePolynomial(x);;
	Polynomial *t = inversePolynomial(ring, b);
	//printf("%d ", t);fflush(stdout);
	printPolynomial(t,"INVERTED POLYNOMINAL ");
	freeQuotientPolynomialRing(ring);
	freePolynomial(b);
	freePolynomial(t);
	return 1;
//	freePolynomial(a);
//	freePolynomial(u);
  // freePolynomial(v);
	
//	printf("%d", countElements(h));*/ 

		
	
	/* 
	QuotientPolynomialRing * ring = createQuotientPolynomialRing(createPolynomial(INTEGER,NULL, NULL, 1, 12, 4, 57, 1),NULL, NULL);
	Polynomial *b = createPolynomial(INTEGER, ring, NULL, 1,52 );
	Polynomial *u;
	Polynomial *v;
	
	Polynomial *x  = invertPolynomial(ring,b);
	printPolynomial(x, "INVERSION ");
	freePolynomial(x);
	//freePolynomial(a);
	freePolynomial(b);
	freeQuotientPolynomialRing(ring);
	return 1;
//	printUnallocatedMemory();
	*/
/*
//	START_DEBUG
	QuotientPolynomialRing * ring = createQuotientPolynomialRing(NULL, 211, NULL);
	Polynomial *a = createPolynomial(INTEGER, ring, NULL, 1 ,41 ,6, 1 ,12);
	Polynomial *b = createPolynomial(INTEGER, ring, NULL,1 ,11 ,177, 67); 


	Polynomial *r = multiplyPolynomials(ring, a,b, NULL);

	printPolynomial(r);

	freePolynomial(a);
	freePolynomial(b);
	freePolynomial(r);
	freeQuotientPolynomialRing(ring);

int error;
	Polynomial *poly1=createPolynomial(INTEGER,NULL,&error, 2, 3, 0, 2, 1);
    Polynomial *poly2=createPolynomial(INTEGER,NULL,&error, 2, 3, 0, 2, 1);

	comparePolynomials(NULL, poly1, poly2, NULL);

	Polynomial *poly3=createPolynomial(INTEGER,NULL, &error,2, 3, 1, 2);
	
	comparePolynomials(NULL, poly1, poly3, NULL);

	Polynomial *poly4=createPolynomial(REAL,NULL, &error,2.0, 3.0, 0.0, 2.0, 1.0);
	comparePolynomials(NULL, poly1, poly4, NULL);

	Polynomial *poly5 = createPolynomial(INTEGER,NULL,&error, 1, 2, 0, 0);
	Polynomial *poly6 = createPolynomial(INTEGER,NULL,&error, 2, -2, -1);
	Polynomial *ideal = createPolynomial(INTEGER,NULL,&error, 1, 0, 2, 1);
	QuotientPolynomialRing *ring = createQuotientPolynomialRing(ideal,-1, &error);
	comparePolynomials(ring, poly5, poly6, NULL);
//	ck_assert(comparePolynomials(ring, poly5,poly1, NULL)==false);
	
 	freePolynomial(poly1);
	freePolynomial(poly2);
 	freePolynomial(poly3);
	freePolynomial(poly4);
 	freePolynomial(poly5);
	freePolynomial(poly6);
	freeQuotientPolynomialRing(ring);
	return 1;
*/START_DEBUG
    int number_failed;
    Suite *s; 
    SRunner *sr;
	//createPolynomial(INTEGER, NULL, 1, 2, 1);
    s = polynomial_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
	
   // printf("%d", number_failed);
	//printf("\nMEMORY_DEBUG: %d \n", elements_allocated);
	//printMemoryStatus();
STOP_DEBUG
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;





}
