#ifndef BLOCK_CIPHER_MODE_IMPL_CTR_MODE_IMPL_H
#define BLOCK_CIPHER_MODE_IMPL_CTR_MODE_IMPL_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/memory_utils/endian.h>
#include <gmlib/memory_utils/memxor.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace block_cipher_mode::impl::internal {

struct CtrU64TypeTraits
{
    using T = std::uint64_t;

    static constexpr std::size_t MAX = UINT64_MAX;

    static constexpr auto load_be_aligned = memory_utils::load64_be_aligned;

    static constexpr auto store_be_aligned = memory_utils::store64_be_aligned;
};

struct CtrU32TypeTraits
{
    using T = std::uint32_t;

    static constexpr std::size_t MAX = UINT32_MAX;

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
        const auto increment_counter = [](std::uint8_t*       dst,
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
class CtrCryptorImpl : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
public:
    static constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

public:
    const char* fetch_name() const noexcept override
    {
        return "CTR";
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }

private:
    Cipher cipher_;
    alignas(std::uint64_t) std::uint8_t counter_[Cipher::BLOCK_SIZE];

public:
    CtrCryptorImpl() = default;

    CtrCryptorImpl(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        this->init(user_key, iv);
    }

    ~CtrCryptorImpl()
    {
        std::memset(counter_, 0, sizeof(counter_));
    }

public:
    const BlockCipher& fetch_cipher_ctx() const noexcept override
    {
        return cipher_;
    }

public:
    void ctrl(const char* cmd, std::size_t argc, void* argv[]) override
    {
        if (std::strcmp(cmd, "init") == 0)
        {
            if (argc != 2)
            {
                throw std::invalid_argument(
                    "invalid number of arguments in CtrCryptorImpl");
            }
            this->init(*(const std::uint8_t**)argv[0],
                       *(const std::uint8_t**)argv[1]);
            return;
        }
        if (std::strcmp(cmd, "reset") == 0)
        {
            if (argc != 1)
            {
                throw std::invalid_argument(
                    "invalid number of arguments in CtrCryptorImpl");
            }
            this->reset(*(const std::uint8_t**)argv[0]);
            return;
        }
        throw std::runtime_error("CtrCryptorImpl does not support ctrl");
    }

    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::unique_ptr<BlockCipherMode>(new CtrCryptorImpl(*this));
    }

public:
    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        cipher_.set_key(user_key, Cipher::ENCRYPTION);
        std::memcpy(counter_, iv, Cipher::BLOCK_SIZE);
    }

    void reset(const std::uint8_t* iv) noexcept
    {
        this->BlockCipherModeImpl<Cipher::BLOCK_SIZE>::reset();
        std::memcpy(counter_, iv, Cipher::BLOCK_SIZE);
    }

private:
    void gen_block_key_stream(std::uint8_t* out, std::size_t block_num)
    {
        if (block_num == 0)
        {
            return;
        }
        constexpr std::size_t block_size = Cipher::BLOCK_SIZE;
        // generate counter
        internal::ctr_generate<block_size>(out, counter_, block_num);
        // generate key stream
        cipher_.encrypt_blocks(out, out, block_num);
    }

protected:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        constexpr std::size_t block_size     = Cipher::BLOCK_SIZE;
        constexpr std::size_t PARALLEL_NUM   = Cipher::PARALLEL_NUM;
        constexpr std::size_t PARALLEL_BYTES = block_size * PARALLEL_NUM;

        alignas(std::uint64_t) std::uint8_t key_stream[PARALLEL_BYTES];
        while (block_num >= PARALLEL_NUM)
        {
            this->gen_block_key_stream(key_stream, PARALLEL_NUM);
            memory_utils::memxor_n(out, in, key_stream, PARALLEL_BYTES);
            in += PARALLEL_BYTES, out += PARALLEL_BYTES;
            block_num -= PARALLEL_NUM;
        }
        if (block_num)
        {
            std::size_t remain_bytes = block_num * block_size;
            this->gen_block_key_stream(key_stream, block_num);
            memory_utils::memxor_n(out, in, key_stream, remain_bytes);
        }
    }

    void final_block(std::uint8_t*       out,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        constexpr std::size_t block_size = Cipher::BLOCK_SIZE;

        if (inl == 0)
        {
            return;
        }
        alignas(std::uint64_t) std::uint8_t key_stream[block_size];
        this->gen_block_key_stream(key_stream, 1);
        memory_utils::memxor_n(out, key_stream, in, inl);
    }
};

template <class Cipher>
using CtrEncryptorImpl = CtrCryptorImpl<Cipher>;

template <class Cipher>
using CtrDecryptorImpl = CtrCryptorImpl<Cipher>;

} // namespace block_cipher_mode::impl

#endif
