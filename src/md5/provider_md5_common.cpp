#include "provider_md5_common.h"

#include <gmlib/hash_lib/impl/hash_impl.h>

#include "md5_common.h"

namespace md5::internal::common {

class MD5Impl : public hash_lib::impl::HashImpl<64>
{
private:
    std::uint32_t state_[4];
    std::uint64_t data_bits_;

public:
    MD5Impl() noexcept
    {
        md5_init(state_, &data_bits_);
    }

    const char* fetch_name() const noexcept override
    {
        return "MD5";
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return MD5_ALGO_NAME;
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return 64;
    }

    std::size_t fetch_digest_size() const noexcept override
    {
        return 16;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return 8;
    }

    void reset() noexcept override
    {
        this->HashImpl<64>::reset();
        md5_reset(state_, &data_bits_);
    }

    hash_lib::Hash::HashPtr clone() const override
    {
        return std::make_unique<MD5Impl>(*this);
    }

protected:
    void update_blocks(const std::uint8_t* in,
                       std::size_t         block_num) noexcept override
    {
        md5_update_blocks(state_, &data_bits_, in, block_num);
    }

    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) noexcept override
    {
        md5_final_block(state_, &data_bits_, digest, in, inl);
    }
};

bool provider_available()
{
    return true;
}

hash_lib::Hash::HashPtr create_hash()
{
    return std::make_unique<MD5Impl>();
}

} // namespace md5::internal::common
