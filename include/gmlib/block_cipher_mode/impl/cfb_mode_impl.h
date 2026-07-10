#ifndef BLOCK_CIPHER_MODE_IMPL_CFB_MODE_IMPL_H
#define BLOCK_CIPHER_MODE_IMPL_CFB_MODE_IMPL_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/memory_utils/memxor.h>

#include <stdexcept>

namespace block_cipher_mode::impl {

template <class Cipher>
class CfbEncryptorImpl : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
public:
    static constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

public:
    const char* fetch_name() const noexcept override
    {
        return "CFB-ENC";
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
    std::uint8_t iv_[Cipher::BLOCK_SIZE];

public:
    CfbEncryptorImpl() = default;

    CfbEncryptorImpl(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        this->init(user_key, iv);
    }

    ~CfbEncryptorImpl()
    {
        std::memset(iv_, 0, sizeof(iv_));
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
                    "invalid number of arguments in CfbEncryptorImpl");
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
                    "invalid number of arguments in CfbEncryptorImpl");
            }
            this->reset(*(const std::uint8_t**)argv[0]);
            return;
        }
        throw std::runtime_error("CfbEncryptorImpl does not support ctrl");
    }

    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::unique_ptr<BlockCipherMode>(new CfbEncryptorImpl(*this));
    }

public:
    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        cipher_.set_key(user_key, Cipher::ENCRYPTION);
        std::memcpy(iv_, iv, Cipher::BLOCK_SIZE);
    }

    void reset(const std::uint8_t* iv) noexcept
    {
        this->BlockCipherModeImpl<Cipher::BLOCK_SIZE>::reset();
        std::memcpy(iv_, iv, Cipher::BLOCK_SIZE);
    }

protected:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        constexpr std::size_t block_size = Cipher::BLOCK_SIZE;

        std::uint8_t* pre_ct = iv_;
        while (block_num)
        {
            cipher_.encrypt_block(iv_, pre_ct);
            memory_utils::memxor_n(out, in, iv_, block_size);
            pre_ct = out;
            in += block_size, out += block_size, block_num--;
        }
        std::memcpy(iv_, pre_ct, block_size);
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
class CfbDecryptorImpl : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
public:
    static constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

public:
    const char* fetch_name() const noexcept override
    {
        return "CFB-DEC";
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
    std::uint8_t iv_[Cipher::BLOCK_SIZE];

public:
    CfbDecryptorImpl() = default;

    CfbDecryptorImpl(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        this->init(user_key, iv);
    }

    ~CfbDecryptorImpl()
    {
        std::memset(iv_, 0, sizeof(iv_));
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
                    "invalid number of arguments in CfbDecryptorImpl");
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
                    "invalid number of arguments in CfbDecryptorImpl");
            }
            this->reset(*(const std::uint8_t**)argv[0]);
            return;
        }
        throw std::runtime_error("CfbDecryptorImpl does not support ctrl");
    }

    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::unique_ptr<BlockCipherMode>(new CfbDecryptorImpl(*this));
    }

public:
    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        cipher_.set_key(user_key, Cipher::ENCRYPTION);
        std::memcpy(iv_, iv, Cipher::BLOCK_SIZE);
    }

    void reset(const std::uint8_t* iv) noexcept
    {
        this->BlockCipherModeImpl<Cipher::BLOCK_SIZE>::reset();
        std::memcpy(iv_, iv, Cipher::BLOCK_SIZE);
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        constexpr std::size_t block_size     = Cipher::BLOCK_SIZE;
        constexpr std::size_t PARALLEL_NUM   = Cipher::PARALLEL_NUM;
        constexpr std::size_t PARALLEL_BYTES = block_size * PARALLEL_NUM;
        constexpr std::size_t REMAIN         = PARALLEL_BYTES - block_size;

        std::uint8_t buffer[PARALLEL_BYTES];
        while (block_num >= PARALLEL_NUM)
        {
            std::memcpy(buffer, iv_, BLOCK_SIZE);
            std::memcpy(buffer + BLOCK_SIZE, in, REMAIN);
            std::memcpy(iv_, in + REMAIN, BLOCK_SIZE);
            cipher_.encrypt_blocks(buffer, buffer, PARALLEL_NUM);
            memory_utils::memxor_n(out, in, buffer, PARALLEL_BYTES);
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

} // namespace block_cipher_mode::impl

#endif
