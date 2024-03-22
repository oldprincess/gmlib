#ifndef BLOCK_CIPHER_MODE_OFB_MODE_H
#define BLOCK_CIPHER_MODE_OFB_MODE_H

#include <gmlib/block_cipher_mode/block_cipher_mode.h>
#include <gmlib/memory_utils/memxor.h>

#include <stdexcept>

namespace block_cipher_mode {

template <class Cipher>
class OfbCryptor : public BlockCipherMode<Cipher::BLOCK_SIZE>
{
public:
    static constexpr std::size_t BLOCK_SIZE   = Cipher::BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

private:
    Cipher       cipher_;
    std::uint8_t iv_[Cipher::BLOCK_SIZE];

public:
    OfbCryptor() = default;

    OfbCryptor(const std::uint8_t* user_key, const std::uint8_t* iv)
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
    void gen_key_stream(std::uint8_t* out, std::size_t block_num)
    {
        constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

        std::uint8_t* pre_ct = iv_;
        do
        {
            cipher_.encrypt_block(out, pre_ct);
            pre_ct = out;
            out += BLOCK_SIZE, block_num--;
        } while (block_num);
        std::memcpy(iv_, pre_ct, BLOCK_SIZE);
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

        std::uint8_t key_stream[BLOCK_SIZE];
        while (block_num)
        {
            this->gen_key_stream(key_stream, 1);
            memory_utils::memxor<BLOCK_SIZE>(out, in, key_stream);
            in += BLOCK_SIZE, out += BLOCK_SIZE, block_num--;
        }
    }

    void final_block(std::uint8_t*       out,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

        if (inl == 0)
        {
            return;
        }
        std::uint8_t key_stream[BLOCK_SIZE];
        this->gen_key_stream(key_stream, 1);
        memory_utils::memxor_n(out, in, key_stream, inl);
    }
};

template <class Cipher>
using OfbEncryptor = OfbCryptor<Cipher>;

template <class Cipher>
using OfbDecryptor = OfbCryptor<Cipher>;

} // namespace block_cipher_mode

#endif