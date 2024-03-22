#ifndef BLOCK_CIPHER_MODE_ECB_MODE_H
#define BLOCK_CIPHER_MODE_ECB_MODE_H

#include <gmlib/block_cipher_mode/block_cipher_mode.h>

#include <stdexcept>

namespace block_cipher_mode {

template <class Cipher>
class EcbEncryptor : public BlockCipherMode<Cipher::BLOCK_SIZE>
{
public:
    static constexpr std::size_t BLOCK_SIZE   = Cipher::BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

private:
    Cipher cipher_;

public:
    EcbEncryptor() = default;

    EcbEncryptor(const std::uint8_t* user_key)
    {
        this->init(user_key);
    }

public:
    void init(const std::uint8_t* user_key)
    {
        cipher_.set_key(user_key, Cipher::ENCRYPTION);
    }

    void reset() noexcept
    {
        this->BlockCipherMode<Cipher::BLOCK_SIZE>::reset();
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        cipher_.encrypt_blocks(out, in, block_num);
    }

    void final_block(std::uint8_t*       out,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        if (inl == 0)
        {
            return;
        }
        // input len != 0
        if (inl != Cipher::BLOCK_SIZE)
        {
            throw std::runtime_error("input data length in ECB mode needs to "
                                     "be an integer multiple of BLOCK_SIZE");
        }
        cipher_.encrypt_block(out, in);
    }
};

template <class Cipher>
class EcbDecryptor : public BlockCipherMode<Cipher::BLOCK_SIZE>
{
public:
    static constexpr size_t BLOCK_SIZE   = Cipher::BLOCK_SIZE;
    static constexpr size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

private:
    Cipher cipher_; // Symmetric Cipher Context

public:
    EcbDecryptor() = default;

    EcbDecryptor(const std::uint8_t* user_key)
    {
        this->init(user_key);
    }

public:
    void init(const std::uint8_t* user_key)
    {
        cipher_.set_key(user_key, Cipher::DECRYPTION);
    }

    void reset() noexcept
    {
        this->BlockCipherMode<Cipher::BLOCK_SIZE>::reset();
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        cipher_.decrypt_blocks(out, in, block_num);
    }

    void final_block(uint8_t*            out,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        if (inl == 0)
        {
            return;
        }
        // input len != 0
        if (inl != Cipher::BLOCK_SIZE)
        {
            throw std::runtime_error("input data length in ECB mode needs to "
                                     "be an integer multiple of BLOCK_SIZE");
        }
        cipher_.decrypt_block(out, in);
    }
};

} // namespace block_cipher_mode

#endif