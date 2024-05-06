#ifndef HASH_LIB_HASH_H
#define HASH_LIB_HASH_H

#include <gmlib/hash_lib/abc.h>

#include <cstdio>
#include <cstdlib>

namespace hash_lib {

template <std::size_t _BLOCK_SIZE>
class HashImpl : public abc::Hash
{
public:
    static constexpr const char* NAME              = nullptr;
    static constexpr std::size_t NAME_STR_LEN      = 0;
    static constexpr std::size_t BLOCK_SIZE        = _BLOCK_SIZE;
    static constexpr std::size_t DIGEST_SIZE       = 0;
    static constexpr std::size_t SECURITY_STRENGTH = 0;

private:
    std::uint8_t buf_[BLOCK_SIZE];
    std::size_t  buf_size_;

public:
    inline const char* fetch_name() const noexcept override;

    inline std::size_t fetch_name_str_len() const noexcept override;

    inline std::size_t fetch_block_size() const noexcept override;

    inline std::size_t fetch_digest_size() const noexcept override;

    inline std::size_t fetch_security_strength() const noexcept override;

protected:
    inline HashImpl() noexcept;

    inline void reset() noexcept override;

public:
    inline void update(const std::uint8_t* in, std::size_t inl) override;

    inline void do_final(std::uint8_t*       digest,
                         const std::uint8_t* in  = nullptr,
                         std::size_t         inl = 0) override;

private:
    virtual void update_blocks(const std::uint8_t* in,
                               std::size_t         block_num) = 0;

    virtual void final_block(std::uint8_t*       digest,
                             const std::uint8_t* in,
                             std::size_t         inl) = 0;
};

// ======================

#define PRINT_ERR_AND_EXIT(exit_code)                                   \
    std::printf("[gmlib error] function not implemented. in file: %s, " \
                "func: %s, line: %d\n",                                 \
                __FILE__, __FUNCTION__, __LINE__);                      \
    std::exit(exit_code)

template <std::size_t BLOCK_SIZE>
const char* HashImpl<BLOCK_SIZE>::fetch_name() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

template <std::size_t BLOCK_SIZE>
std::size_t HashImpl<BLOCK_SIZE>::fetch_name_str_len() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

template <std::size_t BLOCK_SIZE>
std::size_t HashImpl<BLOCK_SIZE>::fetch_block_size() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

template <std::size_t BLOCK_SIZE>
std::size_t HashImpl<BLOCK_SIZE>::fetch_digest_size() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

template <std::size_t BLOCK_SIZE>
std::size_t HashImpl<BLOCK_SIZE>::fetch_security_strength() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

#undef PRINT_ERR_AND_EXIT

// ==========================

template <std::size_t BLOCK_SIZE>
HashImpl<BLOCK_SIZE>::HashImpl() noexcept : buf_size_(0)
{
}

template <std::size_t BLOCK_SIZE>
void HashImpl<BLOCK_SIZE>::reset() noexcept
{
    buf_size_ = 0;
}

template <std::size_t BLOCK_SIZE>
void HashImpl<BLOCK_SIZE>::update(const std::uint8_t* in, std::size_t inl)
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

template <std::size_t BLOCK_SIZE>
void HashImpl<BLOCK_SIZE>::do_final(std::uint8_t*       digest,
                                    const std::uint8_t* in,
                                    std::size_t         inl)
{
    this->update(in, inl);
    this->final_block(digest, buf_, buf_size_);
}

} // namespace hash_lib

#endif