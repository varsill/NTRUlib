#include "rationals.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

START_TEST(generation)
{
    Rational a=createRational(2, 5);
    Rational b = createRational(2, -5);
    ck_assert(a.nominator==2 && a.denominator==5);
    ck_assert(b.nominator==-2&&b.denominator==5);
    Rational c=createRational(2.5);
    ck_assert((float)c.nominator/c.denominator==2.5);

}
END_TEST

START_TEST(comparison)
{
    Rational a=createRational(2, 5);
    Rational b = createRational(4, 10);
    Rational c=createRational(2, -5);
    Rational d=createRational(-2, -5);
    ck_assert(compareRationals(&a, &b)==true);
    ck_assert(compareRationals(&a, &c)==false);
    ck_assert(compareRationals(&a, &d)==true);
    
}
END_TEST


START_TEST(addition)
{
    Rational a=createRational(2, 5);
    Rational b=createRational(1, 12);
    Rational result=addRationals(&a, &b);
    Rational expected_result = createRational(29, 60);
    ck_assert(compareRationals(&result, &expected_result)==true);
   
    
}
END_TEST

START_TEST(substraction)
{
    Rational a=createRational(29, 60);
    Rational b=createRational(1, 12);
    Rational result=substractRationals(&a, &b);
    Rational expected_result = {2, 5};
    ck_assert(compareRationals(&result, &expected_result)==true);
   
}
END_TEST

START_TEST(multiplication)
{
    Rational a=createRational(3, 7);
    Rational b=createRational(1, 12);
    Rational result=multiplyRationals(&a, &b);
    Rational expected_result = createRational(3, 84);
    ck_assert(compareRationals(&result, &expected_result)==true);
}
END_TEST

START_TEST(division)
{
    Rational a=createRational(4, 5);
    Rational b=createRational(1, 5);
    Rational result=divideRationals(&a, &b);
    Rational expected_result = createRational(4, 1);
    ck_assert(compareRationals(&result, &expected_result)==true);
}
END_TEST


START_TEST(inversion)
{
    Rational a=createRational(29, 60);
    Rational result=inverseRational(&a);
    Rational expected_result = createRational(60, 29);
    ck_assert(compareRationals(&result, &expected_result)==true);

}
END_TEST


Suite * rationals_suite()
{
    Suite *s;
    TCase *tc_generation;
    TCase *tc_comparison;
    TCase *tc_basic_operations;

    s=suite_create("Rational numbers testing suite");
    
    tc_generation=tcase_create("Generating rational numbers");
    tcase_add_test(tc_generation, generation);
    suite_add_tcase(s,tc_generation);

    tc_comparison=tcase_create("Comparing rational numbers");
    tcase_add_test(tc_comparison, comparison);
    suite_add_tcase(s,tc_comparison);


    tc_basic_operations=tcase_create("Testing basic arithmetic operations on rational numbers");
    tcase_add_test(tc_basic_operations, addition);
    tcase_add_test(tc_basic_operations, substraction);
    tcase_add_test(tc_basic_operations, multiplication);
    tcase_add_test(tc_basic_operations, division);
    tcase_add_test(tc_basic_operations, inversion);

    suite_add_tcase(s,tc_basic_operations);
    return s;
}


int main()
{
    int number_failed;
    Suite *s; 
    SRunner *sr;
	
    s =rationals_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
	
   // printf("%d", number_failed);
	//printf("\nMEMORY_DEBUG: %d \n", elements_allocated);
	//printMemoryStatus();
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

}




