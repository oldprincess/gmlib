#include <gmlib/number/internal/bn_common.h>

#include <cassert>

#include "bn.inc.h"

#define GMLIB_CATCH_ERROR(exp) \
    do                         \
    {                          \
        err_code = exp;        \
        if (err_code != 0)     \
        {                      \
            goto end;          \
        }                      \
    } while (0)

namespace number::internal::common {

static int bn_uadd(BigNum_st*       r,
                   const BigNum_st* a,
                   const BigNum_st* b) noexcept
{
    const BigNum_st* big   = a->data_len > b->data_len ? a : b;
    const BigNum_st* small = a->data_len > b->data_len ? b : a;

    int         err_code = 0;
    std::size_t i        = 0;
    int         carry    = 0;

    if (r->MAX_DSIZE < big->data_len)
    {
        err_code = -1;
        goto end;
    }

    for (; i < small->data_len; i++)
    {
        carry = _add_carry(&r->data[i], big->data[i], small->data[i], carry);
    }
    for (; i < big->data_len; i++)
    {
        carry = _add_carry(&r->data[i], big->data[i], 0, carry);
    }
    r->data_len = big->data_len;
    if (carry > 0)
    {
        if (r->MAX_DSIZE >= r->data_len + 1)
        {
            r->data[r->data_len] = carry;
            r->data_len += 1;
        }
        else
        {
            err_code = -1;

            goto end;
        }
    }
end:
    return err_code;
}

static int bn_usub(BigNum_st*       r,
                   const BigNum_st* a,
                   const BigNum_st* b) noexcept
{
    assert(bn_ucmp(a, b) >= 0);

    int         err_code = 0;
    std::size_t i        = 0;
    int         borrow   = 0;

    if (r->MAX_DSIZE < a->data_len)
    {
        err_code = -1;

        goto end;
    }

    for (; i < b->data_len; i++)
    {
        borrow = _sub_borrow(&r->data[i], a->data[i], b->data[i], borrow);
    }
    for (; i < a->data_len; i++)
    {
        borrow = _sub_borrow(&r->data[i], a->data[i], 0, borrow);
    }
    r->data_len = a->data_len;
    while (r->data_len > 0 && r->data[r->data_len - 1] == 0)
    {
        r->data_len -= 1;
    }

end:
    return err_code;
}

int bn_add(BigNum_st* r, const BigNum_st* a, const BigNum_st* b) noexcept
{
    int err_code = 0;
    int cmp      = 0;
    if (a->sign == b->sign)
    {
        // (0) + (0) -> (0)
        // (+) + (+) -> (+)
        // (-) + (-) -> (-)
        r->sign = a->sign;
        GMLIB_CATCH_ERROR(bn_uadd(r, a, b));
        goto end;
    }

    cmp = bn_ucmp(a, b);
    if (cmp == 1)
    {
        r->sign = a->sign;
        GMLIB_CATCH_ERROR(bn_usub(r, a, b));
    }
    else if (cmp == -1)
    {
        r->sign = b->sign;
        GMLIB_CATCH_ERROR(bn_usub(r, b, a));
    }
    else
    {
        bn_set_zero(r);
    }
end:
    return err_code;
}

int bn_sub(BigNum_st* r, const BigNum_st* a, const BigNum_st* b) noexcept
{
    int err_code = 0;
    int cmp      = 0;
    if (a->sign != b->sign)
    {
        // (+) - (0) -> (+), (+) - (-) -> (+)
        // (0) - (+) -> (-), (0) - (-) -> (+)
        // (-) - (+) -> (-), (-) - (0) -> (-)
        r->sign = (a->sign != 0) ? a->sign : -(b->sign);
        GMLIB_CATCH_ERROR(bn_uadd(r, a, b));
        goto end;
    }

    cmp = bn_ucmp(a, b);
    if (cmp == 1)
    {
        r->sign = a->sign;
        GMLIB_CATCH_ERROR(bn_usub(r, a, b));
    }
    else if (cmp == -1)
    {
        r->sign = -(b->sign);
        GMLIB_CATCH_ERROR(bn_usub(r, b, a));
    }
    else
    {
        bn_set_zero(r);
    }
end:
    return err_code;
}

static int bn_umul(BigNum_st*       r,
                   const BigNum_st* a,
                   const BigNum_st* b) noexcept
{
    int err_code = 0;
    if (r->MAX_DSIZE < a->data_len + b->data_len)
    {
        err_code = -1;

        goto end;
    }

    for (std::size_t i = 0; i < a->data_len; i++)
    {
        r->data[i] = 0;
    }
    for (std::size_t ib = 0; ib < b->data_len; ib++)
    {
        std::uint32_t carry = 0;
        for (std::size_t ia = 0; ia < a->data_len; ia++)
        {
            carry = _mul_add_carry(&r->data[ib + ia], a->data[ia], b->data[ib],
                                   r->data[ib + ia], carry);
        }
        r->data[ib + a->data_len] = carry;
    }
    r->data_len = a->data_len + b->data_len;
    while (r->data_len > 0 && r->data[r->data_len - 1] == 0)
    {
        r->data_len -= 1;
    }
end:
    return err_code;
}

int bn_mul(BigNum_st* r, const BigNum_st* a, const BigNum_st* b) noexcept
{
    int        err_code = 0;
    BigNum_st* t        = NULL;
    // (+) x (+) -> (+), (+) x (0) -> (0), (+) x (-) -> (-)
    // (0) x (+) -> (0), (0) x (0) -> (0), (0) x (-) -> (0)
    // (-) x (+) -> (-), (-) x (0) -> (0), (-) x (-) -> (+)
    int r_sign = a->sign * b->sign;
    if (r_sign == 0)
    {
        bn_set_zero(r);
        goto end;
    }
    if (r != a && r != b)
    {
        GMLIB_CATCH_ERROR(bn_umul(r, a, b));
        r->sign = r_sign;
        goto end;
    }

    GMLIB_CATCH_ERROR(bn_alloc(&t, 32 * (a->data_len + b->data_len)));
    GMLIB_CATCH_ERROR(bn_umul(t, a, b));
    t->sign = r_sign;
    GMLIB_CATCH_ERROR(bn_cpy(r, t));
end:
    if (t != NULL)
    {
        bn_free(t);
    }
    return err_code;
}

int bn_umul32_uadd32(BigNum_st*       r,
                     const BigNum_st* a,
                     std::uint32_t    mul_val,
                     std::uint32_t    add_val) noexcept
{
    int           err_code = 0;
    std::uint32_t carry    = 0;
    if (mul_val == 0)
    {
        if (add_val == 0)
        {
            r->data_len = 0;
        }
        else
        {
            r->data_len = 1;
            r->data[0]  = add_val;
        }
        goto end;
    }

    if (r->MAX_DSIZE < a->data_len)
    {
        err_code = -1;
        goto end;
    }

    carry = add_val;
    for (std::size_t i = 0; i < a->data_len; i++)
    {
        carry = _mul_carry(&r->data[i], a->data[i], mul_val, carry);
    }
    r->data_len = a->data_len;
    if (carry)
    {
        if (r->MAX_DSIZE < r->data_len + 1)
        {
            err_code = -1;
            goto end;
        }
        r->data[r->data_len] = carry;
        r->data_len += 1;
    }
end:
    return err_code;
}
} // namespace number::internal::common
