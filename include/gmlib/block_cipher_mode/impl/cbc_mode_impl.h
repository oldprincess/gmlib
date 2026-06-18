#ifndef BLOCK_CIPHER_MODE_IMPL_CBC_MODE_IMPL_H
#define BLOCK_CIPHER_MODE_IMPL_CBC_MODE_IMPL_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/type_traits.h>
#include <gmlib/memory_utils/memxor.h>

#include <stdexcept>

namespace block_cipher_mode::impl {

template <class Cipher>
class CbcEncryptorImpl : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
    static_assert(is_valid_block_cipher_v<Cipher>, "invalid block cipher");

public:
    static constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

public:
    const char* fetch_name() const noexcept override
    {
        return "CBC-ENC";
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
    std::uint8_t iv_[BLOCK_SIZE];

public:
    CbcEncryptorImpl() = default;

    CbcEncryptorImpl(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        this->init(user_key, iv);
    }

    ~CbcEncryptorImpl()
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
                    "invalid number of arguments in CbcEncryptorImpl");
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
                    "invalid number of arguments in CbcEncryptorImpl");
            }
            this->reset(*(const std::uint8_t**)argv[0]);
            return;
        }
        throw std::runtime_error("CbcEncryptorImpl does not support ctrl");
    }

    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::unique_ptr<BlockCipherMode>(new CbcEncryptorImpl(*this));
    }

    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        cipher_.set_key(user_key, Cipher::ENCRYPTION);
        std::memcpy(iv_, iv, BLOCK_SIZE);
    }

    void reset(const std::uint8_t* iv) noexcept
    {
        this->BlockCipherModeImpl<BLOCK_SIZE>::reset();
        std::memcpy(iv_, iv, BLOCK_SIZE);
    }

protected:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        std::uint8_t* cur_iv = iv_;
        while (block_num)
        {
            memory_utils::memxor<BLOCK_SIZE>(iv_, in, cur_iv);
            cipher_.encrypt_block(out, iv_);
            cur_iv = out;
            in += BLOCK_SIZE, out += BLOCK_SIZE, block_num--;
        }
        std::memcpy(iv_, cur_iv, BLOCK_SIZE);
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
        if (inl != BLOCK_SIZE)
        {
            throw std::runtime_error("input data length in CBC mode needs to "
                                     "be an integer multiple of BLOCK_SIZE");
        }
        this->update_blocks(out, in, 1);
    }
};

template <class Cipher>
class CbcDecryptorImpl : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
    static_assert(is_valid_block_cipher_v<Cipher>, "invalid block cipher");

public:
    static constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

public:
    const char* fetch_name() const noexcept override
    {
        return "CBC-DEC";
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
    Cipher  cipher_;
    uint8_t iv_[Cipher::BLOCK_SIZE];

public:
    CbcDecryptorImpl() = default;

    CbcDecryptorImpl(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        this->init(user_key, iv);
    }
    ~CbcDecryptorImpl()
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
                    "invalid number of arguments in CbcDecryptorImpl");
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
                    "invalid number of arguments in CbcDecryptorImpl");
            }
            this->reset(*(const std::uint8_t**)argv[0]);
            return;
        }
        throw std::runtime_error("CbcDecryptorImpl does not support ctrl");
    }

    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::unique_ptr<BlockCipherMode>(new CbcDecryptorImpl(*this));
    }

public:
    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        cipher_.set_key(user_key, Cipher::DECRYPTION);
        std::memcpy(iv_, iv, BLOCK_SIZE);
    }

    void reset(const std::uint8_t* iv) noexcept
    {
        this->BlockCipherModeImpl<BLOCK_SIZE>::reset();
        std::memcpy(iv_, iv, BLOCK_SIZE);
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        constexpr std::size_t PARALLEL_NUM   = Cipher::PARALLEL_NUM;
        constexpr std::size_t PARALLEL_BYTES = BLOCK_SIZE * PARALLEL_NUM;
        constexpr std::size_t REMAIN         = PARALLEL_BYTES - BLOCK_SIZE;

        std::uint8_t buffer[PARALLEL_BYTES], next_iv[BLOCK_SIZE];
        while (block_num >= PARALLEL_NUM)
        {
            std::memcpy(next_iv, in + REMAIN, BLOCK_SIZE);

            cipher_.decrypt_blocks(buffer, in, PARALLEL_NUM);
            memory_utils::memxor<BLOCK_SIZE>(out, buffer, iv_);
            std::uint8_t *ptr1 = out + BLOCK_SIZE, *ptr2 = buffer + BLOCK_SIZE;
            memory_utils::memxor<REMAIN>(ptr1, ptr2, in);
            in += PARALLEL_BYTES, out += PARALLEL_BYTES;
            block_num -= PARALLEL_NUM;

            std::memcpy(iv_, next_iv, BLOCK_SIZE);
        }
        if (block_num)
        {
            std::size_t remain = (block_num - 1) * BLOCK_SIZE;
            std::memcpy(next_iv, in + remain, BLOCK_SIZE);

            cipher_.decrypt_blocks(buffer, in, block_num);
            memory_utils::memxor<BLOCK_SIZE>(out, buffer, iv_);
            std::uint8_t* ptr1 = out + BLOCK_SIZE;
            std::uint8_t* ptr2 = buffer + BLOCK_SIZE;
            memory_utils::memxor_n(ptr1, ptr2, in, remain);

            std::memcpy(iv_, next_iv, BLOCK_SIZE);
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
        // input len != 0
        if (inl != BLOCK_SIZE)
        {
            throw std::runtime_error("input data length in CBC mode needs to "
                                     "be an integer multiple of BLOCK_SIZE");
        }
        this->update_blocks(out, in, 1);
    }
};

} // namespace block_cipher_mode::impl

#endif
