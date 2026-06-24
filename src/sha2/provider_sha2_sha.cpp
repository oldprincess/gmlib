#include "config.h"

#if defined(SHA224_256_IMPL_SHA)

#include <gmlib/hash_lib/impl/hash_impl.h>

#include <stdexcept>

#include "provider_sha2_sha.h"
#include "sha224_256_sha.h"

namespace sha2::internal::sha {

// =====================================================
// SHA224Impl (SHA intrinsics)
// =====================================================

class SHA224Impl : public hash_lib::impl::HashImpl<64>
{
private:
    std::uint8_t  state_[32];
    std::uint64_t data_bits_;

public:
    SHA224Impl() noexcept
    {
        sha224_init(state_, &data_bits_);
    }

    const char* fetch_name() const noexcept override
    {
        return "SHA224";
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return SHA2_ALGO_NAME;
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return 64;
    }

    std::size_t fetch_digest_size() const noexcept override
    {
        return 28;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return 14;
    }

    void reset() noexcept override
    {
        this->HashImpl<64>::reset();
        sha224_reset(state_, &data_bits_);
    }

    hash_lib::Hash::HashPtr clone() const override
    {
        return std::make_unique<SHA224Impl>(*this);
    }

protected:
    void update_blocks(const std::uint8_t* in, std::size_t block_num) override
    {
        int ret = sha224_update_blocks(state_, &data_bits_, in, block_num);
        if (ret != 0)
        {
            throw std::runtime_error("sha2 update blocks error");
        }
    }

    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        int ret = sha224_final_block(state_, &data_bits_, digest, in, inl);
        if (ret != 0)
        {
            throw std::runtime_error("sha2 final block error");
        }
    }
};

// =====================================================
// SHA256Impl (SHA intrinsics)
// =====================================================

class SHA256Impl : public hash_lib::impl::HashImpl<64>
{
private:
    std::uint8_t  state_[32];
    std::uint64_t data_bits_;

public:
    SHA256Impl() noexcept
    {
        sha256_init(state_, &data_bits_);
    }

    const char* fetch_name() const noexcept override
    {
        return "SHA256";
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return SHA2_ALGO_NAME;
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return 64;
    }

    std::size_t fetch_digest_size() const noexcept override
    {
        return 32;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return 16;
    }

    void reset() noexcept override
    {
        this->HashImpl<64>::reset();
        sha256_reset(state_, &data_bits_);
    }

    hash_lib::Hash::HashPtr clone() const override
    {
        return std::make_unique<SHA256Impl>(*this);
    }

protected:
    void update_blocks(const std::uint8_t* in, std::size_t block_num) override
    {
        int ret = sha256_update_blocks(state_, &data_bits_, in, block_num);
        if (ret != 0)
        {
            throw std::runtime_error("sha2 update blocks error");
        }
    }

    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        int ret = sha256_final_block(state_, &data_bits_, digest, in, inl);
        if (ret != 0)
        {
            throw std::runtime_error("sha2 final block error");
        }
    }
};

// =====================================================
// Provider functions
// =====================================================

bool provider_available()
{
    return true;
}

hash_lib::Hash::HashPtr create_sha224()
{
    return std::make_unique<SHA224Impl>();
}

hash_lib::Hash::HashPtr create_sha256()
{
    return std::make_unique<SHA256Impl>();
}

} // namespace sha2::internal::sha

#endif