#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "quotient_polynominal_ring.h"
#include "polynominal.h"
#include <stdbool.h>
#include "config.h"
START_TEST(generation)
{
	int error;

	Polynominal *poly = createPolynominal(5,&error, 2, 3, 0, 2, 1);
	ck_assert(error==OK);
	freePolynominal(poly);

	poly=createPolynominal(5,&error, 2, 3);
	ck_assert(error==WRONG_POLYNOMINAL_COEFFICIENTS);
	freePolynominal(poly);

	poly=createPolynominal(5, &error, 0, 2, 1, 2, 1);
	ck_assert(error==WRONG_POLYNOMINAL_COEFFICIENTS);
	freePolynominal(poly);

	Polynominal *ideal = createPolynominal(5, &error, 2.5, 3.1, 0, 2.1, 1.4);
	ck_assert(error==OK);

	QuotientPolynominalRing *ring = createQuotientPolynominalRing(ideal, REAL, &error);
	ck_assert(error==OK);

	ring=createQuotientPolynominalRing(ideal, INTEGER, &error);
	ck_assert(error==WRONG_POLYNOMINAL_COEFFICIENTS);

	ring=createQuotientPolynominalRing(NULL, INTEGER, &error);
	ck_assert(error==OK);


	freePolynominal(ideal);
	freeQuotientPolynominalRing(ring);
}
END_TEST

START_TEST(comparison)
{
	int error;
	Polynominal *poly1=createPolynominal(5,&error, 2, 3, 0, 2, 1);
	Polynominal *poly2=createPolynominal(5,&error, 2, 3, 0, 2, 1);

	ck_assert(comparePolynominals(NULL, poly1, poly2)==true);

	Polynominal *poly3=createPolynominal(4, &error,2, 3, 1, 2);

	ck_assert(comparePolynominals(NULL, poly1, poly3)==false);

	Polynominal *poly4=createPolynominal(5, &error,2.0, 3.0, 0, 2.0, 1.0);
	ck_assert(comparePolynominals(NULL, poly1, poly4)==true);

	Polynominal *poly5 = createPolynominal(4,&error, 1, 2, 0, 0);
	Polynominal *poly6 = createPolynominal(3,&error, 2, 1, 2);
	Polynominal *ideal = createPolynominal(4,&error, 1, 0, 2, 1);
	QuotientPolynominalRing *ring = createQuotientPolynominalRing(ideal, INTEGER, &error);
	ck_assert(comparePolynominals(ring, poly5, poly6)==true);
	ck_assert(comparePolynominals(ring, poly5,poly1)==false);
	
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
	Polynominal *poly1 = createPolynominal(4,NULL, 2, 3, 1, 2);
	Polynominal *poly2 = createPolynominal(3, NULL,2, 1, 0);
	
	Polynominal *result = createPolynominal(4, NULL, 2, 5, 2, 2);
	ck_assert(comparePolynominals(NULL, addPolynominals(NULL, poly1, poly2, NULL), result));
	
	
	freePolynominal(poly1);
	freePolynominal(poly2);
	freePolynominal(result);

}
END_TEST

START_TEST(substraction)
{
        Polynominal *poly1 = createPolynominal(3,NULL, 2, 1, 2);
        Polynominal *poly2 = createPolynominal(3, NULL, 2, 1, 0);
        Polynominal *result = createPolynominal(1,NULL, 2);
        ck_assert(comparePolynominals(NULL, substractPolynominals(NULL, poly1, poly2, NULL), result));

	freePolynominal(poly1);
        freePolynominal(poly2);
        freePolynominal(result);

}
END_TEST

START_TEST(multiplication)
{
	Polynominal *poly1 = createPolynominal(3, NULL, 2, 1, 2);
        Polynominal *poly2 = createPolynominal(3, NULL,2, 1, 0);
        Polynominal *result = createPolynominal(5, NULL,4, 4, 5, 2, 0);
        ck_assert(comparePolynominals(NULL, multiplyPolynominals(NULL, poly1, poly2, NULL), result));

        freePolynominal(poly1);
        freePolynominal(poly2);
        freePolynominal(result);
}
END_TEST

START_TEST(division)
{
	Polynominal *poly1 = createPolynominal(4, NULL,1, -4, 2, -3);
        Polynominal *poly2 = createPolynominal(2, NULL,1, 2);
        Polynominal *result = createPolynominal(3,NULL, 1, -6, 14);
        Polynominal *rest = createPolynominal(1, NULL, -31);
	Polynominal _rest;
	ck_assert(comparePolynominals(NULL, dividePolynominals(NULL, poly1, poly2,&_rest, NULL), result)==true);
	ck_assert(comparePolynominals(NULL, &_rest, rest)==true);
        freePolynominal(poly1);
        freePolynominal(poly2);
        freePolynominal(result);
	freePolynominal(rest);
}
END_TEST

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
END_TEST



Suite * polynominal_suite(void)
{
	Suite * s;
	TCase * tc_comparison;
	TCase * tc_basic_operations;
	TCase * tc_generation;
	s=suite_create("Polynominal testing suite");

	tc_generation=tcase_create("Generate and polynominals");
	tcase_add_test(tc_generation, generation );

	tc_comparison=tcase_create("Compraing two polynominals");
	tcase_add_test(tc_basic_operations, comparison);


	tc_basic_operations=tcase_create("Basic operations on polynominal");
	tcase_add_test(tc_basic_operations, addition);
	tcase_add_test(tc_basic_operations, substraction);
	tcase_add_test(tc_basic_operations, multiplication);
	tcase_add_test(tc_basic_operations, division);
	tcase_add_test(tc_basic_operations, inversion);
 	suite_add_tcase(s, tc_basic_operations);

	return s;

}





int main(void)
{

    int number_failed;
    Suite *s;
    SRunner *sr;

    s = polynominal_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("%d", number_failed);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

}
