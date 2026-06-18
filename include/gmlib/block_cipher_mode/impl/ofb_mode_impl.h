#ifndef BLOCK_CIPHER_MODE_IMPL_OFB_MODE_IMPL_H
#define BLOCK_CIPHER_MODE_IMPL_OFB_MODE_IMPL_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/memory_utils/memxor.h>

#include <stdexcept>

namespace block_cipher_mode::impl {

template <class Cipher>
class OfbCryptorImpl : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
public:
    static constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

public:
    const char* fetch_name() const noexcept override
    {
        return "OFB";
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
    OfbCryptorImpl() = default;

    OfbCryptorImpl(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        this->init(user_key, iv);
    }

    ~OfbCryptorImpl()
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
                    "invalid number of arguments in OfbCryptorImpl");
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
                    "invalid number of arguments in OfbCryptorImpl");
            }
            this->reset(*(const std::uint8_t**)argv[0]);
            return;
        }
        throw std::runtime_error("OfbCryptorImpl does not support ctrl");
    }

    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::unique_ptr<BlockCipherMode>(new OfbCryptorImpl(*this));
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
    void gen_key_stream(std::uint8_t* out, std::size_t block_num)
    {
        std::uint8_t* pre_ct = iv_;
        do
        {
            cipher_.encrypt_block(out, pre_ct);
            pre_ct = out;
            out += BLOCK_SIZE, block_num--;
        } while (block_num);
        std::memcpy(iv_, pre_ct, BLOCK_SIZE);
    }

protected:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        constexpr std::size_t block_size = Cipher::BLOCK_SIZE;

        std::uint8_t key_stream[block_size];
        while (block_num)
        {
            this->gen_key_stream(key_stream, 1);
            memory_utils::memxor<block_size>(out, in, key_stream);
            in += block_size, out += block_size, block_num--;
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
        this->gen_key_stream(key_stream, 1);
        memory_utils::memxor_n(out, in, key_stream, inl);
    }
};

template <class Cipher>
using OfbEncryptorImpl = OfbCryptorImpl<Cipher>;

template <class Cipher>
using OfbDecryptorImpl = OfbCryptorImpl<Cipher>;

} // namespace block_cipher_mode::impl

#endif
