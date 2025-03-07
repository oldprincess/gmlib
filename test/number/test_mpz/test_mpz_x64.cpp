#include <gmlib/number/config.h>

#if defined(NUMBER_IMPL_MPZ_X64)

void test_mpz_x64_add_carry();
void test_mpz_x64_mul();
void test_mpz_x64_sub_borrow();

void test_mpz_x64()
{
    test_mpz_x64_add_carry();
    test_mpz_x64_mul();
    test_mpz_x64_sub_borrow();
}
#else
void test_mpz_x64()
{
}
#endif