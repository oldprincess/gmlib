#ifndef SM9_INTERNAL_SM9_ALG_H
#define SM9_INTERNAL_SM9_ALG_H

#include <gmlib/memory_utils/endian.h>
#include <gmlib/sm9/internal/sm9_field.h>

namespace sm9::internal {

template <class Hash>
void sm9_Hn(std::uint8_t        h[32],
            const std::uint8_t* Z1,
            std::size_t         z1_len,
            const std::uint8_t* Z2,
            std::size_t         z2_len,
            std::uint8_t        tag01)
{
    constexpr std::size_t DIGEST_SIZE = Hash::DIGEST_SIZE;
    constexpr std::size_t h_len       = 40; // [(5xlog2(n)) / 32]
    constexpr std::size_t v           = Hash::DIGEST_SIZE;

    constexpr std::size_t Ha_size = h_len + (v - h_len % v) % v;

    Hash          hash;
    std::uint32_t cnt = 1;
    std::uint8_t  Ha[Ha_size], cnt_buf[4];
    sm9_bn_t      h1;

    // Hai = H(tag || Z || ct)
    hash.update(&tag01, 1);
    hash.update(Z1, z1_len);
    hash.update(Z2, z2_len);
    for (std::size_t i = 0; i < (h_len + v - 1) / v; i++)
    {
        Hash hash_tmp = hash;
        memory_utils::store32_be(cnt_buf, cnt);
        hash_tmp.do_final(Ha + i * DIGEST_SIZE, cnt_buf, 4);
        cnt++;
    }
    // h1 = Ha mod (n-1) + 1
    sm9_bn_mod_n_sub1_ex(h1, Ha, h_len);
    sm9_bn_add_uint32(h1, h1, 1);
    sm9_bn_to_bytes(h, h1);
}

} // namespace sm9::internal

#endif