#ifndef BLOCK_CIPHER_MODE_IMPL_BLOCK_CIPHER_MODE_IMPL_H
#define BLOCK_CIPHER_MODE_IMPL_BLOCK_CIPHER_MODE_IMPL_H

#include <gmlib/block_cipher_mode/block_cipher_mode.h>
#include <gmlib/memory_utils/memxor.h>

#include <cstring>
#include <stdexcept>

namespace block_cipher_mode::impl {

template <std::size_t BLOCK_SIZE, std::size_t PARALLEL_NUM>
class BlockCipherModeEncryptor : public BlockCipherMode
{
private:
    std::uint8_t buf_[BLOCK_SIZE * PARALLEL_NUM];
    std::size_t  pending_len_ = 0;

protected:
    Padding padding_ = Padding::None;

protected:
    virtual void update_blocks_(std::uint8_t*       out,
                                const std::uint8_t* in,
                                std::size_t         block_num) = 0;

    // ==========================================
    // ================ Constructor =============
    // ==========================================
public:
    ~BlockCipherModeEncryptor()
    {
        std::memset(buf_, 0, sizeof(buf_));
        pending_len_ = 0;
    }

    // ==============================================
    // ============ Functionality functions =========
    // ==============================================

protected:
    void init_() noexcept
    {
        pending_len_ = 0;
    }

public:
    void update(std::uint8_t*       out,
                std::size_t*        outl,
                std::size_t         outl_max,
                const std::uint8_t* in,
                std::size_t         inl) override final
    {
        std::size_t total_pending_len  = pending_len_ + inl;
        std::size_t remain_pending_len = total_pending_len % BLOCK_SIZE;
        if (outl_max < total_pending_len - remain_pending_len)
        {
            throw std::length_error(Error::BUFFER_TOO_SMALL);
        }

        *outl = total_pending_len - remain_pending_len;
        // ==============================================
        //  situation1: pending_len_ + inl < BLOCK_SIZE
        // ==============================================
        // |--------- BLOCK_SIZE -----------|
        // |--- pending ---|--- inl ---|
        // |---- remain_pending_len ---|
        // ==============================================
        if (pending_len_ + inl == remain_pending_len)
        {
            if (inl > 0)
            {
                std::memcpy(buf_ + pending_len_, in, inl);
                pending_len_ += inl;
            }
        }
        // ==============================================
        //  situation2: pending_len_ + inl > BLOCK_SIZE
        // ==============================================
        // |--- BLOCK_SIZE ---|--- remain_pending_len ---|
        // |--- pending ---|----------- inl -------------|
        // ==============================================
        else
        {
            // prologue
            if (pending_len_ > 0)
            {
                std::size_t cpy_size = inl - remain_pending_len;
                if (sizeof(buf_) - pending_len_ < cpy_size)
                {
                    cpy_size = sizeof(buf_) - pending_len_;
                }
                std::memcpy(buf_ + pending_len_, in, cpy_size);
                pending_len_ += cpy_size;
                in += cpy_size, inl -= cpy_size;

                std::size_t block_num = pending_len_ / BLOCK_SIZE;
                this->update_blocks_(out, buf_, block_num);
                out += block_num * BLOCK_SIZE;
                pending_len_ = 0;
            }
            // body
            while (inl - remain_pending_len >= sizeof(buf_))
            {
                std::memcpy(buf_, in, sizeof(buf_));
                in += sizeof(buf_), inl -= sizeof(buf_);
                this->update_blocks_(out, buf_, PARALLEL_NUM);
                out += PARALLEL_NUM * BLOCK_SIZE;
            }
            // epilogue
            if (inl - remain_pending_len > 0)
            {
                std::memcpy(buf_, in, inl - remain_pending_len);
                pending_len_ = inl - remain_pending_len;

                std::size_t block_num = pending_len_ / BLOCK_SIZE;
                this->update_blocks_(out, buf_, block_num);
                out += block_num * BLOCK_SIZE;
                pending_len_ = 0;
                in += block_num * BLOCK_SIZE, inl -= block_num * BLOCK_SIZE;
            }

            if (inl > 0)
            {
                std::memcpy(buf_, in, inl);
                pending_len_ = inl;
            }
        }
    }

    void do_final(std::uint8_t*       out,
                  std::size_t*        outl,
                  std::size_t         outl_max,
                  const std::uint8_t* in  = nullptr,
                  std::size_t         inl = 0) override final
    {
        *outl = 0;
        if (inl > 0)
        {
            this->update(out, outl, outl_max, in, inl);
            std::size_t outl_tmp = *outl;
            out += outl_tmp, outl_max -= outl_tmp;
        }

        if (padding_ == Padding::None)
        {
            if (pending_len_ % BLOCK_SIZE != 0)
            {
                throw std::invalid_argument(                 //
                    Error::DATA_NOT_MULTIPLE_OF_BLOCK_LENGTH //
                );                                           //
            }
        }
        else if (padding_ == Padding::PKCS7)
        {
            if (outl_max < BLOCK_SIZE)
            {
                throw std::length_error(Error::BUFFER_TOO_SMALL);
            }
            std::size_t pad_len = BLOCK_SIZE - pending_len_;
            std::memset(buf_ + pending_len_, (int)pad_len, pad_len);
            this->update_blocks_(out, buf_, 1);
            *outl += BLOCK_SIZE;
            pending_len_ = 0;
        }
        else
        {
            throw std::invalid_argument("INVALID_PADDING");
        }
    }

    // ==============================================
    // ============ Getter/Setter functions =========
    // ==============================================

    bool get_padding() const override final
    {
        return padding_ == Padding::PKCS7;
    }

    void set_padding(bool value) override final
    {
        padding_ = value ? Padding::PKCS7 : Padding::None;
    }
};

template <std::size_t BLOCK_SIZE, std::size_t PARALLEL_NUM>
class BlockCipherModeDecryptor : public BlockCipherMode
{
private:
    std::uint8_t buf_[BLOCK_SIZE * PARALLEL_NUM];
    std::size_t  pending_len_ = 0;

protected:
    Padding padding_ = Padding::None;

protected:
    virtual void update_blocks_(std::uint8_t*       out,
                                const std::uint8_t* in,
                                std::size_t         block_num) = 0;

    // ==========================================
    // ================ Constructor =============
    // ==========================================
public:
    ~BlockCipherModeDecryptor()
    {
        std::memset(buf_, 0, sizeof(buf_));
        pending_len_ = 0;
    }

    // ==============================================
    // ============ Functionality functions =========
    // ==============================================

protected:
    void init_() noexcept
    {
        pending_len_ = 0;
    }

public:
    void update(std::uint8_t*       out,
                std::size_t*        outl,
                std::size_t         outl_max,
                const std::uint8_t* in,
                std::size_t         inl) override final
    {
        std::size_t total_pending_len  = pending_len_ + inl;
        std::size_t remain_pending_len = total_pending_len % BLOCK_SIZE;
        if (remain_pending_len == 0 && total_pending_len > 0)
        {
            remain_pending_len = BLOCK_SIZE;
        }
        if (outl_max < total_pending_len - remain_pending_len)
        {
            throw std::length_error(Error::BUFFER_TOO_SMALL);
        }

        *outl = total_pending_len - remain_pending_len;
        // ==============================================
        //  situation1: pending_len_ + inl <= BLOCK_SIZE
        // ==============================================
        // |--------- BLOCK_SIZE -----------|
        // |--- pending ---|--- inl ---|
        // |---- remain_pending_len ---|
        // ==============================================
        if (pending_len_ + inl == remain_pending_len)
        {
            if (inl > 0)
            {
                std::memcpy(buf_ + pending_len_, in, inl);
                pending_len_ += inl;
            }
        }
        // ==============================================
        //  situation2: pending_len_ + inl > BLOCK_SIZE
        // ==============================================
        // |--- BLOCK_SIZE ---|--- remain_pending_len ---|
        // |--- pending ---|----------- inl -------------|
        // ==============================================
        else
        {
            // prologue
            if (pending_len_ > 0)
            {
                std::size_t cpy_size = inl - remain_pending_len;
                if (sizeof(buf_) - pending_len_ < cpy_size)
                {
                    cpy_size = sizeof(buf_) - pending_len_;
                }
                std::memcpy(buf_ + pending_len_, in, cpy_size);
                pending_len_ += cpy_size;
                in += cpy_size, inl -= cpy_size;

                std::size_t block_num = pending_len_ / BLOCK_SIZE;
                this->update_blocks_(out, buf_, block_num);
                out += block_num * BLOCK_SIZE;
                pending_len_ = 0;
            }
            // body
            while (inl - remain_pending_len >= sizeof(buf_))
            {
                std::memcpy(buf_, in, sizeof(buf_));
                in += sizeof(buf_), inl -= sizeof(buf_);
                this->update_blocks_(out, buf_, PARALLEL_NUM);
                out += PARALLEL_NUM * BLOCK_SIZE;
            }
            // epilogue
            if (inl - remain_pending_len > 0)
            {
                std::memcpy(buf_, in, inl - remain_pending_len);
                pending_len_ = inl - remain_pending_len;

                std::size_t block_num = pending_len_ / BLOCK_SIZE;
                this->update_blocks_(out, buf_, block_num);
                out += block_num * BLOCK_SIZE;
                pending_len_ = 0;
                in += block_num * BLOCK_SIZE, inl -= block_num * BLOCK_SIZE;
            }

            std::memcpy(buf_, in, inl);
            pending_len_ = inl;
        }
    }

    void do_final(std::uint8_t*       out,
                  std::size_t*        outl,
                  std::size_t         outl_max,
                  const std::uint8_t* in  = nullptr,
                  std::size_t         inl = 0) override final
    {
        *outl = 0;
        if (inl > 0)
        {
            this->update(out, outl, outl_max, in, inl);
            std::size_t outl_tmp = *outl;
            out += outl_tmp, outl_max -= outl_tmp;
        }

        if (padding_ == Padding::None)
        {
            if (pending_len_ != 0 && pending_len_ != BLOCK_SIZE)
            {
                throw std::invalid_argument(                 //
                    Error::DATA_NOT_MULTIPLE_OF_BLOCK_LENGTH //
                );                                           //
            }
            if (pending_len_ == BLOCK_SIZE)
            {
                if (outl_max < BLOCK_SIZE)
                {
                    throw std::length_error(Error::BUFFER_TOO_SMALL);
                }
                this->update_blocks_(out, buf_, 1);
                *outl += BLOCK_SIZE;
                pending_len_ = 0;
            }
        }
        else if (padding_ == Padding::PKCS7)
        {
            if (pending_len_ != BLOCK_SIZE)
            {
                throw std::invalid_argument(                 //
                    Error::DATA_NOT_MULTIPLE_OF_BLOCK_LENGTH //
                );                                           //
            }
            std::uint8_t buf_pt[BLOCK_SIZE];
            this->update_blocks_(buf_pt, buf_, 1);
            std::uint8_t pad_value = buf_pt[BLOCK_SIZE - 1];
            if ((std::size_t)pad_value > BLOCK_SIZE || pad_value == 0)
            {
                throw std::invalid_argument(Error::BAD_DECRYPT);
            }
            for (std::size_t i = 0; i < (std::size_t)pad_value; i++)
            {
                if (buf_pt[BLOCK_SIZE - 1 - i] != pad_value)
                {
                    throw std::invalid_argument(Error::BAD_DECRYPT);
                }
            }
            std::size_t plaintext_len = BLOCK_SIZE - (std::size_t)pad_value;
            if (outl_max < plaintext_len)
            {
                throw std::length_error(Error::BUFFER_TOO_SMALL);
            }
            std::memcpy(out, buf_pt, plaintext_len);
            *outl += plaintext_len;
            pending_len_ = 0;
        }
        else
        {
            throw std::invalid_argument("INVALID_PADDING");
        }
    }

    // ==============================================
    // ============ Getter/Setter functions =========
    // ==============================================

    bool get_padding() const override final
    {
        return padding_ == Padding::PKCS7;
    }

    void set_padding(bool value) override final
    {
        padding_ = value ? Padding::PKCS7 : Padding::None;
    }
};

template <std::size_t BLOCK_SIZE,
          std::size_t PARALLEL_NUM,
          std::size_t ALIGNMENT = alignof(std::uint8_t)>
class BlockCipherModeStreamCryptor : public BlockCipherMode
{
private:
    alignas(ALIGNMENT) std::uint8_t key_stream_buf_[BLOCK_SIZE * PARALLEL_NUM];
    std::size_t key_stream_idx_;

public:
    ~BlockCipherModeStreamCryptor()
    {
        std::memset(key_stream_buf_, 0, sizeof(key_stream_buf_));
        key_stream_idx_ = 0;
    }

protected:
    void init_() noexcept
    {
        key_stream_idx_ = sizeof(key_stream_buf_);
    }

    /**
     * @brief Generate blocks in [offset_block_num, total_block_num)
     * @param key_stream_blocks points to the buffer start, aligned to ALIGNMENT
     * @param offset_block_num  the block number to start
     * @param total_block_num   the total block number
     */
    virtual void generate_key_stream_blocks_(std::uint8_t* key_stream_blocks,
                                             std::size_t   offset_block_num,
                                             std::size_t   total_block_num) = 0;

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
                in += update_size, inl -= update_size;
                out += update_size;
                key_stream_idx_ += update_size;
            }
        }
        // body
        while (inl >= sizeof(key_stream_buf_))
        {
            this->generate_key_stream_blocks_(key_stream_buf_, 0, PARALLEL_NUM);
            memory_utils::memxor_n(                               //
                out, key_stream_buf_, in, sizeof(key_stream_buf_) //
            );                                                    //
            out += sizeof(key_stream_buf_);
            in += sizeof(key_stream_buf_), inl -= sizeof(key_stream_buf_);
        }
        // epilogue
        if (inl > 0)
        {
            std::size_t block_num = (inl + BLOCK_SIZE - 1) / BLOCK_SIZE;
            std::size_t offset    = (PARALLEL_NUM - block_num) * BLOCK_SIZE;
            this->generate_key_stream_blocks_(                          //
                key_stream_buf_, PARALLEL_NUM - block_num, PARALLEL_NUM //
            );                                                          //
            memory_utils::memxor_n(out, key_stream_buf_ + offset, in, inl);
            key_stream_idx_ = offset + inl;
        }
        *outl = input_len;
    }

    void do_final(std::uint8_t*       out,
                  std::size_t*        outl,
                  std::size_t         outl_max,
                  const std::uint8_t* in  = nullptr,
                  std::size_t         inl = 0) override
    {
        this->BlockCipherModeStreamCryptor::update( //
            out, outl, outl_max, in, inl            //
        );                                          //
    }

public:
    void set_padding(bool value) override final
    {
        (void)value;
    }

    bool get_padding() const override final
    {
        return false;
    }
};

} // namespace block_cipher_mode::impl

#endif
