#ifndef BLOCK_CIPHER_MODE_IMPL_ECB_MODE_IMPL_H
#define BLOCK_CIPHER_MODE_IMPL_ECB_MODE_IMPL_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/memory_utils/memxor.h>

#include <cstring>

namespace block_cipher_mode::impl {

template <class Cipher>
class EcbEncryptorImpl
    : public BlockCipherModeEncryptor<Cipher::BLOCK_SIZE, Cipher::PARALLEL_NUM>
{
    using Base = BlockCipherModeEncryptor< //
        Cipher::BLOCK_SIZE,                //
        Cipher::PARALLEL_NUM               //
        >;                                 //

private:
    static constexpr std::size_t BLOCK_SIZE   = Cipher::BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = Cipher::PARALLEL_NUM;

private:
    Cipher cipher_;

public:
    EcbEncryptorImpl() = default;

    ~EcbEncryptorImpl() override = default;

public:
    const BlockCipher& get_cipher_ctx() const noexcept override
    {
        return cipher_;
    }

    const char* get_name() const noexcept override
    {
        return "ECB-ENC";
    }

public:
    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::make_unique<EcbEncryptorImpl>(*this);
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
        (void)iv;
        (void)iv_len;
        (void)aad;
        (void)aad_len;
        this->Base::init_();
    }

private:
    void update_blocks_(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) override final
    {
        cipher_.encrypt_blocks(out, in, block_num);
    }

public:
    std::size_t get_block_size() const noexcept override
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
class EcbDecryptorImpl
    : public BlockCipherModeDecryptor<Cipher::BLOCK_SIZE, Cipher::PARALLEL_NUM>
{
    using Base = BlockCipherModeDecryptor< //
        Cipher::BLOCK_SIZE,                //
        Cipher::PARALLEL_NUM               //
        >;                                 //

private:
    static constexpr std::size_t BLOCK_SIZE   = Cipher::BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = Cipher::PARALLEL_NUM;

private:
    Cipher cipher_;

public:
    EcbDecryptorImpl() = default;

    ~EcbDecryptorImpl() override = default;

public:
    const BlockCipher& get_cipher_ctx() const noexcept override
    {
        return cipher_;
    }

    const char* get_name() const noexcept override
    {
        return "ECB-DEC";
    }

public:
    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::make_unique<EcbDecryptorImpl>(*this);
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
            cipher_.set_key(user_key, Cipher::DECRYPTION);
        }
        (void)iv;
        (void)iv_len;
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
    }

public:
    std::size_t get_block_size() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t get_iv_len() const noexcept override
    {
        return 0;
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
