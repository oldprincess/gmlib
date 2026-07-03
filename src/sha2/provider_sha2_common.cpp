#include <gmlib/hash_lib/impl/hash_impl.h>

#include <stdexcept>

#include "provider_sha2_common.h"
#include "sha2_common.h"

namespace sha2::internal::common {

// =====================================================
// SHA224Impl
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
// SHA256Impl
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
// SHA384Impl
// =====================================================

class SHA384Impl : public hash_lib::impl::HashImpl<128>
{
private:
    std::uint8_t  state_[64];
    std::uint64_t data_bits_h_;
    std::uint64_t data_bits_l_;

public:
    SHA384Impl() noexcept
    {
        sha384_init(state_, &data_bits_h_, &data_bits_l_);
    }

    const char* fetch_name() const noexcept override
    {
        return "SHA384";
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return SHA2_ALGO_NAME;
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return 128;
    }

    std::size_t fetch_digest_size() const noexcept override
    {
        return 48;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return 24;
    }

    void reset() noexcept override
    {
        this->HashImpl<128>::reset();
        sha384_reset(state_, &data_bits_h_, &data_bits_l_);
    }

    hash_lib::Hash::HashPtr clone() const override
    {
        return std::make_unique<SHA384Impl>(*this);
    }

protected:
    void update_blocks(const std::uint8_t* in, std::size_t block_num) override
    {
        int ret = sha384_update_blocks(state_, &data_bits_h_, &data_bits_l_, in,
                                       block_num);
        if (ret != 0)
        {
            throw std::runtime_error("sha2 update blocks error");
        }
    }

    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        int ret = sha384_final_block(state_, &data_bits_h_, &data_bits_l_,
                                     digest, in, inl);
        if (ret != 0)
        {
            throw std::runtime_error("sha2 final block error");
        }
    }
};

// =====================================================
// SHA512Impl
// =====================================================

class SHA512Impl : public hash_lib::impl::HashImpl<128>
{
private:
    std::uint8_t  state_[64];
    std::uint64_t data_bits_h_;
    std::uint64_t data_bits_l_;

public:
    SHA512Impl() noexcept
    {
        sha512_init(state_, &data_bits_h_, &data_bits_l_);
    }

    const char* fetch_name() const noexcept override
    {
        return "SHA512";
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return SHA2_ALGO_NAME;
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return 128;
    }

    std::size_t fetch_digest_size() const noexcept override
    {
        return 64;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return 32;
    }

    void reset() noexcept override
    {
        this->HashImpl<128>::reset();
        sha512_reset(state_, &data_bits_h_, &data_bits_l_);
    }

    hash_lib::Hash::HashPtr clone() const override
    {
        return std::make_unique<SHA512Impl>(*this);
    }

protected:
    void update_blocks(const std::uint8_t* in, std::size_t block_num) override
    {
        int ret = sha512_update_blocks(state_, &data_bits_h_, &data_bits_l_, in,
                                       block_num);
        if (ret != 0)
        {
            throw std::runtime_error("sha2 update blocks error");
        }
    }

    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        int ret = sha512_final_block(state_, &data_bits_h_, &data_bits_l_,
                                     digest, in, inl);
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

hash_lib::Hash::HashPtr create_sha384()
{
    return std::make_unique<SHA384Impl>();
}

hash_lib::Hash::HashPtr create_sha512()
{
    return std::make_unique<SHA512Impl>();
}

} // namespace sha2::internal::common
