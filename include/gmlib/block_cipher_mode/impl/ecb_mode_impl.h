#ifndef BLOCK_CIPHER_MODE_IMPL_ECB_MODE_IMPL_H
#define BLOCK_CIPHER_MODE_IMPL_ECB_MODE_IMPL_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>

#include <stdexcept>

namespace block_cipher_mode::impl {

template <class Cipher>
class EcbEncryptorImpl : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
public:
    static constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

public:
    const char* fetch_name() const noexcept override
    {
        return "ECB-ENC";
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

public:
    EcbEncryptorImpl() = default;

    EcbEncryptorImpl(const std::uint8_t* user_key)
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
        this->BlockCipherModeImpl<Cipher::BLOCK_SIZE>::reset();
    }

protected:
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
class EcbDecryptorImpl : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
public:
    static constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

public:
    const char* fetch_name() const noexcept override
    {
        return "ECB-DEC";
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
    Cipher cipher_; // Symmetric Cipher Context

public:
    EcbDecryptorImpl() = default;

    EcbDecryptorImpl(const std::uint8_t* user_key)
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
        this->BlockCipherModeImpl<Cipher::BLOCK_SIZE>::reset();
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        cipher_.decrypt_blocks(out, in, block_num);
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
        cipher_.decrypt_block(out, in);
    }
};

} // namespace block_cipher_mode::impl

#endif