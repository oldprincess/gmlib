void test_sm2_fn_add();
void test_sm2_fn_inv();
void test_sm2_fn_mul();
void test_sm2_fn_sqr();
void test_sm2_fn_sub();

void test_sm2_fp_add();
void test_sm2_fp_dbl();
void test_sm2_fp_inv();
void test_sm2_fp_mul();
void test_sm2_fp_neg();
void test_sm2_fp_sqr();
void test_sm2_fp_sqrt();
void test_sm2_fp_sub();
void test_sm2_fp_tpl();

void test_sm2p256v1()
{
    test_sm2_fn_add();
    test_sm2_fn_inv();
    test_sm2_fn_mul();
    test_sm2_fn_sqr();
    test_sm2_fn_sub();

    test_sm2_fp_add();
    test_sm2_fp_dbl();
    test_sm2_fp_inv();
    test_sm2_fp_mul();
    test_sm2_fp_neg();
    test_sm2_fp_sqr();
    test_sm2_fp_sqrt();
    test_sm2_fp_sub();
    test_sm2_fp_tpl();
}