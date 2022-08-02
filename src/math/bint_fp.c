#include <gmlib/err.h>
#include <gmlib/math.h>

int fp_add(BINT* r, BINT* n1, BINT* n2, BINT* p) {
    if (!bint_is_pos(p)) {
        ERR_LOG("FiniteField Error, p need be positive");
        goto error;
    }

    BINT t;
    try_goto(bint_add(&t, n1, n2));
    try_goto(bint_divmod(NULL, &t, &t, p));
    if (bint_is_neg(&t)) {
        try_goto(bint_add(&t, &t, p));
    } else {
        bint_copy(r, &t);
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

int fp_sub(BINT* r, BINT* n1, BINT* n2, BINT* p) {
    if (!bint_is_pos(p)) {
        ERR_LOG("FiniteField Error, p need be positive");
        goto error;
    }

    BINT t;
    try_goto(bint_sub(&t, n1, n2));
    try_goto(bint_divmod(NULL, &t, &t, p));
    if (bint_is_neg(&t)) {
        try_goto(bint_add(r, &t, p));
    } else {
        bint_copy(r, &t);
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

int fp_mul(BINT* r, BINT* n1, BINT* n2, BINT* p) {
    if (!bint_is_pos(p)) {
        ERR_LOG("FiniteField Error, p need be positive");
        goto error;
    }

    BINT t;
    try_goto(bint_mul(&t, n1, n2));
    try_goto(bint_divmod(NULL, &t, &t, p));
    if (bint_is_neg(&t)) {
        try_goto(bint_add(r, &t, p));
    } else {
        bint_copy(r, &t);
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

int fp_mul_u32(BINT* r, BINT* n1, uint32_t n2, BINT* p) {
    if (!bint_is_pos(p)) {
        ERR_LOG("FiniteField Error, p need be positive");
        goto error;
    }

    BINT t;
    try_goto(bint_mul_u32(&t, n1, n2));
    try_goto(bint_divmod(NULL, &t, &t, p));
    if (bint_is_neg(&t)) {
        try_goto(bint_add(r, &t, p));
    } else {
        bint_copy(r, &t);
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

int fp_sqr(BINT* r, BINT* n, BINT* p) {
    if (!bint_is_pos(p)) {
        ERR_LOG("FiniteField Error, p need be positive");
        goto error;
    }

    BINT t;
    try_goto(bint_sqr(&t, n));
    try_goto(bint_divmod(NULL, &t, &t, p));
    if (bint_is_neg(&t)) {
        try_goto(bint_add(r, &t, p));
    } else {
        bint_copy(r, &t);
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

int fp_pow(BINT* r, BINT* n, BINT* e, BINT* p) {
    if (!bint_is_pos(p)) {
        ERR_LOG("FiniteField Error, p need be positive");
        goto error;
    }

    BINT t;
    try_goto(bint_pow(r, n, e, p));
    if (bint_is_neg(&t)) {
        try_goto(bint_add(r, &t, p));
    } else {
        bint_copy(r, &t);
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

int fp_neg(BINT* r, BINT* n, BINT* p) {
    if (!bint_is_pos(p)) {
        ERR_LOG("FiniteField Error, p need be positive");
        goto error;
    }

    try_goto(fp_sub(r, p, n, p));

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
