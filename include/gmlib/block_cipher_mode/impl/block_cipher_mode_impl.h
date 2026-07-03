#ifndef BLOCK_CIPHER_MODE_IMPL_BLOCK_CIPHER_MODE_IMPL_H
#define BLOCK_CIPHER_MODE_IMPL_BLOCK_CIPHER_MODE_IMPL_H

#include <gmlib/block_cipher_mode/block_cipher_mode.h>

#include <cstring>
#include <stdexcept>

namespace block_cipher_mode::impl {

template <std::size_t BLOCK_SIZE_>
class BlockCipherModeImpl : public BlockCipherMode
{
protected:
    std::uint8_t buf_[BLOCK_SIZE_];
    std::size_t  buf_size_ = 0;

protected:
    ~BlockCipherModeImpl()
    {
        std::memset(buf_, 0, sizeof(buf_));
        buf_size_ = 0;
    }

public:
    void update(std::uint8_t*       out,
                std::size_t*        outl,
                const std::uint8_t* in,
                std::size_t         inl) override
    {
        this->update(out, outl, (std::size_t)(-1), in, inl);
    }

    void update(std::uint8_t*       out,
                std::size_t*        outl,
                std::size_t         outl_max,
                const std::uint8_t* in,
                std::size_t         inl) override
    {
        std::size_t total_size  = buf_size_ + inl;
        std::size_t output_size = total_size - total_size % BLOCK_SIZE_;
        if (output_size > outl_max)
        {
            throw std::length_error(
                "block cipher mode output buffer is too small");
        }

        if (in == 0)
        {
            *outl = 0;
            return;
        }
        std::uint8_t* out_base = (std::uint8_t*)out;
        if (buf_size_ == 0)
        {
            std::size_t block_num = inl / BLOCK_SIZE_;
            std::size_t size      = block_num * BLOCK_SIZE_;
            this->update_blocks(out, in, block_num);
            out += size, in += size, inl -= size;

            std::memcpy(buf_, in, inl);
            buf_size_ = inl, *outl = (std::size_t)(out - out_base);

            return;
        }
        {
            std::size_t size = BLOCK_SIZE_ - buf_size_;
            if (size > inl)
            {
                size = inl;
            }
            std::memcpy(buf_ + buf_size_, in, size);
            buf_size_ += size, in += size, inl -= size;

            if (buf_size_ == BLOCK_SIZE_)
            {
                this->update_blocks(out, buf_, 1);
                buf_size_ = 0, out += BLOCK_SIZE_;
            }
        }
        if (buf_size_ == 0)
        {
            std::size_t block_num = inl / BLOCK_SIZE_;
            std::size_t size      = block_num * BLOCK_SIZE_;
            this->update_blocks(out, in, block_num);
            out += size, in += size, inl -= size;

            std::memcpy(buf_, in, inl);
            buf_size_ = inl, *outl = (std::size_t)(out - out_base);
        }
    }

    void do_final(std::uint8_t*       out,
                  std::size_t*        outl,
                  const std::uint8_t* in  = nullptr,
                  std::size_t         inl = 0) override
    {
        this->do_final(out, outl, (std::size_t)(-1), in, inl);
    }

    void do_final(std::uint8_t*       out,
                  std::size_t*        outl,
                  std::size_t         outl_max,
                  const std::uint8_t* in  = nullptr,
                  std::size_t         inl = 0) override
    {
        if (buf_size_ + inl > outl_max)
        {
            throw std::length_error(
                "block cipher mode output buffer is too small");
        }

        this->update(out, outl, outl_max, in, inl);
        out += *outl;
        this->final_block(out, buf_, buf_size_);
        *outl += buf_size_;
    }

protected:
    void reset() noexcept
    {
        buf_size_ = 0;
    }

protected:
    virtual void update_blocks(std::uint8_t*       out,
                               const std::uint8_t* in,
                               std::size_t         block_num) = 0;

    virtual void final_block(std::uint8_t*       out,
                             const std::uint8_t* in,
                             std::size_t         inl) = 0;
};

class BlockCipherModeForwarder : public BlockCipherMode
{
protected:
    static void dispatch_ctrl(BlockCipherMode& mode,
                              const char*      cmd,
                              std::size_t      argc,
                              void*            argv[])
    {
        mode.ctrl(cmd, argc, argv);
    }

public:
    const char* fetch_name() const noexcept override
    {
        return impl().fetch_name();
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return impl().fetch_block_size();
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return impl().fetch_user_key_len();
    }

    const BlockCipher& fetch_cipher_ctx() const noexcept override
    {
        return impl().fetch_cipher_ctx();
    }

    void ctrl(const char* cmd, std::size_t argc, void* argv[]) override
    {
        impl().ctrl(cmd, argc, argv);
    }

    void update(std::uint8_t*       out,
                std::size_t*        outl,
                const std::uint8_t* in,
                std::size_t         inl) override
    {
        impl().update(out, outl, (std::size_t)(-1), in, inl);
    }

    void do_final(std::uint8_t*       out,
                  std::size_t*        outl,
                  const std::uint8_t* in  = nullptr,
                  std::size_t         inl = 0) override
    {
        impl().do_final(out, outl, (std::size_t)(-1), in, inl);
    }

    void update(std::uint8_t*       out,
                std::size_t*        outl,
                std::size_t         outl_max,
                const std::uint8_t* in,
                std::size_t         inl) override
    {
        impl().update(out, outl, outl_max, in, inl);
    }

    void do_final(std::uint8_t*       out,
                  std::size_t*        outl,
                  std::size_t         outl_max,
                  const std::uint8_t* in  = nullptr,
                  std::size_t         inl = 0) override
    {
        impl().do_final(out, outl, outl_max, in, inl);
    }

private:
    virtual BlockCipherMode&       impl() noexcept       = 0;
    virtual const BlockCipherMode& impl() const noexcept = 0;
};

} // namespace block_cipher_mode::impl

#endif
