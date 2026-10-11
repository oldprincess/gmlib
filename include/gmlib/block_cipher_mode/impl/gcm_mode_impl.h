#ifndef BLOCK_CIPHER_MODE_IMPL_GCM_MODE_IMPL_H
#define BLOCK_CIPHER_MODE_IMPL_GCM_MODE_IMPL_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/ghash/ghash.h>
#include <gmlib/memory_utils/endian.h>

#include <cstring>

namespace block_cipher_mode::impl::internal {

template <std::size_t BATCH_SIZE>
static inline void gctr_generate_fixed_batch(std::uint8_t* out,
                                             std::uint8_t  counter[16]) noexcept
{
    static_assert(BATCH_SIZE > 0, "GCTR batch size must be positive");

    alignas(std::uint32_t) std::uint8_t counter_prefix[12];
    std::memcpy(counter_prefix, counter, sizeof(counter_prefix));
    std::uint32_t low = memory_utils::load32_be_aligned(counter + 12);
    for (std::size_t i = 0; i < BATCH_SIZE; ++i)
    {
        std::uint8_t* dst = out + i * 16;
        std::memcpy(dst, counter_prefix, sizeof(counter_prefix));
        memory_utils::store32_be_aligned(dst + 12, low + (std::uint32_t)(i));
    }
    memory_utils::store32_be_aligned(                 //
        counter + 12, low + (std::uint32_t)BATCH_SIZE //
    );                                                //
}

static inline void gctr_generate_batched(std::uint8_t* out,
                                         std::uint8_t  counter[16],
                                         std::size_t   block_num) noexcept
{
    while (block_num >= 16)
    {
        gctr_generate_fixed_batch<16>(out, counter);
        out += 16 * 16;
        block_num -= 16;
    }
    if (block_num >= 8)
    {
        gctr_generate_fixed_batch<8>(out, counter);
        out += 16 * 8;
        block_num -= 8;
    }
    if (block_num >= 4)
    {
        gctr_generate_fixed_batch<4>(out, counter);
        out += 16 * 4;
        block_num -= 4;
    }
    while (block_num != 0)
    {
        gctr_generate_fixed_batch<1>(out, counter);
        out += 16;
        --block_num;
    }
}

} // namespace block_cipher_mode::impl::internal

namespace block_cipher_mode::impl {

template <class Cipher>
using GcmCryptorBase = BlockCipherModeStreamCryptor<Cipher::BLOCK_SIZE,
                                                    Cipher::PARALLEL_NUM,
                                                    alignof(std::uint64_t)>;

template <class Cipher>
class GcmCryptorImpl : public GcmCryptorBase<Cipher>
{
    static_assert(Cipher::BLOCK_SIZE == 16, "block size must be 16");

    using Base = GcmCryptorBase<Cipher>;

private:
    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

private:
    Cipher cipher_;

    alignas(std::uint64_t) std::uint8_t iv_[16];
    ghash::GHash  hash_;
    std::uint8_t  tag_[16], encrypted_j0_[16];
    std::uint64_t aad_len_ = 0, data_len_ = 0, iv_len_ = 12, tag_len_ = 16;

    bool enc_;

    static constexpr const std::uint8_t ZEROS[16] = {0};

public:
    GcmCryptorImpl(bool enc) noexcept : enc_{enc}
    {
    }

    ~GcmCryptorImpl() override
    {
        std::memset(tag_, 0, sizeof(tag_));
        std::memset(encrypted_j0_, 0, sizeof(encrypted_j0_));
        std::memset(iv_, 0, sizeof(iv_));
    }

public:
    const BlockCipher& get_cipher_ctx() const noexcept override
    {
        return cipher_;
    }

    const char* get_name() const noexcept override
    {
        return enc_ ? "GCM-ENC" : "GCM-DEC";
    }

public:
    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::unique_ptr<BlockCipherMode>(new GcmCryptorImpl(*this));
    }

public:
    void init(const std::uint8_t* user_key,
              std::size_t         user_key_len,
              const std::uint8_t* iv,
              std::size_t         iv_len,
              const std::uint8_t* aad,
              std::size_t         aad_len) override
    {
        if (user_key != nullptr)
        {
            if (user_key_len != USER_KEY_LEN)
            {
                throw std::invalid_argument(Error::INVALID_KEY_LENGTH);
            }
            cipher_.set_key(user_key, Cipher::ENCRYPTION);
            // init ghash
            std::uint8_t h[16];
            cipher_.encrypt_block(h, ZEROS);
            hash_.set_key(h);
        }
        if (iv != nullptr)
        {
            if (iv_len != iv_len_)
            {
                throw std::invalid_argument(Error::INVALID_IV_LENGTH);
            }
            if (iv_len_ == 12)
            {
                std::memcpy(iv_, iv, 12);
                std::memset(iv_ + 12, 0, 4);
                iv_[15] = 1;
            }
            else
            {
                hash_.reset();
                hash_.update(iv, iv_len);
                hash_.update(ZEROS, (16 - iv_len_ % 16) % 16);
                alignas(std::uint64_t) std::uint8_t t[8];
                memory_utils::store64_be_aligned(t, (std::uint64_t)iv_len * 8);
                hash_.update(ZEROS, 8);
                hash_.update(t, 8);
                hash_.do_final(iv_);
            }
            // init encrypt j0
            cipher_.encrypt_block(encrypted_j0_, iv_);
            // init iv = j1
            internal::gctr_generate_batched(iv_, iv_, 1);
        }
        hash_.reset();
        aad_len_ = 0;
        if (aad != nullptr)
        {
            hash_.update(aad, aad_len);
            aad_len_ = aad_len;
            hash_.update(ZEROS, (16 - aad_len_ % 16) % 16);
        }
        data_len_ = 0;
        this->Base::init_();
    }

private:
    void generate_key_stream_blocks_(std::uint8_t* key_stream_blocks,
                                     std::size_t   offset_block_num,
                                     std::size_t   total_block_num) override
    {
        std::uint8_t* out       = key_stream_blocks + offset_block_num * 16;
        std::size_t   block_num = total_block_num - offset_block_num;
        internal::gctr_generate_batched(out, iv_, block_num);
        cipher_.encrypt_blocks(out, out, block_num);
    }

public:
    void update(std::uint8_t*       out,
                std::size_t*        outl,
                std::size_t         outl_max,
                const std::uint8_t* in,
                std::size_t         inl) override
    {
        if (out == nullptr) // aad
        {
            hash_.reset();
            hash_.update(in, inl);
            aad_len_ = inl;
            hash_.update(ZEROS, (16 - inl % 16) % 16);
        }
        else
        {
            if (!enc_)
            {
                hash_.update(in, inl);
            }
            this->Base::update(out, outl, outl_max, in, inl);
            if (enc_)
            {
                hash_.update(out, *outl);
            }
            data_len_ += inl;
        }
    }

    void do_final(std::uint8_t*       out,
                  std::size_t*        outl,
                  std::size_t         outl_max,
                  const std::uint8_t* in  = nullptr,
                  std::size_t         inl = 0) override
    {
        if (!enc_)
        {
            hash_.update(in, inl);
        }
        this->Base::do_final(out, outl, outl_max, in, inl);
        if (enc_)
        {
            hash_.update(out, *outl);
        }
        data_len_ += *outl;
        // final tag
        alignas(8) std::uint8_t tmp[16];
        hash_.update(ZEROS, (16 - data_len_ % 16) % 16);
        memory_utils::store64_be_aligned(tmp, aad_len_ * 8);
        memory_utils::store64_be_aligned(tmp + 8, data_len_ * 8);
        hash_.update(tmp, 16);
        hash_.do_final(tmp);
        memory_utils::memxor_n(tmp, tmp, encrypted_j0_, 16);
        if (enc_)
        {
            std::memcpy(tag_, tmp, 16);
        }
        else
        {
            if (std::memcmp(tag_, tmp, tag_len_) != 0)
            {
                throw std::runtime_error(Error::BAD_DECRYPT);
            }
        }
    }

public:
    std::size_t get_block_size() const noexcept override
    {
        return 1;
    }

    std::size_t get_iv_len() const noexcept override
    {
        return iv_len_;
    }

    void set_iv_len(std::size_t value) noexcept override
    {
        iv_len_ = value;
    }

    std::size_t get_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }

    void get_tag(std::uint8_t* out, std::size_t tag_len) const override
    {
        if (tag_len > tag_len_)
        {
            throw std::invalid_argument("Tag length is too large.");
        }
        std::memcpy(out, tag_, tag_len);
    }

    void set_tag(const std::uint8_t* in, std::size_t inl) override
    {
        if (inl > 16)
        {
            throw std::invalid_argument("Tag length is too large.");
        }
        std::memcpy(tag_, in, inl);
        tag_len_ = inl;
    }
};

template <class Cipher>
class GcmEncryptorImpl : public GcmCryptorImpl<Cipher>
{
public:
    GcmEncryptorImpl() : GcmCryptorImpl<Cipher>(true)
    {
    }
};

template <class Cipher>
class GcmDecryptorImpl : public GcmCryptorImpl<Cipher>
{
public:
    GcmDecryptorImpl() : GcmCryptorImpl<Cipher>(false)
    {
    }
};

} // namespace block_cipher_mode::impl
#endif
