void test_sm9_bn_mod_n_sub1_ex();

void test_sm9_fn_add();
void test_sm9_fn_inv();
void test_sm9_fn_mul();
void test_sm9_fn_sqr();
void test_sm9_fn_sub();

void test_sm9_fp_add();
void test_sm9_fp_dbl();
void test_sm9_fp_inv();
void test_sm9_fp_mul();
void test_sm9_fp_neg();
void test_sm9_fp_sqr();
void test_sm9_fp_sqrt();
void test_sm9_fp_sub();
void test_sm9_fp_tpl();

void test_sm9_field()
{
    test_sm9_bn_mod_n_sub1_ex();

    test_sm9_fn_add();
    test_sm9_fn_inv();
    test_sm9_fn_mul();
    test_sm9_fn_sqr();
    test_sm9_fn_sub();

    test_sm9_fp_add();
    test_sm9_fp_dbl();
    test_sm9_fp_inv();
    test_sm9_fp_mul();
    test_sm9_fp_neg();
    test_sm9_fp_sqr();
    test_sm9_fp_sqrt();
    test_sm9_fp_sub();
    test_sm9_fp_tpl();
}