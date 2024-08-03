#ifndef SM9_INTERNAL_SM9_ALG_H
#define SM9_INTERNAL_SM9_ALG_H

#include <gmlib/memory_utils/endian.h>
#include <gmlib/memory_utils/memxor.h>
#include <gmlib/sm9/internal/sm9_field.h>

#include <cstring>

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

template <class Hash>
class SM9Kdf
{
private:
    Hash          hash_;
    std::uint32_t ct_;
    std::uint8_t  buf_[Hash::DIGEST_SIZE];
    std::size_t   buf_pos_;
    bool          all_zero_;

public:
    SM9Kdf() noexcept
    {
        ct_       = 0x00000001;
        buf_pos_  = sizeof(buf_);
        all_zero_ = true;
    }

public:
    void reset()
    {
        ct_       = 0x00000001;
        buf_pos_  = sizeof(buf_);
        all_zero_ = true;
        hash_.reset();
    }

    void update_z(const std::uint8_t* z, std::size_t z_len)
    {
        hash_.update(z, z_len);
    }

    void gen_keystream(std::uint8_t* out, std::size_t len)
    {
        static const std::uint8_t ZERO[Hash::DIGEST_SIZE] = {0};

        std::size_t  size, buf_size;
        std::uint8_t ct_buf[4];
        while (len)
        {
            if (buf_pos_ == sizeof(buf_))
            {
                memory_utils::store32_be(ct_buf, ct_);
                auto hash = hash_;
                hash.do_final(buf_, ct_buf, 4);
                buf_pos_ = 0;
                ct_++;
            }

            buf_size = sizeof(buf_) - buf_pos_;
            size     = (len > buf_size) ? buf_size : len;
            if (std::memcmp(buf_ + buf_pos_, ZERO, size) != 0)
            {
                all_zero_ = false; // check if all zero
            }
            std::memcpy(out, buf_ + buf_pos_, size);
            out += size, buf_pos_ += size, len -= size;
        }
    }

    void gen_keystream_and_xor(std::uint8_t*       out,
                               const std::uint8_t* in,
                               std::size_t         inl)
    {
        std::uint8_t buf[Hash::DIGEST_SIZE];
        while (inl >= Hash::DIGEST_SIZE)
        {
            this->gen_keystream(buf, Hash::DIGEST_SIZE);
            memory_utils::memxor<Hash::DIGEST_SIZE>(out, in, buf);
            out += Hash::DIGEST_SIZE;
            in += Hash::DIGEST_SIZE;
            inl -= Hash::DIGEST_SIZE;
        }
        if (inl)
        {
            this->gen_keystream(buf, inl);
            memory_utils::memxor_n(out, in, buf, inl);
        }
    }

    bool all_zero_check() const noexcept
    {
        return all_zero_;
    }
};

} // namespace sm9::internal

#endif