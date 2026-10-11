#ifndef BLOCK_CIPHER_MODE_IMPL_CTR_MODE_IMPL_H
#define BLOCK_CIPHER_MODE_IMPL_CTR_MODE_IMPL_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/memory_utils/endian.h>
#include <gmlib/memory_utils/memxor.h>

#include <cstring>

namespace block_cipher_mode::impl::internal {

struct CtrU64TypeTraits
{
    using T = std::uint64_t;

    static constexpr T MAX = UINT64_MAX;

    static constexpr auto load_be_aligned = memory_utils::load64_be_aligned;

    static constexpr auto store_be_aligned = memory_utils::store64_be_aligned;
};

struct CtrU32TypeTraits
{
    using T = std::uint32_t;

    static constexpr T MAX = UINT32_MAX;

    static constexpr auto load_be_aligned = memory_utils::load32_be_aligned;

    static constexpr auto store_be_aligned = memory_utils::store32_be_aligned;
};

template <class Traits, std::size_t BLOCK_SIZE, std::size_t BATCH_SIZE>
static inline void ctr_generate_fixed_batch(std::uint8_t* out,
                                            std::uint8_t* counter) noexcept

{
    using T = typename Traits::T;

    static_assert(BATCH_SIZE < Traits::MAX, "invalid batch size");
    static_assert((BLOCK_SIZE >= sizeof(T) && BLOCK_SIZE % sizeof(T) == 0),
                  "invalid block size");
    if constexpr (BATCH_SIZE == 0)
    {
        return;
    }

    std::uint8_t* low_ptr = counter + BLOCK_SIZE - sizeof(T);
    T             low     = Traits::load_be_aligned(low_ptr);
    if (BATCH_SIZE <= Traits::MAX - low)
    {
        for (std::size_t i = 0; i < BATCH_SIZE; ++i)
        {
            std::uint8_t* dst = out + i * BLOCK_SIZE;
            if constexpr (BLOCK_SIZE > sizeof(T))
            {
                std::memcpy(dst, counter, BLOCK_SIZE - sizeof(T));
                dst += BLOCK_SIZE - sizeof(T);
            }
            Traits::store_be_aligned(dst, low + static_cast<T>(i));
        }
        low += static_cast<T>(BATCH_SIZE);
        Traits::store_be_aligned(low_ptr, low);
        return;
    }

    constexpr std::size_t LIMB_NUM = BLOCK_SIZE / sizeof(T);
    T                     limbs[LIMB_NUM];
    for (std::size_t i = 0; i < LIMB_NUM; ++i)
    {
        std::uint8_t* src = counter + i * sizeof(T);
        limbs[i]          = Traits::load_be_aligned(src);
    }
    for (std::size_t i = 0; i < BATCH_SIZE; ++i)
    {
        std::uint8_t* dst   = out + i * BLOCK_SIZE;
        T             carry = static_cast<T>(i);
        for (std::size_t j = 0; j < LIMB_NUM; ++j)
        {
            T dst_j = limbs[LIMB_NUM - 1 - j] + carry;
            carry   = dst_j < carry ? 1 : 0;
            Traits::store_be_aligned(                       //
                dst + (LIMB_NUM - 1 - j) * sizeof(T), dst_j //
            );                                              //
        }
    }
    T carry = static_cast<T>(BATCH_SIZE);
    for (std::size_t j = 0; j < LIMB_NUM; ++j)
    {
        T dst_j = limbs[LIMB_NUM - 1 - j] + carry;
        carry   = dst_j < carry ? 1 : 0;
        Traits::store_be_aligned(                           //
            counter + (LIMB_NUM - 1 - j) * sizeof(T), dst_j //
        );                                                  //
    }
}

template <class Traits, std::size_t BLOCK_SIZE>
static inline void ctr_generate_batched(std::uint8_t* out,
                                        std::uint8_t* counter,
                                        std::size_t   block_num) noexcept
{
    while (block_num >= 16)
    {
        ctr_generate_fixed_batch<Traits, BLOCK_SIZE, 16>(out, counter);
        out += BLOCK_SIZE * 16;
        block_num -= 16;
    }
    if (block_num >= 8)
    {
        ctr_generate_fixed_batch<Traits, BLOCK_SIZE, 8>(out, counter);
        out += BLOCK_SIZE * 8;
        block_num -= 8;
    }
    if (block_num >= 4)
    {
        ctr_generate_fixed_batch<Traits, BLOCK_SIZE, 4>(out, counter);
        out += BLOCK_SIZE * 4;
        block_num -= 4;
    }
    while (block_num != 0)
    {
        ctr_generate_fixed_batch<Traits, BLOCK_SIZE, 1>(out, counter);
        out += BLOCK_SIZE;
        --block_num;
    }
}

/**
 * @pre out (block_num * BLOCK_SIZE bytes) and counter (BLOCK_SIZE bytes)
 *      do not overlap.
 * @pre When a limb implementation is selected, `out` and `counter` satisfy
 *      the natural alignment requirement of that limb type.
 */
template <std::size_t BLOCK_SIZE>
static inline void ctr_generate(std::uint8_t* out,
                                std::uint8_t* counter,
                                std::size_t   block_num) noexcept
{
    static_assert(BLOCK_SIZE > 0, "CTR block size must be positive");

    if (block_num == 0)
    {
        return;
    }

    if constexpr (BLOCK_SIZE % sizeof(std::uint64_t) == 0 &&
                  sizeof(std::size_t) == sizeof(std::uint64_t))
    {
        ctr_generate_batched<CtrU64TypeTraits, BLOCK_SIZE>(out, counter,
                                                           block_num);
    }
    else if constexpr (BLOCK_SIZE % sizeof(std::uint32_t) == 0)
    {
        ctr_generate_batched<CtrU32TypeTraits, BLOCK_SIZE>(out, counter,
                                                           block_num);
    }
    else
    {
        auto increment_counter = [](std::uint8_t*       dst,
                                    const std::uint8_t* src) noexcept {
            std::uint16_t carry = 1;
            for (std::size_t i = BLOCK_SIZE; i != 0; --i)
            {
                carry += src[i - 1];
                dst[i - 1] = static_cast<std::uint8_t>(carry);
                carry >>= 8;
            }
        };

        std::uint8_t* current = out;
        std::memcpy(current, counter, BLOCK_SIZE);
        for (std::size_t i = 1; i < block_num; ++i)
        {
            std::uint8_t* next = current + BLOCK_SIZE;
            increment_counter(next, current);
            current = next;
        }
        increment_counter(counter, current);
    }
}

} // namespace block_cipher_mode::impl::internal

namespace block_cipher_mode::impl {

template <class Cipher>
class CtrCryptorImpl
    : public BlockCipherModeStreamCryptor<Cipher::BLOCK_SIZE,
                                          Cipher::PARALLEL_NUM,
                                          alignof(std::uint64_t)>
{
private:
    using Base = BlockCipherModeStreamCryptor< //
        Cipher::BLOCK_SIZE,                    //
        Cipher::PARALLEL_NUM,                  //
        alignof(std::uint64_t)                 //
        >;                                     //

private:
    static constexpr std::size_t BLOCK_SIZE   = Cipher::BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = Cipher::PARALLEL_NUM;

private:
    Cipher cipher_;
    alignas(std::uint64_t) std::uint8_t iv_[BLOCK_SIZE];

public:
    CtrCryptorImpl() = default;

    ~CtrCryptorImpl() override
    {
        std::memset(iv_, 0, sizeof(iv_));
    }

public:
    const BlockCipher& get_cipher_ctx() const noexcept override
    {
        return cipher_;
    }

    const char* get_name() const noexcept override
    {
        return "CTR";
    }

public:
    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::make_unique<CtrCryptorImpl>(*this);
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
        }
        if (iv != nullptr)
        {
            if (iv_len != BLOCK_SIZE)
            {
                throw std::invalid_argument(Error::INVALID_IV_LENGTH);
            }
            std::memcpy(iv_, iv, BLOCK_SIZE);
        }
        (void)aad;
        (void)aad_len;
        this->Base::init_();
    }

private:
    void generate_key_stream_blocks_(std::uint8_t* key_stream_blocks,
                                     std::size_t   offset_block_num,
                                     std::size_t   total_block_num) override
    {
        // offsets preserve the alignment used by the generation helpers.
        std::uint8_t* out = key_stream_blocks + offset_block_num * BLOCK_SIZE;
        std::size_t   block_num = total_block_num - offset_block_num;
        // Generate counter blocks in fixed batches, then encrypt in parallel.
        internal::ctr_generate<BLOCK_SIZE>(out, iv_, block_num);
        cipher_.encrypt_blocks(out, out, block_num);
    }

public:
    std::size_t get_block_size() const noexcept override
    {
        return 1;
    }

    std::size_t get_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }
};

template <class Cipher>
using CtrEncryptorImpl = CtrCryptorImpl<Cipher>;
template <class Cipher>
using CtrDecryptorImpl = CtrCryptorImpl<Cipher>;

} // namespace block_cipher_mode::impl

#endif
