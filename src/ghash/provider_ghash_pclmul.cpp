#include "config.h"

#if defined(GHASH_IMPL_PCLMUL)

#include <gmlib/hash_lib/impl/hash_impl.h>

#include <cstring>
#include <stdexcept>

#include "ghash_pclmul.h"
#include "provider_ghash_pclmul.h"

namespace ghash::internal::pclmul {

class GHashImpl : public hash_lib::impl::HashImpl<16>
{
private:
    GHashCTX ctx_;

public:
    GHashImpl() noexcept
    {
        std::memset(&ctx_, 0, sizeof(ctx_));
    }

    const char* fetch_name() const noexcept override
    {
        return "GHash";
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return GHASH_ALGO_NAME;
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return 16;
    }

    std::size_t fetch_digest_size() const noexcept override
    {
        return 16;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return 0;
    }

    void set_key(const std::uint8_t H[16]) noexcept
    {
        ghash_init(&ctx_, H);
    }

    void reset() noexcept override
    {
        this->HashImpl<16>::reset();
        ghash_reset(&ctx_);
    }

    hash_lib::Hash::HashPtr clone() const override
    {
        return std::make_unique<GHashImpl>(*this);
    }

    void ctrl(const char* cmd, std::size_t argc, void* argv[]) override
    {
        if (std::strcmp(cmd, "set_key") == 0)
        {
            if (argc != 1)
            {
                throw std::invalid_argument(
                    "GHashImpl ctrl set_key requires 1 argument");
            }
            this->set_key(*(const std::uint8_t**)argv[0]);
            return;
        }
        throw std::runtime_error("GHashImpl does not support ctrl");
    }

protected:
    void update_blocks(const std::uint8_t* in,
                       std::size_t         block_num) noexcept override
    {
        ghash_update_blocks(&ctx_, in, block_num);
    }

    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        int ret = ghash_final_block(&ctx_, digest, in, inl);
        if (ret != 0)
        {
            throw std::runtime_error("ghash final block error");
        }
    }
};

bool provider_available()
{
    return true;
}

hash_lib::Hash::HashPtr create_hash()
{
    return std::make_unique<GHashImpl>();
}

} // namespace ghash::internal::pclmul

#endif