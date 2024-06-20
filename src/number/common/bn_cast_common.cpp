#include <gmlib/number/internal/bn_common.h>

#include <cstring>

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

#define _bn_alloc(n, bits, mp)    GMLIB_CATCH_ERROR(bn_alloc(n, bits, mp))
#define _bn_cpy(r, a)             GMLIB_CATCH_ERROR(bn_cpy(r, a))
#define _bn_udivmod32(q, r, a, b) GMLIB_CATCH_ERROR(bn_udivmod32(q, r, a, b))
#define _bn_umul32_uadd32(r, a, mul_val, add_val) \
    GMLIB_CATCH_ERROR(bn_umul32_uadd32(r, a, mul_val, add_val))

int bn_from_u32(BigNum_st *r, std::uint32_t a) noexcept
{
    int err_code = 0;
    if (a == 0)
    {
        r->data_len = 0, r->sign = 0;
    }
    else
    {
        if (r->data_len >= 1)
        {
            r->data_len = 1, r->sign = 1;
            r->data[0] = a;
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

int bn_to_str(char                      *s,
              const BigNum_st           *a,
              int                        radix,
              std::pmr::memory_resource *mp) noexcept
{
    // GMLIB_ASSERT(2 <= radix && radix <= 36);
    if (!(2 <= radix && radix <= 36))
    {
        return -1;
    }
    if (bn_cmp_zero(a) == 0)
    {
        s[0] = '0', s[1] = '\0';
        return 0;
    }

    int         err_code = 0;
    BigNum_st  *t        = NULL;
    char       *cur_str  = NULL;
    std::size_t s_len    = 0;
    _bn_alloc(&t, 32 * a->data_len, mp);
    _bn_cpy(t, a);

    if (bn_cmp_zero(t) < 0)
    {
        *s = '-', s += 1;
    }

    cur_str = s;
    while (bn_ucmp_zero(t) != 0)
    {
        std::uint32_t r = 0;
        _bn_udivmod32(t, &r, t, radix);
        *cur_str = (0 <= r && r <= 9) ? ('0' + r) : ('A' + r - 10);
        cur_str += 1;
    }
    *cur_str = '\0';
    //
    s_len = (std::size_t)cur_str - (std::size_t)s;
    for (std::size_t i = 0; i < s_len / 2; i++)
    {
        char c           = s[i];
        s[i]             = s[s_len - 1 - i];
        s[s_len - 1 - i] = c;
    }

end:
    bn_free(t, mp);
    return err_code;
}

int bn_from_str(BigNum_st *r, const char *s, int radix) noexcept
{
    // GMLIB_ASSERT(2 <= radix && radix <= 36);
    if (!(2 <= radix && radix <= 36))
    {
        return -1;
    }
    static int PARSE_SPAN[] = {0, 0, 30, 19, 15, 13, 11, 11, 10, 9, 9, 8, 8,
                               8, 8, 7,  7,  7,  7,  7,  7,  7,  6, 6, 6, 6,
                               6, 6, 6,  6,  6,  6,  6,  6,  6,  6, 5};

    int err_code = 0;
    int is_neg   = 0;
    if (*s == '-')
    {
        is_neg = 1;
        s += 1;
    }
    else if (*s == '+')
    {
        s += 1;
    }
    bn_set_zero(r);
    while (*s != '\0')
    {
        std::uint32_t add_val = 0, mul_val = 1;
        int           i = 0;
        while (i < PARSE_SPAN[radix])
        {
            std::uint32_t tmp = 0;
            if (*s == '\0')
            {
                break;
            }
            if ('0' <= *s && *s <= '9')
            {
                tmp = *s - '0';
            }
            else if ('A' <= *s && *s <= 'A' + radix - 10 - 1)
            {
                tmp = *s - 'A' + 10;
            }
            else if ('a' <= *s && *s <= 'a' + radix - 10 - 1)
            {
                tmp = *s - 'a' + 10;
            }
            else
            {
                err_code = -1;
                goto end;
            }
            mul_val = mul_val * radix;
            add_val = add_val * radix + tmp;
            s += 1, i += 1;
        }
        _bn_umul32_uadd32(r, r, mul_val, add_val);
    }
    if (is_neg)
    {
        r->sign = -1;
    }
    else if (bn_ucmp_zero(r))
    {
        r->sign = 1;
    }
    else
    {
        r->sign = 0;
    }

end:
    return err_code;
}

int bn_from_bytes(BigNum_st          *r,
                  const std::uint8_t *bytes,
                  std::size_t         bytes_len,
                  int                 is_big_endian) noexcept
{
    int         err_code = 0;
    std::size_t data_len = 0;
    if (bytes_len == 0)
    {
        bn_set_zero(r);
        goto end;
    }
    data_len = (bytes_len + 3) / 4;
    if (r->MAX_DSIZE < data_len)
    {
        err_code = -1;
        goto end;
    }
    if (is_big_endian == 1)
    {
        r->data[data_len - 1] = 0;
        std::uint8_t *nptr    = (std::uint8_t *)(r->data);
        for (int i = 0; i < bytes_len; i++)
        {
            nptr[bytes_len - i - 1] = bytes[i];
        }
    }
    else
    {
        r->data[data_len - 1] = 0;
        std::memcpy(r->data, bytes, bytes_len);
    }

    while (data_len > 0 && r->data[data_len - 1] == 0)
    {
        data_len--;
    }
    if (data_len == 0)
    {
        bn_set_zero(r);
    }
    else
    {
        r->data_len = data_len, r->sign = 1;
    }
end:
    return err_code;
}

int bn_to_bytes(std::uint8_t    *bytes,
                std::size_t      bytes_len,
                const BigNum_st *a,
                int              is_big_endian) noexcept
{
    std::size_t nbsize = (bn_bits_length(a) + 7) / 8;
    if (nbsize > bytes_len)
    {
        return -1;
    }
    if (is_big_endian == 1)
    {
        std::uint8_t *nptr = (std::uint8_t *)(a->data);
        for (int i = 0; i < bytes_len; i++)
        {
            bytes[bytes_len - i - 1] = nptr[i];
        }
        std::memset(bytes, 0, bytes_len - nbsize);
    }
    else
    {
        std::memcpy(bytes, a->data, nbsize);
        std::memset(bytes + nbsize, 0, bytes_len - nbsize);
    }
    return 0;
}

} // namespace number::internal::common
