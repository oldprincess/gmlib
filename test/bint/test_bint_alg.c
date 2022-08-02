#include <gmlib/bint.h>
#include <gmlib/err.h>
#include <stdlib.h>
#include <string.h>

static void test_alg1();
static void test_shift();
static void test_pow1();
static void test_pow2();
void test_bint_alg() {
    test_alg1();
    test_shift();
    test_pow1();
    test_pow2();
}

static void test_alg1() {
    char* x_dec =
        "8843831488639197702090570126856729465584991286633792804918946311271029"
        "579295";
    char* y_dec =
        "9319360923209885734809144475426267514259734266156897706546267125481039"
        "70477";
    char* x_add_y_dec =
        "9775767580960186275571484574399356217010964713249482575573573023819133"
        "549772";
    char* x_sub_y_dec =
        "7911895396318209128609655679314102714159017860018103034264319598722925"
        "608818";
    char* x_mul_y_dec =
        "8241885758667725158145554270852742020098271580556199243911513995772367"
        "7119565123244136848328359672090446279116902162905190471158694735769153"
        "00410473715";
    char* x_div_y_dec = "9";
    char* x_mod_y_dec =
        "4564066577503005407623400989730887027512304470925848690273058983380938"
        "45002";

    BINT x, y, z1, z2;
    // test add
    try_goto(bint_from_str(&x, x_dec, BINT_DEC));
    try_goto(bint_from_str(&y, y_dec, BINT_DEC));
    try_goto(bint_from_str(&z1, x_add_y_dec, BINT_DEC));

    try_goto(bint_add(&z2, &x, &y));  // x+y
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_add");
        goto error;
    }

    try_goto(bint_add(&z2, &y, &x));  // y+x
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_add");
        goto error;
    }
    bint_neg(&x, &x);
    try_goto(bint_sub(&z2, &y, &x));  // y-(-x)
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_sub");
        goto error;
    }
    // test sub
    try_goto(bint_from_str(&x, x_dec, BINT_DEC));
    try_goto(bint_from_str(&y, y_dec, BINT_DEC));
    try_goto(bint_from_str(&z1, x_sub_y_dec, BINT_DEC));

    try_goto(bint_sub(&z2, &x, &y));  // x-y
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_sub");
        goto error;
    }
    bint_neg(&y, &y);                 // -y
    try_goto(bint_add(&z2, &x, &y));  // x+(-y)
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_add");
        goto error;
    }
    try_goto(bint_add(&z2, &y, &x));  // (-y)+x
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_add");
        goto error;
    }
    bint_neg(&x, &x);                 // -x
    try_goto(bint_sub(&z2, &y, &x));  // (-y)-(-x)
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_sub");
        goto error;
    }

    // test mul
    try_goto(bint_from_str(&x, x_dec, BINT_DEC));
    try_goto(bint_from_str(&y, y_dec, BINT_DEC));
    try_goto(bint_from_str(&z1, x_mul_y_dec, BINT_DEC));

    try_goto(bint_mul(&z2, &x, &y));  // x*y
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_mul");
        goto error;
    }
    try_goto(bint_mul(&z2, &y, &x));  // y*x
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_mul");
        goto error;
    }
    bint_neg(&x, &x);
    bint_neg(&y, &y);
    try_goto(bint_mul(&z2, &x, &y));  // (-x)*(-y)
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_mul");
        goto error;
    }
    // test div
    try_goto(bint_from_str(&x, x_dec, BINT_DEC));
    try_goto(bint_from_str(&y, y_dec, BINT_DEC));
    try_goto(bint_from_str(&z1, x_div_y_dec, BINT_DEC));

    try_goto(bint_divmod(&z2, NULL, &x, &y));  // x/y
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_div");
        goto error;
    }
    // test mod
    try_goto(bint_from_str(&z1, x_mod_y_dec, BINT_DEC));

    try_goto(bint_divmod(NULL, &z2, &x, &y));  // x%y
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_add");
        goto error;
    }

    return;
error:
    exit(-1);
}

static void test_shift() {
    char* x_dec = "307839308792102039737608520265752119502";
    BINT x, z1, z2;
    try_goto(bint_from_str(&x, x_dec, BINT_DEC));
    // text sll
    try_goto(bint_sll(&z1, &x, 12));
    try_goto(bint_mul_u32(&z2, &x, 1 << 12));
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_sll");
        goto error;
    }
    // text sra
    try_goto(bint_sra(&z1, &x, 12));
    try_goto(bint_divmod_u32(&z2, NULL, &x, 1 << 12));
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_sra");
        goto error;
    }

    // text sll
    try_goto(bint_sll(&z1, &x, 0));
    bint_copy(&z2, &x);
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_sll");
        goto error;
    }
    // text sra
    try_goto(bint_sra(&z1, &x, 0));
    bint_copy(&z2, &x);
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_sra");
        goto error;
    }
    return;
error:
    exit(-1);
}

static void test_pow1() {
    char* x_dec = "307839308792102039737608520265752119502";
    char* m_dec = "320295952621962597036354399329644264845";
    char* z_dec = "232143115812353298984138825506207922349";
    uint32_t e = 16716066;

    BINT x, m, z1, z2;
    try_goto(bint_from_str(&x, x_dec, 10));
    try_goto(bint_from_str(&m, m_dec, 10));
    try_goto(bint_from_str(&z1, z_dec, 10));
    try_goto(bint_pow_u32(&z2, &x, e, &m));
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_pow_u32");
        goto error;
    }

    return;
error:
    exit(-1);
}

static void test_pow2() {
    char* x_dec = "307839308792102039737608520265752119502";
    char* y_dec = "307839308792102039737608520265752119502";
    char* m_dec = "320295952621962597036354399329644264845";
    char* z_dec = "239093530782924349700424740994457940524";

    BINT x, y, m, z1, z2;
    try_goto(bint_from_str(&x, x_dec, 10));
    try_goto(bint_from_str(&y, y_dec, 10));
    try_goto(bint_from_str(&m, m_dec, 10));
    try_goto(bint_from_str(&z1, z_dec, 10));
    try_goto(bint_pow(&z2, &x, &y, &m));
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_pow");
        goto error;
    }

    char* x_dec2 = "1008990073325912288538836573062";
    char* y_dec2 = "563913050187841372353561918701";
    char* m_dec2 = "1127826100375682744707123837403";
    char* z_dec2 = "1127826100375682744707123837402";
    try_goto(bint_from_str(&x, x_dec2, 10));
    try_goto(bint_from_str(&y, y_dec2, 10));
    try_goto(bint_from_str(&m, m_dec2, 10));
    try_goto(bint_from_str(&z1, z_dec2, 10));
    try_goto(bint_pow(&z2, &x, &y, &m));
    if (bint_cmp(&z1, &z2) != 0) {
        ERR_LOG("Err in bint_pow");
        goto error;
    }
    return;

error:
    exit(-1);
}
