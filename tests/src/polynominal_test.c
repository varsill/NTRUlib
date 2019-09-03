#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "quotient_polynominal_ring.h"
#include "polynominal.h"
#include <stdbool.h>
#include "config.h"
#include "hashtable.h"
#ifdef DEBUG_MEMORY
#include "debug_memory.h"
#endif
extern int elements_allocated;

START_TEST(generation)
{
	int error;

	Polynominal *poly = createPolynominal(INTEGER,NULL,&error, 2, 3, 0, 2, 1);
	
	ck_assert(error==OK);

	freePolynominal(poly);
	
	poly=createPolynominal(INTEGER, &error, 0, 2, 1, 2, 1);
	ck_assert_msg(error==WRONG_POLYNOMINAL_COEFFICIENTS);
	freePolynominal(poly);

	Polynominal *ideal = createPolynominal(REAL, NULL, &error, 2.5, 3.1, 0, 2.1, 1.4);
	ck_assert(error==OK);

	QuotientPolynominalRing *ring = createQuotientPolynominalRing(ideal,-1, &error);
	ck_assert(error==OK);
	freeQuotientPolynominalRing(ring);

	ideal=createPolynominal(INTEGER,NULL, &error, 2.5, 3, 12, 2);
	ck_assert(error=WRONG_POLYNOMINAL_COEFFICIENTS);
	freePolynominal(ideal);

}
END_TEST

START_TEST(comparison)
{
	int error;
	Polynominal *poly1=createPolynominal(REAL,NULL,&error, 2, 3, 0, 2, 1);
	Polynominal *poly2=createPolynominal(REAL,NULL,&error, 2, 3, 0, 2, 1);

	ck_assert(comparePolynominals(NULL, poly1, poly2, NULL)==true);

	Polynominal *poly3=createPolynominal(REAL,NULL, &error,2, 3, 1, 2);

	ck_assert(comparePolynominals(NULL, poly1, poly3, NULL)==false);

	Polynominal *poly4=createPolynominal(REAL,NULL, &error,2.0, 3.0, 0, 2.0, 1.0);
	ck_assert(comparePolynominals(NULL, poly1, poly4, NULL)==true);

	Polynominal *poly5 = createPolynominal(REAL,NULL,&error, 1, 2, 0, 0);
	Polynominal *poly6 = createPolynominal(REAL,NULL,&error, 2, 1, 2);
	Polynominal *ideal = createPolynominal(REAL,NULL,&error, 1, 0, 2, 1);
	QuotientPolynominalRing *ring = createQuotientPolynominalRing(ideal,-1, &error);
	ck_assert(comparePolynominals(ring, poly5, poly6, NULL)==true);
	ck_assert(comparePolynominals(ring, poly5,poly1, NULL)==false);
	
	freePolynominal(poly1);
	freePolynominal(poly2);
	freePolynominal(poly3);
	freePolynominal(poly4);
	freePolynominal(poly5);
	freePolynominal(poly6);
	freePolynominal(ideal);
	freeQuotientPolynominalRing(ring);
}
END_TEST

START_TEST(addition)
{
	
 	Polynominal *poly1 = createPolynominal(INTEGER,NULL,NULL, 2, 3, 1, 2);
	Polynominal *poly2 = createPolynominal(INTEGER, NULL,NULL,2, 1, 0);
	
	Polynominal *result = createPolynominal(INTEGER, NULL,NULL, 2, 5, 2, 2);
	Polynominal * _result = addPolynominals(NULL, poly1, poly2, NULL);
	ck_assert(comparePolynominals(NULL, _result , result, NULL));
	
	
	freePolynominal(poly1);
	freePolynominal(poly2);
	freePolynominal(result);
	freePolynominal(_result);
}
END_TEST

START_TEST(substraction)
{
        Polynominal *poly1 = createPolynominal(INTEGER,NULL,NULL, 2, 1, 2);
        Polynominal *poly2 = createPolynominal(INTEGER,NULL,NULL, 2, 1, 0);
        Polynominal *result = createPolynominal(INTEGER,NULL,NULL, 2);
		Polynominal *_result=substractPolynominals(NULL, poly1, poly2, NULL);
        ck_assert(comparePolynominals(NULL, _result, result, NULL));

		freePolynominal(poly1);
        freePolynominal(poly2);
        freePolynominal(result);
		freePolynominal(_result);
}
END_TEST

START_TEST(multiplication)
{
		Polynominal *poly1 = createPolynominal(INTEGER,NULL,NULL, 2, 1, 2);
        Polynominal *poly2 = createPolynominal(INTEGER,NULL,NULL,2, 1, 0);
        Polynominal *result = createPolynominal(INTEGER,NULL,NULL,4, 4, 5, 2, 0);
		
		Polynominal *_result=multiplyPolynominals(NULL, poly1, poly2, NULL);
		
		QuotientPolynominalRing * ring = createQuotientPolynominalRing(NULL, 3, NULL);
		Polynominal * result_modulo=createPolynominal(INTEGER, NULL,NULL, 1,1,2,2,0);
		
		Polynominal *_result_modulo=multiplyPolynominals(ring, poly1, poly2, NULL);
		
		//printPolynominal(_result_modulo);
        ck_assert(comparePolynominals(NULL, _result, result, NULL)==true);
		ck_assert(comparePolynominals(ring, _result_modulo, result_modulo, NULL)==true);
        freePolynominal(poly1);
        freePolynominal(poly2);
        freePolynominal(result);
		freePolynominal(_result);
		freePolynominal(result_modulo);
		freePolynominal(_result_modulo);
		freeQuotientPolynominalRing(ring);
}
END_TEST

START_TEST(division)
{
	Polynominal *poly1 = createPolynominal(INTEGER,NULL, NULL,1, -4, 2, -3);
    Polynominal *poly2 = createPolynominal(INTEGER,NULL, NULL,1, 2);
    Polynominal *result = createPolynominal(INTEGER,NULL,NULL, 1, -6, 14);
    Polynominal *rest = createPolynominal(INTEGER,NULL, NULL, -31);
	Polynominal *_rest=createZeroPolynominal(INTEGER, NULL);
	Polynominal * _result= dividePolynominals(NULL, poly1, poly2, _rest, NULL);
	
	ck_assert(comparePolynominals(NULL,_result, result, NULL)==true);
	ck_assert(comparePolynominals(NULL, _rest, rest, NULL)==true);
	
	moduloPolynominal(&poly1, poly2, NULL);
	ck_assert(comparePolynominals(NULL, rest, poly1, NULL)==true);
    freePolynominal(poly1);
    freePolynominal(poly2);
    freePolynominal(result);
	freePolynominal(rest);
	freePolynominal(_result);
	freePolynominal(_rest);
}
END_TEST
/* 
START_TEST(inversion)
{
	int error;
	Polynominal *poly = createPolynominal(3,NULL, 1, 0, 1);
        Polynominal *ideal = createPolynominal(4,NULL, 1, 0, 2,1);
        Polynominal *result = createPolynominal(3,NULL, 2, 1, 2);
	QuotientPolynominalRing *ring = createQuotientPolynominalRing(ideal, INTEGER, NULL);

	ck_assert(error==INVERSION_ONLY_IN_QUOTIENT_RING);
	ck_assert(comparePolynominals(ring, inversePolynominal(ring, poly, NULL), result)==true);
	
	freePolynominal(poly);
	freePolynominal(ideal);
	freePolynominal(result);
	freeQuotientPolynominalRing(ring);

}
END_TEST*/



Suite * polynominal_suite(void)
{
	Suite * s;
	TCase * tc_comparison;
	TCase * tc_basic_operations;
	TCase * tc_generation;
	s=suite_create("Polynominal testing suite");

	tc_generation=tcase_create("Generate and polynominals");
	tcase_add_test(tc_generation, generation );
	suite_add_tcase(s, tc_generation);
	tc_comparison=tcase_create("Comparing two polynominals");
	tcase_add_test(tc_comparison, comparison);
	suite_add_tcase(s, tc_generation);

	tc_basic_operations=tcase_create("Basic operations on polynominal");
	tcase_add_test(tc_basic_operations, addition);
	tcase_add_test(tc_basic_operations, substraction);
	tcase_add_test(tc_basic_operations, multiplication);
	tcase_add_test(tc_basic_operations, division);
	
 	suite_add_tcase(s, tc_basic_operations);

	return s;

}


unsigned long fun(int k)
{
	return k;
}

int main(void)
{
#ifdef DEBUG_MEMORY	
START_DEBUG
#endif
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

 /*	Polynominal *a1 = createPolynominal(INTEGER, NULL, 4, 4);
	Polynominal *a2 = createPolynominal(INTEGER, NULL, 1, 3);

	Polynominal *result = multiplyPolynominals(ring, a1, a2, NULL);
	result = multiplyPolynominals(ring, a1, a2, NULL);
	result = multiplyPolynominals(ring, a1, a2, NULL);
	result = multiplyPolynominals(ring, a1, a2, NULL);
	printPolynominal(result, "");
	freePolynominal(a1);
	freePolynominal(a2);
	freePolynominal(result);
	//freeQuotientPolynominalRing(ring);
	printf()
	*/
   
	
/* 
	QuotientPolynominalRing * ring = createQuotientPolynominalRing(createPolynominal(INTEGER,NULL, NULL, 1, 2,0,6,1), 7, NULL);
//Polynominal *a = createPolynominal(INTEGER,ring, NULL, 1, 2,0,6,0);
	Polynominal *b = createPolynominal(INTEGER, ring, NULL, 1,2, 0, 6, 0, 2);
	//Polynominal *u;
	//Polynominal *v;
	//Polynominal *x  = extendedEuclid(a, b, &u, &v, ring);
	//printf("GCD: %d", gcdOfPolynomialCoefficients(a));
	//Polynominal * x = dividePolynominals(ring, a, b, u, NULL);
	//printPolynominal(a, "");
  //  printPolynominal(x, "FINALE: ");
//	printPolynominal(u, "FIRST:");
//	printPolynominal(v, "SECOND: ");
//	freePolynominal(x);
	Polynominal *t = invertPolynominal(b, ring);
	//printf("%d ", t);fflush(stdout);
	printPolynominal(t,"INVERTED POLYNOMINAL");
	freeQuotientPolynominalRing(ring);
	freePolynominal(b);
	freePolynominal(t);
//	freePolynominal(a);
//	freePolynominal(u);
  // freePolynominal(v);
*/	
//	printf("%d", countElements(h));

	QuotientPolynominalRing * ring = createQuotientPolynominalRing(createPolynominal(INTEGER,NULL, NULL, 1, 2,0,6,1), 0, NULL);
	Polynominal *a = createPolynominal(INTEGER,ring, NULL, 1, 2,0,6,1);
	Polynominal *b = createPolynominal(INTEGER, ring, NULL, 1,2, 0, 6, 0, 2);
	Polynominal *u;
	Polynominal *v;
	Polynominal *x  = extendedEuclid(a, b, &u, &v, ring);
	printPolynominal(x, "FINALE: ");
	printPolynominal(u, "FIRST:");
	printPolynominal(v, "SECOND: ");
	freePolynominal(b);
	freePolynominal(a);
	freePolynominal(u);
    freePolynominal(v);
	freePolynominal(x);
	freeQuotientPolynominalRing(ring);

	printUnallocatedMemory();
	
#ifdef DEBUG_MEMORY
	STOP_DEBUG;
#endif
	return 1;
	
	//Polynominal * x = createPolynominal(INTEGER, NULL,1);
    int number_failed;
    Suite *s; 
    SRunner *sr;
	//createPolynominal(INTEGER, NULL, 1, 2, 1);
    s = polynominal_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
	
   // printf("%d", number_failed);
	printf("\nMEMORY_DEBUG: %d \n", elements_allocated);
	printMemoryStatus();
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;





}
