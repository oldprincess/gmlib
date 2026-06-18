#ifndef BLOCK_CIPHER_MODE_IMPL_CTR_MODE_IMPL_H
#define BLOCK_CIPHER_MODE_IMPL_CTR_MODE_IMPL_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/internal/ctr_inc.h>
#include <gmlib/memory_utils/memxor.h>

#include <stdexcept>

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
    Cipher       cipher_;
    std::uint8_t counter_[Cipher::BLOCK_SIZE];

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
        std::uint8_t* cur_counter = out;
        std::memcpy(cur_counter, counter_, block_size);
        for (std::size_t i = 1; i < block_num; i++)
        {
            std::uint8_t* nxt_counter = cur_counter + block_size;
            internal::ctr_inc<block_size>(nxt_counter, cur_counter);
            cur_counter = nxt_counter;
        }
        internal::ctr_inc<block_size>(counter_, cur_counter);
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

        std::uint8_t key_stream[PARALLEL_BYTES];
        while (block_num >= PARALLEL_NUM)
        {
            this->gen_block_key_stream(key_stream, PARALLEL_NUM);
            memory_utils::memxor<PARALLEL_BYTES>(out, in, key_stream);
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
        std::uint8_t key_stream[block_size];
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
