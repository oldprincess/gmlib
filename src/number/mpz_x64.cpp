#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/mpz_x64.h>
#include <immintrin.h>

#include <cstring>

#if defined(_MSC_VER)
#include <intrin.h>
#else

#define _mulx_u64(a, b, c) _mulx_u64(a, b, (long long unsigned int*)c)
#define _addcarry_u64(a, b, c, d) \
    _addcarry_u64(a, b, c, (long long unsigned int*)d)
#define _subborrow_u64(a, b, c, d) \
    _subborrow_u64(a, b, c, (long long unsigned int*)d)

#define _loadbe_i64(ptr)     __builtin_bswap64(*(std::uint64_t*)(ptr))
#define _storebe_i64(ptr, a) *(std::uint64_t*)(ptr) = __builtin_bswap64(a)

#endif

namespace number::internal::x64 {

int mpz_add_carry(std::uint64_t*       r,
                  const std::uint64_t* a,
                  const std::uint64_t* b,
                  int                  carry,
                  std::size_t          limb_size) noexcept
{
    if (limb_size == 0) return 0;
    unsigned char CF = (char)carry;
    for (std::size_t i = 0; i < limb_size; i++)
    {
        CF = _addcarry_u64(CF, a[i], b[i], &r[i]);
    }
    return CF;
}

int mpz_sub_borrow(std::uint64_t*       r,
                   const std::uint64_t* a,
                   const std::uint64_t* b,
                   int                  borrow,
                   std::size_t          limb_size) noexcept
{
    if (limb_size == 0) return 0;
    unsigned char CF = -borrow;
    for (std::size_t i = 0; i < limb_size; i++)
    {
        CF = _subborrow_u64(CF, a[i], b[i], &r[i]);
    }
    return -CF;
}

void mpz_mul(std::uint64_t*       product,
             const std::uint64_t* multiplier,
             const std::uint64_t* multiplicand,
             std::size_t          limb_size) noexcept
{
    if (limb_size == 0) return;

    unsigned char CF = 0;
    std::uint64_t hi, lo, pre_hi = 0;
    {
        for (std::size_t i1 = 0; i1 < limb_size; i1++)
        {
            product[i1] = _mulx_u64(multiplier[i1], multiplicand[0], &hi);
            CF          = _addcarry_u64(0, product[i1], pre_hi, &product[i1]);
            _addcarry_u64(CF, hi, 0, &hi); // drop CF
            pre_hi = hi;
        }
        product[limb_size] = pre_hi;
    }
    for (std::size_t i2 = 1; i2 < limb_size; i2++)
    {
        pre_hi = 0;
        for (std::size_t i1 = 0; i1 < limb_size; i1++)
        {
            lo = _mulx_u64(multiplier[i1], multiplicand[i2], &hi);
            CF = _addcarry_u64(0, product[i1 + i2], lo, &product[i1 + i2]);
            _addcarry_u64(CF, hi, 0, &hi); // drop CF
            CF = _addcarry_u64(0, product[i1 + i2], pre_hi, &product[i1 + i2]);
            _addcarry_u64(CF, hi, 0, &hi); // drop CF
            pre_hi = hi;
        }
        product[limb_size + i2] = pre_hi;
    }
}

int mpz_cmp(const std::uint64_t* a,
            const std::uint64_t* b,
            std::size_t          limb_size) noexcept
{
    if (limb_size == 0) return 0;
    for (std::size_t i = 0; i < limb_size; i++)
    {
        std::size_t pos = limb_size - 1 - i;
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;
}

void mpz_cpy(std::uint64_t*       r,
             const std::uint64_t* a,
             std::size_t          limb_size) noexcept
{
    std::memmove(r, a, limb_size * sizeof(std::uint64_t));
}

void mpz_from_bytes(std::uint64_t*      r,
                    const std::uint8_t* src,
                    std::size_t         limb_size) noexcept
{
    if (limb_size == 0) return;
    for (std::size_t i = 0; i < limb_size; i++)
    {
        r[limb_size - 1 - i] = _loadbe_i64(src + 8 * i);
    }
}

void mpz_to_bytes(std::uint8_t*        r,
                  const std::uint64_t* src,
                  std::size_t          limb_size) noexcept
{
    if (limb_size == 0) return;
    for (std::size_t i = 0; i < limb_size; i++)
    {
        _storebe_i64(r + 8 * i, src[limb_size - 1 - i]);
    }
}

} // namespace number::internal::x64

#endif