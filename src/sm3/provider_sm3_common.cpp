#include "config.h"

#if defined(SM3_IMPL_COMMON)

#include <gmlib/hash_lib/impl/hash_impl.h>

#include <stdexcept>

#include "provider_sm3_common.h"
#include "sm3_common.h"

namespace sm3::internal::common {

class SM3Impl : public hash_lib::impl::HashImpl<64>
{
private:
    std::uint32_t state_[8];
    std::uint64_t data_bits_;

public:
    SM3Impl() noexcept
    {
        sm3_init(state_, &data_bits_);
    }

    const char* fetch_name() const noexcept override
    {
        return "SM3";
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return SM3_ALGO_NAME;
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
        sm3_reset(state_, &data_bits_);
    }

    hash_lib::Hash::HashPtr clone() const override
    {
        return std::make_unique<SM3Impl>(*this);
    }

protected:
    void update_blocks(const std::uint8_t* in, std::size_t block_num) override
    {
        int ret = sm3_update_blocks(state_, &data_bits_, in, block_num);
        if (ret != 0)
        {
            throw std::runtime_error("sm3 update blocks error");
        }
    }

    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        int ret = sm3_final_block(state_, &data_bits_, digest, in, inl);
        if (ret != 0)
        {
            throw std::runtime_error("sm3 final block error");
        }
    }
};

bool provider_available()
{
    return true;
}

hash_lib::Hash::HashPtr create_hash()
{
    return std::make_unique<SM3Impl>();
}

} // namespace sm3::internal::common

#endif