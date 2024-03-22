#ifndef HASH_LIB_HASH_H
#define HASH_LIB_HASH_H

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace hash_lib {

template <std::size_t BLOCK_SIZE>
class Hash
{
private:
    std::uint8_t buf_[BLOCK_SIZE];
    std::size_t  buf_size_;

public:
    Hash() noexcept : buf_size_(0)
    {
    }

    virtual ~Hash() = default;

protected:
    void reset() noexcept
    {
        buf_size_ = 0;
    }

public:
    void update(const std::uint8_t* in, std::size_t inl)
    {
        if (inl == 0)
        {
            return;
        }
        if (buf_size_ == 0)
        {
            std::size_t block_num = inl / BLOCK_SIZE;
            this->update_blocks(in, block_num);
            in += block_num * BLOCK_SIZE, inl -= block_num * BLOCK_SIZE;
            if (inl)
            {
                std::memcpy(buf_, in, inl);
                buf_size_ = inl;
            }
            return;
        }
        if (inl)
        {
            std::size_t size = BLOCK_SIZE - buf_size_;
            if (size > inl)
            {
                size = inl;
            }
            std::memcpy(buf_ + buf_size_, in, size);
            in += size, inl -= size, buf_size_ += size;

            if (buf_size_ == BLOCK_SIZE)
            {
                this->update_blocks(buf_, 1);
                buf_size_ = 0;
            }
        }
        if (inl && buf_size_ == 0)
        {
            std::size_t block_num = inl / 64;
            this->update_blocks(in, block_num);
            in += block_num * BLOCK_SIZE, inl -= block_num * BLOCK_SIZE;
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
                  std::size_t         inl = 0)
    {
        this->update(in, inl);
        this->final_block(digest, buf_, buf_size_);
    }

public:
    virtual const char* name() const noexcept
    {
        return "Hash";
    }

private:
    virtual void update_blocks(const std::uint8_t* in,
                               std::size_t         block_num) = 0;

    virtual void final_block(std::uint8_t*       digest,
                             const std::uint8_t* in,
                             std::size_t         inl) = 0;
};

} // namespace hash_lib

#endif