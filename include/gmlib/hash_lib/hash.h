#ifndef HASH_LIB_HASH_H
#define HASH_LIB_HASH_H

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace hash_lib {

class Hash_Base
{
public:
    virtual ~Hash_Base() = default;

    virtual void reset() = 0;

    virtual void update(const std::uint8_t* in, std::size_t inl) = 0;

    virtual void do_final(std::uint8_t*       digest,
                          const std::uint8_t* in  = nullptr,
                          std::size_t         inl = 0) = 0;

    virtual const char* name() const noexcept = 0;
};

template <std::size_t BLOCK_SIZE>
class Hash : public Hash_Base
{
private:
    std::uint8_t buf_[BLOCK_SIZE];
    std::size_t  buf_size_;

public:
    Hash() noexcept : buf_size_(0)
    {
    }

protected:
    void reset_() noexcept
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
                  std::size_t         inl = 0) override
    {
        this->update(in, inl);
        this->final_block(digest, buf_, buf_size_);
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