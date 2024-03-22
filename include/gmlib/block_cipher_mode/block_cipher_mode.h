#ifndef BLOCK_CIPHER_MODE_BLOCK_CIPHER_MODE_H
#define BLOCK_CIPHER_MODE_BLOCK_CIPHER_MODE_H

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace block_cipher_mode {

template <std::size_t BLOCK_SIZE>
class BlockCipherMode
{
private:
    std::uint8_t buf_[BLOCK_SIZE];
    std::size_t  buf_size_;

public:
    virtual ~BlockCipherMode() = default;

protected:
    BlockCipherMode() noexcept : buf_size_(0)
    {
    }

    void reset() noexcept
    {
        buf_size_ = 0;
    }

public:
    void update(std::uint8_t*       out,
                std::size_t*        outl,
                const std::uint8_t* in,
                std::size_t         inl)
    {
        if (inl == 0)
        {
            *outl = 0;
            return;
        }
        std::uint8_t* out_base = out;
        if (buf_size_ == 0)
        {
            std::size_t block_num = inl / BLOCK_SIZE;
            std::size_t size      = block_num * BLOCK_SIZE;
            this->update_blocks(out, in, block_num);
            out += size, in += size, inl -= size;

            std::memcpy(buf_, in, inl);
            buf_size_ = inl, *outl = (std::size_t)(out - out_base);

            return;
        }
        {
            std::size_t size = BLOCK_SIZE - buf_size_;
            if (size > inl)
            {
                size = inl;
            }
            std::memcpy(buf_ + buf_size_, in, size);
            buf_size_ += size, in += size, inl -= size;

            if (buf_size_ == BLOCK_SIZE)
            {
                this->update_blocks(out, buf_, 1);
                buf_size_ = 0, out += BLOCK_SIZE;
            }
        }
        if (buf_size_ == 0)
        {
            std::size_t block_num = inl / BLOCK_SIZE;
            std::size_t size      = block_num * BLOCK_SIZE;
            this->update_blocks(out, in, block_num);
            out += size, in += size, inl -= size;

            std::memcpy(buf_, in, inl);
            buf_size_ = inl, *outl = (std::size_t)(out - out_base);
        }
    }

    void do_final(std::uint8_t*       out,
                  std::size_t*        outl,
                  const std::uint8_t* in  = nullptr,
                  std::size_t         inl = 0)
    {
        this->update(out, outl, in, inl);
        out += *outl;
        this->final_block(out, buf_, buf_size_);
        *outl += buf_size_;
    }

private:
    virtual void update_blocks(std::uint8_t*       out,
                               const std::uint8_t* in,
                               std::size_t         block_num) = 0;

    virtual void final_block(std::uint8_t*       out,
                             const std::uint8_t* in,
                             std::size_t         inl) = 0;
};

} // namespace block_cipher_mode

#endif