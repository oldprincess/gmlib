#include <gmlib/number/internal/bn_common.h>

#include "bn.inc.h"

namespace number::internal::common {

#define u_ge_zero(i) ((i) < (std::size_t)(-1))

int bn_cmp(const BigNum_st* a, const BigNum_st* b)
{
    if (a->sign > b->sign)
    {
        return 1; // (+) > (0)/(-), (0) > (-)
    }
    else if (a->sign < b->sign)
    {
        return -1; // (-) < (0)/(+), (0) < (+)
    }
    int cmp = bn_ucmp(a, b);
    if (cmp == 0)
    {
        return 0;
    }
    else if (cmp == 1)
    {
        return a->sign; // |a|>|b|
    }
    else
    {
        return -(a->sign); // |a|<|b|
    }
}

int bn_cmp_zero(const BigNum_st* a)
{
    return a->sign;
}

int bn_cmp_u32(const BigNum_st* a, uint32_t b)
{
    int bSign    = (b == 0) ? 0 : 1;
    int bDataLen = (b == 0) ? 0 : 1;

    if (a->sign > bSign)
    {
        return 1; // (+) > (0)/(-), (0) > (-)
    }
    else if (a->sign < bSign)
    {
        return -1; // (-) < (0)/(+), (0) < (+)
    }

    if (a->data_len > bDataLen)
    {
        return 1;
    }
    else if (a->data_len < bDataLen)
    {
        return -1;
    }

    if (a->data[0] > b)
    {
        return 1;
    }
    else if (a->data[0] < b)
    {
        return -1;
    }
    return 0;
}

int bn_ucmp(const BigNum_st* a, const BigNum_st* b)
{
    if (a->data_len > b->data_len)
    {
        return 1;
    }
    else if (a->data_len < b->data_len)
    {
        return -1;
    }

    for (std::size_t i = a->data_len - 1; u_ge_zero(i); i--)
    {
        if (a->data[i] > b->data[i])
        {
            return 1;
        }
        else if (a->data[i] < b->data[i])
        {
            return -1;
        }
    }
    return 0;
}

int bn_ucmp_zero(const BigNum_st* a)
{
    return a->data_len > 0;
}

} // namespace number::internal::common
