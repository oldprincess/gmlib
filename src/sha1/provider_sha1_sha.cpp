#if defined(SUPPORT_SHA1_SHA)

#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/hash_lib/impl/hash_impl.h>

#include <stdexcept>

#include "provider_sha1_sha.h"
#include "sha1_sha.h"

namespace sha1::internal::sha {

class SHA1Impl : public hash_lib::impl::HashImpl<64>
{
private:
    std::uint32_t state_[5];
    std::uint64_t data_bits_;

public:
    SHA1Impl() noexcept
    {
        sha1_init(state_, &data_bits_);
    }

    const char* fetch_name() const noexcept override
    {
        return "SHA1";
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return SHA1_ALGO_NAME;
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return 64;
    }

    std::size_t fetch_digest_size() const noexcept override
    {
        return 20;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return 10;
    }

    void reset() noexcept override
    {
        this->HashImpl<64>::reset();
        sha1_reset(state_, &data_bits_);
    }

    hash_lib::Hash::HashPtr clone() const override
    {
        return std::make_unique<SHA1Impl>(*this);
    }

protected:
    void update_blocks(const std::uint8_t* in, std::size_t block_num) override
    {
        int ret = sha1_update_blocks(state_, &data_bits_, in, block_num);
        if (ret != 0)
        {
            throw std::runtime_error("sha1 update blocks error");
        }
    }

    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        int ret = sha1_final_block(state_, &data_bits_, digest, in, inl);
        if (ret != 0)
        {
            throw std::runtime_error("sha1 final block error");
        }
    }
};

bool provider_available()
{
    return cpuinfo::x86_64::cpu_supports_sha() &&
           cpuinfo::x86_64::cpu_supports_sse4_1();
}

hash_lib::Hash::HashPtr create_hash()
{
    return std::make_unique<SHA1Impl>();
}

} // namespace sha1::internal::sha

#endif
