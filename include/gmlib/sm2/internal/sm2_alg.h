#ifndef SM2_INTERNAL_SM2_ALG_H
#define SM2_INTERNAL_SM2_ALG_H

#include <gmlib/memory_utils/endian.h>
#include <gmlib/memory_utils/memxor.h>
#include <gmlib/sm2/internal/sm2p256v1.h>

#include <cstring>
#include <stdexcept>

namespace sm2::internal {

template <class Hash>
void sm2_compute_z(std::uint8_t*       z,
                   const std::uint8_t* id,
                   std::size_t         id_len,
                   const std::uint8_t  x[32],
                   const std::uint8_t  y[32])
{
    if (id_len * 8 > UINT16_MAX)
    {
        throw std::runtime_error("SM2 ID length too long");
    }
    std::uint8_t  ENTL[2];
    std::uint16_t entl_len = (std::uint16_t)(id_len * 8);
    ENTL[0]                = entl_len >> 8;
    ENTL[1]                = entl_len & 0xFF;
    Hash hash;
    hash.update(ENTL, 2);
    hash.update(id, id_len);
    hash.update(SM2_CURVE_A, 32);
    hash.update(SM2_CURVE_B, 32);
    hash.update(SM2_CURVE_GX, 32);
    hash.update(SM2_CURVE_GY, 32);
    hash.update(x, 32);
    hash.update(y, 32);
    hash.do_final(z);
}

template <class Hash>
int sm2_kdf_xor(std::uint8_t*       out,
                const std::uint8_t* in,
                std::size_t         inl,
                const std::uint8_t* Z,
                std::size_t         z_len)
{
    constexpr std::size_t     DIGEST_SIZE       = Hash::DIGEST_SIZE;
    static const std::uint8_t ZERO[DIGEST_SIZE] = {0};
    if (inl >= DIGEST_SIZE * UINT32_MAX)
    {
        throw std::runtime_error("SM2 KDF derived key too long");
    }
    if (inl == 0)
    {
        return 0;
    }
    bool          all_zero = true;
    std::uint32_t ct       = 1;
    std::uint8_t  ct_buf[4], dk[DIGEST_SIZE];
    Hash          hash_save;
    hash_save.update(Z, z_len);
    while (inl >= DIGEST_SIZE)
    {
        memory_utils::store32_be(ct_buf, ct);
        auto hash = hash_save;
        hash.do_final(dk, ct_buf, 4);
        all_zero = all_zero && (std::memcmp(ZERO, dk, DIGEST_SIZE) == 0);
        memory_utils::memxor<DIGEST_SIZE>(out, in, dk);
        out += DIGEST_SIZE, in += DIGEST_SIZE, inl -= DIGEST_SIZE;
        ct++;
    }
    if (inl)
    {
        memory_utils::store32_be(ct_buf, ct);
        auto hash = hash_save;
        hash.do_final(dk, ct_buf, 4);
        all_zero = all_zero && (std::memcmp(ZERO, dk, inl) == 0);
        memory_utils::memxor_n(out, dk, in, inl);
    }
    if (all_zero)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

} // namespace sm2::internal

#endif