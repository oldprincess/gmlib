#include <gmlib/bint.h>
#include <gmlib/err.h>

/// @brief 大整数求幂
int bint_pow(BINT* r, BINT* n, BINT* e, BINT* mod) {
    BINT f, result;
    bint_copy(&f, n);
    bint_from_u32(&result, 1);
    // 快速幂
    int bits_size = bint_bits_len(e);
    for (int ei = 0; ei < bits_size; ei++) {
        if (bint_bits_at(e, ei) == 1) {
            if (mod != NULL) {
                try_goto(bint_mul(&result, &result, &f));
                try_goto(bint_divmod(NULL, &result, &result, mod));
            } else {
                try_goto(bint_mul(&result, &result, &f));
            }
        }
        if (mod != NULL) {
            try_goto(bint_sqr(&f, &f));
            try_goto(bint_divmod(NULL, &f, &f, mod));
        } else {
            try_goto(bint_sqr(&f, &f));
        }
    }
    bint_copy(r, &result);

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

///// @brief 大整数求幂
// int bint_pow(BINT* r, BINT* n, BINT* e, BINT* mod) {
//    BINT f, result;
//    bint_copy(&f, n);
//    bint_from_u32(&result, 1);
//    // 快速幂
//    for (int ei = 0; ei < e->dsize; ei++) {
//        uint32_t exp = e->d[ei];
//        for (int j = 0; j < 32; j++) {
//            // 结束条件判断
//            if (exp == 0 && ei == e->dsize - 1) {
//                break;
//            }
//            // 快速幂
//            if ((exp & 1) == 1) {
//                if (mod != NULL) {
//                    try_goto(bint_mod_mul(&result, &result, &f, mod));
//                } else {
//                    try_goto(bint_mul(&result, &result, &f));
//                }
//            }
//            if (mod != NULL) {
//                try_goto(bint_mod_sqr(&f, &f, mod));
//            } else {
//                try_goto(bint_sqr(&f, &f));
//            }
//            exp = exp >> 1;
//        }
//    }
//    bint_copy(r, &result);

//    return ERR_NOERROR;
// error:
//    return ERR_RUNTIME_ERROR;
//}

/// @brief 大整数求幂
int bint_pow_u32(BINT* r, BINT* n, uint32_t e, BINT* mod) {
    BINT f, result;
    bint_copy(&f, n);
    bint_from_u32(&result, 1);
    while (e) {
        if ((e & 1) == 1) {
            if (mod != NULL) {
                try_goto(bint_mul(&result, &result, &f));
                try_goto(bint_divmod(NULL, &result, &result, mod));
            } else {
                try_goto(bint_mul(&result, &result, &f));
            }
        }
        if (mod != NULL) {
            try_goto(bint_sqr(&f, &f));
            try_goto(bint_divmod(NULL, &f, &f, mod));
        } else {
            try_goto(bint_sqr(&f, &f));
        }
        e = e >> 1;
    }
    bint_copy(r, &result);

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
