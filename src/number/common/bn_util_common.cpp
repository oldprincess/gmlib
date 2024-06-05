#include <gmlib/number/internal/bn_common.h>

#include <cstring>

namespace number::internal::common {

int bn_alloc(BigNum_st                **n,
             std::size_t                bits,
             std::pmr::memory_resource *mp) noexcept
{
    int         err_code = 0;
    std::size_t data_len = (bits + 31) / 32;
    void       *mem      = NULL;

    try
    {
        mem = mp->allocate(sizeof(BigNum_st) + 4 * data_len);
    }
    catch (std::exception &)
    {
        err_code = -1;
        goto end;
    }
    *n         = (BigNum_st *)mem;
    (*n)->data = (std::uint32_t *)((std::uint8_t *)mem + sizeof(BigNum_st));
    (*n)->MAX_DSIZE = data_len;
    (*n)->sign      = 0;
    (*n)->data_len  = 0;
end:
    return err_code;
}

void bn_free(BigNum_st *n, std::pmr::memory_resource *mp) noexcept
{
    mp->deallocate(n, sizeof(BigNum_st) + 4 * n->MAX_DSIZE);
}

int bn_test(const BigNum_st *a, std::size_t i) noexcept
{
    std::size_t index_u32 = i / 32;
    std::size_t index_bit = i % 32;
    if (index_u32 >= a->data_len)
    {
        return 0;
    }
    return (a->data[index_u32] >> index_bit) & 1;
}

void bn_set_zero(BigNum_st *a) noexcept
{
    a->sign = 0, a->data_len = 0;
}

int bn_cpy(BigNum_st *r, const BigNum_st *a) noexcept
{
    if (r->MAX_DSIZE < a->data_len)
    {
        return -1;
    }
    if (r != a)
    {
        r->sign     = a->sign;
        r->data_len = a->data_len;
        std::memcpy(r->data, a->data, a->data_len * 4);
    }
    return 0;
}

std::size_t bn_bits_length(const BigNum_st *a) noexcept
{
    if (a->data_len == 0)
    {
        return 0;
    }
    std::uint32_t n    = a->data[a->data_len - 1];
    std::size_t   bits = 32 * (a->data_len - 1);
    while (n != 0)
    {
        n >>= 1;
        bits++;
    }
    return bits;
}

} // namespace number::internal::common
