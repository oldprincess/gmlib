#if !(defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2))
void test_mpz_common_add_carry();
void test_mpz_common_mul();
void test_mpz_common_sub_borrow();

void test_mpz_common()
{
    test_mpz_common_add_carry();
    test_mpz_common_mul();
    test_mpz_common_sub_borrow();
}
#else
void test_mpz_common()
{
}
#endif