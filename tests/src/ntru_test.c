#include "config.h"
#include <check.h>
#include <stdbool.h>
#include "ntru.h"

const int N=10;

START_TEST(crc_test)
{
    srand(time(NULL));
    uint8_t msg[N];

    for(int i=0; i<N; i++)
    {
        msg[i]=rand()%10;
    }

    uint8_t x = generateCRC(msg, N);
    
    ck_assert(checkCRC(msg, N, x)==true);
    
}
END_TEST

START_TEST(encode_test1)
{
    //short message
    ParametersPack params_pack ={.N=167, .p=7, .q=512, .d=71};
    KeyPackage keys = generateKey(params_pack);
    
    
    const char* msg1 = "Hello post-quantum world!";
    const char* cipher1 = encodeMessage(msg1, params_pack, keys.h);
    const char* decoded1 = decodeMessage(cipher1, params_pack, keys.f, keys.f_p_inverse);
    ck_assert(strcmp(msg1, decoded1)==true);


    const char* msg2 = "Hello post-quantum world! How good to see you from the other side of the lattice! We have come the long way! We have already dealed with modular arithmetic, we have implemented extended euclidean algorithm for polynomials \\
    basing on terribly bugged dividing function, we have dealed with statistical and probabilistic aspect of NTRU!";
    const char* cipher2 = encodeMessage(msg2, params_pack, keys.h);
    const char* decoded2 = decodeMessage(cipher2, params_pack, keys.f, keys.f_p_inverse);
    ck_assert(strcmp(msg2, decoded2)==true);




}



START_TEST(encode_test2)
{
    //short message
    ParametersPack params_pack ={.N=107, .p=5, .q=256, .d=31};
    KeyPackage keys = generateKey(params_pack);
    
    
    const char* msg1 = "Hello post-quantum world!";
    const char* cipher1 = encodeMessage(msg1, params_pack, keys.h);
    const char* decoded1 = decodeMessage(cipher1, params_pack, keys.f, keys.f_p_inverse);
    ck_assert(strcmp(msg1, decoded1)==true);


    const char* msg2 = "Hello post-quantum world! How good to see you from the other side of the lattice! We have come the long way! We have already dealed with modular arithmetic, we have implemented extended euclidean algorithm for polynomials \\
    basing on terribly bugged dividing function, we have dealed with statistical and probabilistic aspect of NTRU!";
    const char* cipher2 = encodeMessage(msg2, params_pack, keys.h);
    const char* decoded2 = decodeMessage(cipher2, params_pack, keys.f, keys.f_p_inverse);
    ck_assert(strcmp(msg2, decoded2)==true);




}




END_TEST

Suite * ntru_suite(void)
{
	Suite * s;
	TCase * tc_crc;
	TCase * tc_encrypt;
	s=suite_create("NTRUEncrypt testing suite");

	tc_crc=tcase_create("Check Cyclic Redundancy Code");
	tcase_add_test(tc_crc, crc_test);
	suite_add_tcase(s, tc_crc);

    tc_encrypt=tcase_create("Check whether NTRU can encrypt and decrypt the message");
    tcase_add_test(tc_encrypt, encode_test1);
    tcase_add_test(tc_encrypt,encode_test2);
    suite_add_tcase(s, tc_encrypt);

	return s;

}



int main()
{
   
    int number_failed;
    Suite *s; 
    SRunner *sr;
	//createPolynomial(INTEGER, NULL, 1, 2, 1);
    s =ntru_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
	
   // printf("%d", number_failed);
	//printf("\nMEMORY_DEBUG: %d \n", elements_allocated);
	//printMemoryStatus();

    return (number_failed == 0) ? 0 : 1;

}