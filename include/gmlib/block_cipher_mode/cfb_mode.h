#ifndef BLOCK_CIPHER_MODE_CFB_MODE_H
#define BLOCK_CIPHER_MODE_CFB_MODE_H

#include <gmlib/block_cipher_mode/block_cipher_mode.h>
#include <gmlib/memory_utils/memxor.h>

#include <stdexcept>

namespace block_cipher_mode {

template <class Cipher>
class CfbEncryptor : public BlockCipherMode<Cipher::BLOCK_SIZE>
{
public:
    static constexpr std::size_t BLOCK_SIZE   = Cipher::BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

private:
    Cipher       cipher_;
    std::uint8_t iv_[Cipher::BLOCK_SIZE];

public:
    CfbEncryptor() = default;

    CfbEncryptor(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        this->init(user_key, iv);
    }

public:
    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        cipher_.set_key(user_key, Cipher::ENCRYPTION);
        std::memcpy(iv_, iv, Cipher::BLOCK_SIZE);
    }

    void reset(const std::uint8_t* iv) noexcept
    {
        this->BlockCipherMode<Cipher::BLOCK_SIZE>::reset();
        std::memcpy(iv_, iv, Cipher::BLOCK_SIZE);
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

        std::uint8_t* pre_ct = iv_;
        while (block_num)
        {
            cipher_.encrypt_block(iv_, pre_ct);
            memory_utils::memxor<BLOCK_SIZE>(out, in, iv_);
            pre_ct = out;
            in += BLOCK_SIZE, out += BLOCK_SIZE, block_num--;
        }
        std::memcpy(iv_, pre_ct, BLOCK_SIZE);
    }

    void final_block(std::uint8_t*       out,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        if (inl == 0)
        {
            return;
        }
        cipher_.encrypt_block(iv_, iv_);
        memory_utils::memxor_n(out, iv_, in, inl);
    }
};

template <class Cipher>
class CfbDecryptor : public BlockCipherMode<Cipher::BLOCK_SIZE>
{
public:
    static constexpr std::size_t BLOCK_SIZE   = Cipher::BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

private:
    Cipher       cipher_;
    std::uint8_t iv_[Cipher::BLOCK_SIZE];

public:
    CfbDecryptor() = default;

    CfbDecryptor(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        this->init(user_key, iv);
    }

public:
    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        cipher_.set_key(user_key, Cipher::ENCRYPTION);
        std::memcpy(iv_, iv, Cipher::BLOCK_SIZE);
    }

    void reset(const std::uint8_t* iv) noexcept
    {
        this->BlockCipherMode<Cipher::BLOCK_SIZE>::reset();
        std::memcpy(iv_, iv, Cipher::BLOCK_SIZE);
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        constexpr std::size_t BLOCK_SIZE     = Cipher::BLOCK_SIZE;
        constexpr std::size_t PARALLEL_NUM   = Cipher::PARALLEL_NUM;
        constexpr std::size_t PARALLEL_BYTES = BLOCK_SIZE * PARALLEL_NUM;
        constexpr std::size_t REMAIN         = PARALLEL_BYTES - BLOCK_SIZE;

        std::uint8_t buffer[PARALLEL_BYTES];
        while (block_num >= PARALLEL_NUM)
        {
            std::memcpy(buffer, iv_, BLOCK_SIZE);
            std::memcpy(buffer + BLOCK_SIZE, in, REMAIN);
            std::memcpy(iv_, in + REMAIN, BLOCK_SIZE);
            cipher_.encrypt_blocks(buffer, buffer, PARALLEL_NUM);
            memory_utils::memxor<PARALLEL_BYTES>(out, in, buffer);
            out += PARALLEL_BYTES;
            in += PARALLEL_BYTES, block_num -= PARALLEL_NUM;
        }
        if (block_num)
        {
            std::size_t         remain_bytes = block_num * BLOCK_SIZE;
            const std::uint8_t* nxt_iv       = in + remain_bytes - BLOCK_SIZE;
            std::memcpy(buffer, iv_, BLOCK_SIZE);
            std::memcpy(buffer + BLOCK_SIZE, in, remain_bytes - BLOCK_SIZE);
            std::memcpy(iv_, nxt_iv, BLOCK_SIZE);
            cipher_.encrypt_blocks(buffer, buffer, block_num);
            memory_utils::memxor_n(out, in, buffer, remain_bytes);
        }
    }

    void final_block(std::uint8_t*       out,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        if (inl == 0)
        {
            return;
        }
        cipher_.encrypt_block(iv_, iv_);
        memory_utils::memxor_n(out, in, iv_, inl);
    }
};

} // namespace block_cipher_mode

#endif