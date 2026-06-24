#ifndef HASH_LIB_IMPL_HASH_IMPL_H
#define HASH_LIB_IMPL_HASH_IMPL_H

#include <gmlib/hash_lib/hash.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace hash_lib::impl {

template <std::size_t BLOCK_SIZE_>
class HashImpl : public Hash
{
private:
    std::uint8_t buf_[BLOCK_SIZE_];
    std::size_t  buf_size_ = 0;

protected:
    HashImpl() = default;

    void reset() noexcept override
    {
        buf_size_ = 0;
    }

public:
    void update(const std::uint8_t* in, std::size_t inl) override
    {
        if (inl == 0)
        {
            return;
        }
        if (buf_size_ == 0)
        {
            std::size_t block_num = inl / BLOCK_SIZE_;
            this->update_blocks(in, block_num);
            in += block_num * BLOCK_SIZE_, inl -= block_num * BLOCK_SIZE_;
            if (inl)
            {
                std::memcpy(buf_, in, inl);
                buf_size_ = inl;
            }
            return;
        }
        if (inl)
        {
            std::size_t size = BLOCK_SIZE_ - buf_size_;
            if (size > inl)
            {
                size = inl;
            }
            std::memcpy(buf_ + buf_size_, in, size);
            in += size, inl -= size, buf_size_ += size;

            if (buf_size_ == BLOCK_SIZE_)
            {
                this->update_blocks(buf_, 1);
                buf_size_ = 0;
            }
        }
        if (inl && buf_size_ == 0)
        {
            std::size_t block_num = inl / BLOCK_SIZE_;
            this->update_blocks(in, block_num);
            in += block_num * BLOCK_SIZE_, inl -= block_num * BLOCK_SIZE_;
            if (inl)
            {
                std::memcpy(buf_, in, inl);
                buf_size_ = inl;
            }
            return;
        }
        return;
    }

    void do_final(std::uint8_t*       digest,
                  const std::uint8_t* in  = nullptr,
                  std::size_t         inl = 0) override
    {
        this->update(in, inl);
        this->final_block(digest, buf_, buf_size_);
    }

public:
    void ctrl(const char* cmd, std::size_t argc, void* argv[]) override
    {
        (void)cmd;
        (void)argc;
        (void)argv;
        throw std::runtime_error("HashImpl does not support ctrl");
    }

protected:
    virtual void update_blocks(const std::uint8_t* in,
                               std::size_t         block_num) = 0;

    virtual void final_block(std::uint8_t*       digest,
                             const std::uint8_t* in,
                             std::size_t         inl) = 0;
};

} // namespace hash_lib::impl

#endif
