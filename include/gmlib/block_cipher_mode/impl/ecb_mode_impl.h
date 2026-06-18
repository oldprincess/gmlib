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
    const BlockCipher& fetch_cipher_ctx() const noexcept override
    {
        return cipher_;
    }

public:
    void ctrl(const char* cmd, std::size_t argc, void* argv[]) override
    {
        if (std::strcmp(cmd, "init") == 0)
        {
            if (argc != 1)
            {
                throw std::invalid_argument(
                    "invalid number of arguments in EcbEncryptorImpl");
            }
            this->init(*(const std::uint8_t**)argv[0]);
            return;
        }
        if (std::strcmp(cmd, "reset") == 0)
        {
            if (argc != 0)
            {
                throw std::invalid_argument(
                    "invalid number of arguments in EcbEncryptorImpl");
            }
            this->reset();
            return;
        }
        throw std::runtime_error("EcbEncryptorImpl does not support ctrl");
    }

    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::unique_ptr<BlockCipherMode>(new EcbEncryptorImpl(*this));
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
    const BlockCipher& fetch_cipher_ctx() const noexcept override
    {
        return cipher_;
    }

public:
    void ctrl(const char* cmd, std::size_t argc, void* argv[]) override
    {
        if (std::strcmp(cmd, "init") == 0)
        {
            if (argc != 1)
            {
                throw std::invalid_argument(
                    "invalid number of arguments in EcbDecryptorImpl");
            }
            this->init(*(const std::uint8_t**)argv[0]);
            return;
        }
        if (std::strcmp(cmd, "reset") == 0)
        {
            if (argc != 0)
            {
                throw std::invalid_argument(
                    "invalid number of arguments in EcbDecryptorImpl");
            }
            this->reset();
            return;
        }
        throw std::runtime_error("EcbDecryptorImpl does not support ctrl");
    }

    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::unique_ptr<BlockCipherMode>(new EcbDecryptorImpl(*this));
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
