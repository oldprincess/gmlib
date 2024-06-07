#ifndef BLOCK_CIPHER_MODE_BLOCK_CIPHER_MODE_H
#define BLOCK_CIPHER_MODE_BLOCK_CIPHER_MODE_H

#include <gmlib/block_cipher_mode/abc.h>

#include <cstdio>
#include <cstdlib>

namespace block_cipher_mode {

template <std::size_t _BLOCK_SIZE>
class BlockCipherModeImpl : public abc::BlockCipherMode
{
public:
    static constexpr const char* NAME_SUFFIX  = nullptr;
    static constexpr std::size_t NAME_STR_LEN = 0;
    static constexpr std::size_t BLOCK_SIZE   = _BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = 0;

public:
    inline const char* fetch_name() const noexcept override;

    inline std::size_t fetch_name_str_len() const noexcept override;

    inline std::size_t fetch_block_size() const noexcept override;

    inline std::size_t fetch_user_key_len() const noexcept override;

public:
    inline const abc::BlockCipher& fetch_cipher_ctx() const noexcept override;

private:
    std::uint8_t buf_[BLOCK_SIZE];
    std::size_t  buf_size_;

protected:
    inline BlockCipherModeImpl() noexcept;

    inline void reset() noexcept;

public:
    inline std::size_t init(const ConstParameter& params) override;

    inline std::size_t set(const ConstParameter& params) override;

    inline std::size_t get(const Parameter& params) override;

    inline void update(std::uint8_t*       out,
                       std::size_t*        outl,
                       const std::uint8_t* in,
                       std::size_t         inl) override;

    inline void do_final(std::uint8_t*       out,
                         std::size_t*        outl,
                         const std::uint8_t* in  = nullptr,
                         std::size_t         inl = 0) override;

private:
    inline virtual void update_blocks(std::uint8_t*       out,
                                      const std::uint8_t* in,
                                      std::size_t         block_num) = 0;

    inline virtual void final_block(std::uint8_t*       out,
                                    const std::uint8_t* in,
                                    std::size_t         inl) = 0;
};

// ================================

#define PRINT_ERR_AND_EXIT(exit_code)                                   \
    std::printf("[gmlib error] function not implemented. in file: %s, " \
                "func: %s, line: %d\n",                                 \
                __FILE__, __FUNCTION__, __LINE__);                      \
    std::exit(exit_code)

template <std::size_t BLOCK_SIZE>
const char* BlockCipherModeImpl<BLOCK_SIZE>::fetch_name() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

template <std::size_t BLOCK_SIZE>
std::size_t BlockCipherModeImpl<BLOCK_SIZE>::fetch_name_str_len() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

template <std::size_t BLOCK_SIZE>
std::size_t BlockCipherModeImpl<BLOCK_SIZE>::fetch_block_size() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

template <std::size_t BLOCK_SIZE>
std::size_t BlockCipherModeImpl<BLOCK_SIZE>::fetch_user_key_len() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

template <std::size_t BLOCK_SIZE>
const abc::BlockCipher& BlockCipherModeImpl<BLOCK_SIZE>::fetch_cipher_ctx()
    const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

#undef PRINT_ERR_AND_EXIT

// ==========================

template <std::size_t BLOCK_SIZE>
BlockCipherModeImpl<BLOCK_SIZE>::BlockCipherModeImpl() noexcept : buf_size_(0)
{
}

template <std::size_t BLOCK_SIZE>
void BlockCipherModeImpl<BLOCK_SIZE>::reset() noexcept
{
    buf_size_ = 0;
}

template <std::size_t BLOCK_SIZE>
std::size_t BlockCipherModeImpl<BLOCK_SIZE>::init(const ConstParameter& params)
{
    return 0;
}

template <std::size_t BLOCK_SIZE>
std::size_t BlockCipherModeImpl<BLOCK_SIZE>::set(const ConstParameter& params)
{
    return 0;
}

template <std::size_t BLOCK_SIZE>
std::size_t BlockCipherModeImpl<BLOCK_SIZE>::get(const Parameter& params)
{
    return 0;
}

template <std::size_t BLOCK_SIZE>
void BlockCipherModeImpl<BLOCK_SIZE>::update(std::uint8_t*       out,
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

template <std::size_t BLOCK_SIZE>
void BlockCipherModeImpl<BLOCK_SIZE>::do_final(std::uint8_t*       out,
                                               std::size_t*        outl,
                                               const std::uint8_t* in,
                                               std::size_t         inl)
{
    this->update(out, outl, in, inl);
    out += *outl;
    this->final_block(out, buf_, buf_size_);
    *outl += buf_size_;
}

} // namespace block_cipher_mode

#endif