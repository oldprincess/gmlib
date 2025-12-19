#include <gmlib/number/internal/bn_common.h>

#include <cassert>
#include <cstring>

#include "bn.inc.h"

namespace number::internal::common {

#define GMLIB_CATCH_ERROR(exp) \
    do                         \
    {                          \
        err_code = exp;        \
        if (err_code != 0)     \
        {                      \
            goto end;          \
        }                      \
    } while (0)

#define u_ge_zero(i) ((size_t)(i) < (size_t)(-1))

static inline std::uint32_t divmod(std::uint32_t *q,
                                   std::uint64_t  a,
                                   std::uint32_t  b) noexcept
{
    assert(b != 0);
    *q = (a / b) & UINT32_MAX;
    return (std::uint32_t)(a - (*q) * b);
}

int bn_udivmod32(BigNum_st       *q,
                 std::uint32_t   *r,
                 const BigNum_st *a,
                 std::uint32_t    b) noexcept
{
    int           err_code = 0;
    std::uint64_t rem      = 0, tmp;

    if (b == 0)
    {
        return -1;
    }
    if (q->MAX_DSIZE < a->data_len)
    {
        err_code = -1;
        goto end;
    }

    for (size_t i = a->data_len - 1; u_ge_zero(i); i--)
    {
        tmp = (rem << 32) | a->data[i];
        rem = (std::uint64_t)divmod(&q->data[i], tmp, b);
    }

    q->data_len = a->data_len;
    while (q->data_len > 0 && q->data[q->data_len - 1] == 0)
    {
        q->data_len -= 1;
    }
    *r = (std::uint32_t)rem;
end:
    return err_code;
}

static int bn_umod32(std::uint32_t   *r,
                     const BigNum_st *a,
                     std::uint32_t    b) noexcept
{
    if (b == 0)
    {
        return -1;
    }
    std::uint64_t rem = 0, tmp;
    for (int64_t i = a->data_len - 1; u_ge_zero(i); i--)
    {
        tmp = (rem << 32) | a->data[i];
        rem = tmp % b;
    }
    *r = (std::uint32_t)rem;

    return 0;
}

static void mem_sll(std::uint32_t       *r,
                    size_t              *rLen,
                    const std::uint32_t *d,
                    size_t               dLen,
                    size_t               bits) noexcept
{
    *rLen = dLen;
    if (bits == 0)
    {
        // bits=0
        std::memcpy(r, d, dLen * 4);
        return;
    }
    std::uint32_t carry = 0;
    for (size_t i = 0; i < dLen; i++)
    {
        // r[i] = r[i]<<b | r[i-1]>>(32-b)
        std::uint32_t tmp = d[i] << bits | carry;
        carry             = d[i] >> (32 - bits);
        r[i]              = tmp;
    }
    if (carry != 0)
    {
        r[*rLen] = carry;
        (*rLen)++;
    }
}

static void mem_srl(std::uint32_t       *r,
                    size_t              *rLen,
                    const std::uint32_t *d,
                    size_t               dLen,
                    size_t               bits) noexcept
{
    *rLen = dLen;
    if (bits == 0)
    {
        // bits=0
        std::memcpy(r, d, dLen * 4);
        return;
    }
    std::uint32_t carry = 0;
    for (size_t i = dLen - 1; u_ge_zero(i); i--)
    {
        // r[i] = d[i+1]<<(32-b) | d[i]>>b
        std::uint32_t tmp = carry | (d[i] >> bits);
        carry             = d[i] << (32 - bits);
        r[i]              = tmp;
    }
    // rsize
    while (*rLen > 0 && r[*rLen - 1] == 0)
    {
        (*rLen)--;
    }
}

static int msb32(std::uint32_t n) noexcept
{
    int bits = 0;
    while (n != 0)
    {
        n >>= 1;
        bits++;
    }
    return bits;
}

static int bn_div_knuth(BigNum_st       *q,
                        BigNum_st       *r,
                        const BigNum_st *a,
                        const BigNum_st *b,
                        std::uint32_t   *u,
                        std::uint32_t   *v) noexcept
{
    int err_code = 0;
    //
    size_t shiftBits = 32 - msb32(b->data[b->data_len - 1]);
    size_t uLen = 0, vLen = 0;
    mem_sll(u, &uLen, a->data, a->data_len, shiftBits);
    mem_sll(v, &vLen, b->data, b->data_len, shiftBits);
    u[uLen] = 0; //
    // D2
    size_t        divLen  = vLen;
    std::uint32_t divHigh = v[divLen - 1];
    std::uint32_t divLow  = v[divLen - 2];
    std::uint64_t base    = (std::uint64_t)UINT32_MAX + 1; // 2^32

    if (q != NULL && q->MAX_DSIZE < uLen - divLen)
    {
        err_code = -1;

        goto end;
    }

    if (r != NULL && r->MAX_DSIZE < b->data_len)
    {
        err_code = -1;

        goto end;
    }

    for (size_t j = uLen - divLen; u_ge_zero(j); j--)
    {
        // D3 qhat
        std::uint64_t qhat, rhat;
        std::uint64_t uh  = (std::uint64_t)(u[j + divLen]);
        std::uint64_t ul  = (std::uint64_t)(u[j + divLen - 1]);
        std::uint64_t ul2 = (std::uint64_t)(u[j + divLen - 2]);

        qhat = (uh * base + ul) / (std::uint64_t)divHigh;
        if (qhat > UINT32_MAX)
        {
            qhat = UINT32_MAX;
        }
        rhat = (uh * base + ul) - (std::uint64_t)divHigh * qhat;
        if (qhat == 0)
        {
            if (q != NULL)
            {
                q->data[j] = 0;
            }
            continue;
        }
        while (qhat * (std::uint64_t)divLow > base * rhat + ul2)
        {
            // qhat
            rhat += divHigh, qhat -= 1;
            if (rhat >= base)
            {
                break;
            }
        }
        // D4
        int           borrow = 0; // u
        std::uint32_t carry  = 0; // div
        for (size_t iv = 0; iv < divLen; iv++)
        {
            std::uint32_t t;
            // div*qhat
            carry = _mul_carry(&t, (std::uint32_t)qhat, v[iv], carry);
            // u - div*qhat
            borrow = _sub_borrow(&u[j + iv], u[j + iv], t, borrow);
        }
        if (borrow != 0 || carry != 0)
        {
            borrow = _sub_borrow(&u[j + divLen], u[j + divLen], carry, borrow);
        }
        // D5
        if (q != NULL)
        {
            q->data[j] =
                (borrow == 0) ? (std::uint32_t)qhat : (std::uint32_t)qhat - 1;
        }
        // D6
        if (borrow != 0)
        {
            int carry_ = 0; //
            for (size_t iv = 0; iv < divLen; iv++)
            {
                carry_ = _add_carry(&u[j + iv], u[j + iv], v[iv], carry_);
            }
            if (carry_ != 0)
            {
                _add_carry(&u[j + divLen], u[j + divLen], 0, carry_);
                // drop carry
            }
        }
    } // D7
    if (q != NULL)
    {
        q->data_len = uLen - divLen + 1;
        while (q->data_len > 0 && q->data[q->data_len - 1] == 0)
        {
            (q->data_len)--;
        }
    }
    if (r != NULL)
    {
        mem_srl(r->data, &(r->data_len), u, vLen, shiftBits);
        while (r->data_len > 0 && r->data[r->data_len - 1] == 0)
        {
            (r->data_len)--;
        }
    }

end:
    return err_code;
}

int bn_divmod(BigNum_st                 *q,
              BigNum_st                 *r,
              const BigNum_st           *a,
              const BigNum_st           *b,
              std::pmr::memory_resource *mp) noexcept
{
    if (bn_cmp_zero(b) == 0)
    {
        return -1;
    }
    if (q == NULL && r == NULL)
    {
        return 0;
    }
    if (bn_cmp_zero(a) == 0)
    {
        if (q != NULL) bn_set_zero(q);
        if (r != NULL) bn_set_zero(r);
        return 0;
    }

    int err_code = 0;

    std::uint32_t *u = NULL, *v = NULL;
    // a = q*b+r
    // a  (+) (-) (+) (-)
    // b  (+) (+) (-) (-)
    // q  (+) (-) (-) (+)
    // r  (+) (-) (+) (-)
    int q_sign = a->sign * b->sign, r_sign = a->sign;
    int cmp = bn_ucmp(a, b);
    if (cmp == 0)
    { // |a|=|b|, a/b = 1...0
        if (q != NULL)
        {
            GMLIB_CATCH_ERROR(bn_from_u32(q, 1));
            q->sign = q_sign;
        }
        if (r != NULL) bn_set_zero(r);

        goto end;
    }
    if (cmp < 0)
    { // |a|<|b|, a/b = 0...a
        if (r != NULL) GMLIB_CATCH_ERROR(bn_cpy(r, a));
        if (q != NULL) bn_set_zero(q);
        goto end;
    }

    // |a|>|b|
    if (b->data_len == 1)
    {
        std::uint32_t rem;
        if (q != NULL)
        {
            GMLIB_CATCH_ERROR(bn_udivmod32(q, &rem, a, b->data[0]));
            q->sign = q_sign;
        }
        else
        {
            GMLIB_CATCH_ERROR(bn_umod32(&rem, a, b->data[0]));
        }

        if (r != NULL)
        {
            GMLIB_CATCH_ERROR(bn_from_u32(r, rem));
            r->sign = rem ? r_sign : 0;
        }
        goto end;
    }

    try
    {
        u = (std::uint32_t *)mp->allocate(4 * (a->data_len + 2));
        v = (std::uint32_t *)mp->allocate(4 * (a->data_len + 1));
    }
    catch (std::exception &)
    {
        err_code = -1;
        goto end;
    }

    GMLIB_CATCH_ERROR(bn_div_knuth(q, r, a, b, u, v));
    if (q != NULL) q->sign = q_sign;
    if (r != NULL) r->sign = r->data_len ? r_sign : 0;
end:
    if (v != NULL)
    {
        mp->deallocate(v, 4 * (a->data_len + 1));
    }
    if (u != NULL)
    {
        mp->deallocate(u, 4 * (a->data_len + 2));
    }

    return err_code;
}

int bn_div(BigNum_st                 *r,
           const BigNum_st           *a,
           const BigNum_st           *b,
           std::pmr::memory_resource *mp) noexcept
{
    int err_code = 0;
    GMLIB_CATCH_ERROR(bn_divmod(r, NULL, a, b, mp));
end:
    return err_code;
}

int bn_mod(BigNum_st                 *r,
           const BigNum_st           *a,
           const BigNum_st           *b,
           std::pmr::memory_resource *mp) noexcept
{
    int err_code = 0;
    GMLIB_CATCH_ERROR(bn_divmod(NULL, r, a, b, mp));
end:
    return err_code;
}

} // namespace number::internal::common
