#ifndef BLOCK_CIPHER_MODE_IMPL_CBC_MODE_IMPL_H
#define BLOCK_CIPHER_MODE_IMPL_CBC_MODE_IMPL_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/memory_utils/memxor.h>

#include <cstring>

namespace block_cipher_mode::impl {

template <class Cipher>
class CbcEncryptorImpl : public BlockCipherModeEncryptor<Cipher::BLOCK_SIZE, 1>
{
private:
    using Base = BlockCipherModeEncryptor<Cipher::BLOCK_SIZE, 1>;

private:
    static constexpr std::size_t BLOCK_SIZE   = Cipher::BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = 1;

private:
    Cipher       cipher_;
    std::uint8_t iv_[BLOCK_SIZE];

public:
    CbcEncryptorImpl() = default;

    ~CbcEncryptorImpl() override
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
        return "CBC-ENC";
    }

public:
    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::make_unique<CbcEncryptorImpl>(*this);
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
    void update_blocks_(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) override
    {
        std::uint8_t block[BLOCK_SIZE];
        for (std::size_t i = 0; i < block_num; ++i)
        {
            memory_utils::memxor_n(block, in, iv_, BLOCK_SIZE);
            cipher_.encrypt_block(out, block);
            std::memcpy(iv_, out, BLOCK_SIZE);
            in += BLOCK_SIZE;
            out += BLOCK_SIZE;
        }
    }

public:
    std::size_t get_block_size() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t get_iv_len() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t get_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }

public:
    using BlockCipherMode::do_final;
    using BlockCipherMode::init;
    using BlockCipherMode::update;
};

template <class Cipher>
class CbcDecryptorImpl
    : public BlockCipherModeDecryptor<Cipher::BLOCK_SIZE, Cipher::PARALLEL_NUM>
{
private:
    using Base = BlockCipherModeDecryptor< //
        Cipher::BLOCK_SIZE,                //
        Cipher::PARALLEL_NUM               //
        >;                                 //

private:
    static constexpr std::size_t BLOCK_SIZE   = Cipher::BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = Cipher::PARALLEL_NUM;

private:
    Cipher       cipher_;
    std::uint8_t iv_[BLOCK_SIZE];

public:
    CbcDecryptorImpl() = default;

    ~CbcDecryptorImpl() override
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
        return "CBC-DEC";
    }

public:
    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::make_unique<CbcDecryptorImpl>(*this);
    }

public:
    void init(const std::uint8_t* user_key,
              std::size_t         user_key_len,
              const std::uint8_t* iv,
              std::size_t         iv_len,
              const std::uint8_t* aad,
              std::size_t         aad_len) override final
    {
        if (user_key != nullptr)
        {
            if (user_key_len != USER_KEY_LEN)
            {
                throw std::invalid_argument(Error::INVALID_KEY_LENGTH);
            }
            cipher_.set_key(user_key, Cipher::DECRYPTION);
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
    void update_blocks_(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) override final
    {
        cipher_.decrypt_blocks(out, in, block_num);
        memory_utils::memxor_n(out, out, iv_, BLOCK_SIZE);
        if (block_num > 1)
        {
            memory_utils::memxor_n(          //
                out + BLOCK_SIZE,            //
                out + BLOCK_SIZE,            //
                in,                          //
                (block_num - 1) * BLOCK_SIZE //
            );                               //
        }
        std::memcpy(                                           //
            iv_, in + (block_num - 1) * BLOCK_SIZE, BLOCK_SIZE //
        );                                                     //
    }

public:
    std::size_t get_block_size() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t get_iv_len() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t get_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }

public:
    using BlockCipherMode::do_final;
    using BlockCipherMode::init;
    using BlockCipherMode::update;
};

} // namespace block_cipher_mode::impl

#endif
