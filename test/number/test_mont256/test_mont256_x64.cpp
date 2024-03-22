void test_mont256_x64_add();
void test_mont256_x64_dbl();
void test_mont256_x64_div2();
void test_mont256_x64_from_bytes_ex();
void test_mont256_x64_inv();
void test_mont256_x64_mul();
void test_mont256_x64_neg();
void test_mont256_x64_pow();
void test_mont256_x64_sqr();
void test_mont256_x64_sub();
void test_mont256_x64_tpl();

void test_mont256_x64()
{
    test_mont256_x64_add();
    test_mont256_x64_dbl();
    test_mont256_x64_div2();
    test_mont256_x64_from_bytes_ex();
    test_mont256_x64_inv();
    test_mont256_x64_mul();
    test_mont256_x64_neg();
    test_mont256_x64_pow();
    test_mont256_x64_sqr();
    test_mont256_x64_sub();
    test_mont256_x64_tpl();
}