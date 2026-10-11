#ifndef BLOCK_CIPHER_MODE_IMPL_CFB_MODE_IMPL_H
#define BLOCK_CIPHER_MODE_IMPL_CFB_MODE_IMPL_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/memory_utils/memxor.h>

#include <cstring>

namespace block_cipher_mode::impl {

template <class Cipher>
class CfbEncryptorImpl : public BlockCipherMode
{
private:
    using Base = BlockCipherMode;

private:
    static constexpr std::size_t BLOCK_SIZE   = Cipher::BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = 1;

private:
    Cipher       cipher_;
    std::uint8_t iv_[BLOCK_SIZE];
    std::uint8_t key_stream_buf_[BLOCK_SIZE];
    std::size_t  key_stream_idx_ = sizeof(key_stream_buf_);

public:
    CfbEncryptorImpl() = default;

    ~CfbEncryptorImpl() override
    {
        std::memset(iv_, 0, sizeof(iv_));
        std::memset(key_stream_buf_, 0, sizeof(key_stream_buf_));
    }

public:
    const char* get_name() const noexcept override
    {
        return "CFB-ENC";
    }

    const BlockCipher& get_cipher_ctx() const noexcept override
    {
        return cipher_;
    }

public:
    std::unique_ptr<BlockCipherMode> clone() const override final
    {
        return std::make_unique<CfbEncryptorImpl>(*this);
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
        key_stream_idx_ = sizeof(key_stream_buf_);
    }

public:
    void update(std::uint8_t*       out,
                std::size_t*        outl,
                std::size_t         outl_max,
                const std::uint8_t* in,
                std::size_t         inl) override
    {
        *outl = 0;
        if (outl_max < inl)
        {
            throw std::length_error(Error::BUFFER_TOO_SMALL);
        }
        std::size_t input_len = inl;
        // prologue
        if (inl > 0)
        {
            if (key_stream_idx_ < sizeof(key_stream_buf_))
            {
                std::size_t update_size = inl;
                if (sizeof(key_stream_buf_) - key_stream_idx_ < update_size)
                {
                    update_size = sizeof(key_stream_buf_) - key_stream_idx_;
                }
                memory_utils::memxor_n(                                     //
                    out, key_stream_buf_ + key_stream_idx_, in, update_size //
                );                                                          //
                std::memcpy(                                                //
                    iv_ + key_stream_idx_ % BLOCK_SIZE, out, update_size    //
                );                                                          //
                in += update_size, inl -= update_size;
                out += update_size;
                key_stream_idx_ += update_size;
            }
        }
        // body
        while (inl >= BLOCK_SIZE)
        {
            cipher_.encrypt_block(key_stream_buf_, iv_);
            memory_utils::memxor_n(out, key_stream_buf_, in, BLOCK_SIZE);
            std::memcpy(iv_, out, BLOCK_SIZE);
            out += BLOCK_SIZE;
            in += BLOCK_SIZE, inl -= BLOCK_SIZE;
        }
        // epilogue
        if (inl > 0)
        {
            cipher_.encrypt_block(key_stream_buf_, iv_);
            memory_utils::memxor_n(out, key_stream_buf_, in, inl);
            std::memcpy(iv_, out, inl);
            key_stream_idx_ = inl;
        }
        *outl = input_len;
    }

    void do_final(std::uint8_t*       out,
                  std::size_t*        outl,
                  std::size_t         outl_max,
                  const std::uint8_t* in  = nullptr,
                  std::size_t         inl = 0) override
    {
        this->update(out, outl, outl_max, in, inl);
    }

public:
    std::size_t get_block_size() const noexcept override
    {
        return 1;
    }

    std::size_t get_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }

    std::size_t get_iv_len() const noexcept override
    {
        return BLOCK_SIZE;
    }

    void set_padding(bool value) override
    {
        (void)value;
    }

    bool get_padding() const override
    {
        return false;
    }

public:
    using BlockCipherMode::do_final;
    using BlockCipherMode::init;
    using BlockCipherMode::update;
};

template <class Cipher>
class CfbDecryptorImpl : public BlockCipherMode
{
private:
    using Base = BlockCipherMode;

private:
    static constexpr std::size_t BLOCK_SIZE   = Cipher::BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = Cipher::PARALLEL_NUM;

private:
    Cipher       cipher_;
    std::uint8_t iv_[BLOCK_SIZE];
    std::uint8_t key_stream_buf_[BLOCK_SIZE * PARALLEL_NUM];
    std::size_t  key_stream_idx_ = sizeof(key_stream_buf_);

public:
    CfbDecryptorImpl() = default;

    ~CfbDecryptorImpl()
    {
        std::memset(iv_, 0, sizeof(iv_));
        std::memset(key_stream_buf_, 0, sizeof(key_stream_buf_));
    }

public:
    const char* get_name() const noexcept override
    {
        return "CFB-DEC";
    }

    const BlockCipher& get_cipher_ctx() const noexcept override
    {
        return cipher_;
    }

public:
    std::unique_ptr<BlockCipherMode> clone() const override final
    {
        return std::make_unique<CfbDecryptorImpl>(*this);
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
        key_stream_idx_ = sizeof(key_stream_buf_);
    }

public:
    void update(std::uint8_t*       out,
                std::size_t*        outl,
                std::size_t         outl_max,
                const std::uint8_t* in,
                std::size_t         inl) override final
    {
        *outl = 0;
        if (outl_max < inl)
        {
            throw std::length_error(Error::BUFFER_TOO_SMALL);
        }
        std::size_t input_len = inl;
        // prologue
        if (inl > 0)
        {
            if (key_stream_idx_ < sizeof(key_stream_buf_))
            {
                std::size_t update_size = inl;
                if (sizeof(key_stream_buf_) - key_stream_idx_ < update_size)
                {
                    update_size = sizeof(key_stream_buf_) - key_stream_idx_;
                }
                memory_utils::memxor_n(                                     //
                    out, key_stream_buf_ + key_stream_idx_, in, update_size //
                );                                                          //
                std::memcpy(                                                //
                    iv_ + key_stream_idx_ % BLOCK_SIZE, in, update_size     //
                );                                                          //
                in += update_size, inl -= update_size;
                out += update_size;
                key_stream_idx_ += update_size;
            }
        }
        // body
        while (inl >= sizeof(key_stream_buf_))
        {
            this->generate_key_stream_blocks_(                             //
                key_stream_buf_, in, 0, PARALLEL_NUM                       //
            );                                                             //
            memory_utils::memxor_n(                                        //
                out, key_stream_buf_, in, sizeof(key_stream_buf_)          //
            );                                                             //
            std::memcpy(                                                   //
                iv_, in + sizeof(key_stream_buf_) - BLOCK_SIZE, BLOCK_SIZE //
            );                                                             //
            out += sizeof(key_stream_buf_);
            in += sizeof(key_stream_buf_), inl -= sizeof(key_stream_buf_);
        }
        // epilogue
        if (inl > 0)
        {
            std::size_t block_num = (inl + BLOCK_SIZE - 1) / BLOCK_SIZE;
            std::size_t offset    = (PARALLEL_NUM - block_num) * BLOCK_SIZE;
            this->generate_key_stream_blocks_(                              //
                key_stream_buf_, in, PARALLEL_NUM - block_num, PARALLEL_NUM //
            );                                                              //
            memory_utils::memxor_n(out, key_stream_buf_ + offset, in, inl);
            std::size_t feedback_offset = (block_num - 1) * BLOCK_SIZE;
            std::memcpy(iv_, in + feedback_offset, inl - feedback_offset);
            key_stream_idx_ = offset + inl;
        }
        *outl = input_len;
    }

    void do_final(std::uint8_t*       out,
                  std::size_t*        outl,
                  std::size_t         outl_max,
                  const std::uint8_t* in  = nullptr,
                  std::size_t         inl = 0) override final
    {
        this->update(out, outl, outl_max, in, inl);
    }

private:
    void generate_key_stream_blocks_(std::uint8_t*       key_stream_blocks,
                                     const std::uint8_t* in,
                                     std::size_t         offset_block_num,
                                     std::size_t         total_block_num)
    {
        std::uint8_t* out = key_stream_blocks + offset_block_num * BLOCK_SIZE;
        std::size_t   block_num = total_block_num - offset_block_num;
        std::memcpy(out, iv_, BLOCK_SIZE);
        if (block_num > 1)
        {
            std::memcpy(out + BLOCK_SIZE, in, (block_num - 1) * BLOCK_SIZE);
        }
        cipher_.encrypt_blocks(out, out, block_num);
    }

public:
    std::size_t get_block_size() const noexcept override
    {
        return 1;
    }

    std::size_t get_iv_len() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t get_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }

    void set_padding(bool value) override
    {
        (void)value;
    }

    bool get_padding() const override
    {
        return false;
    }

public:
    using BlockCipherMode::do_final;
    using BlockCipherMode::init;
    using BlockCipherMode::update;
};

} // namespace block_cipher_mode::impl

#endif
