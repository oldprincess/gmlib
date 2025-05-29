#include <gmlib/ghash/ghash.h>

#include <cstring>
#include <stdexcept>

#include "config.h"

#if defined(GHASH_IMPL_PCLMUL)
#include "ghash_pclmul.h"
namespace ghash {
namespace alg = internal::pclmul;
} // namespace ghash
#else
#include "ghash_lut256.h"
namespace ghash {
namespace alg = internal::lut256;
} // namespace ghash
#endif

namespace ghash {

static void ghash_ctx_free(void* ctx)
{
    delete (alg::GHashCTX*)ctx;
}

GHash::GHash() : ctx_{nullptr, ghash_ctx_free}
{
    ctx_.reset(new alg::GHashCTX());
}

GHash::GHash(const GHash& other) : ctx_{nullptr, ghash_ctx_free}
{
    ctx_.reset(new alg::GHashCTX());
    std::memcpy(ctx_.get(), other.ctx_.get(), sizeof(alg::GHashCTX));
}

GHash::GHash(const std::uint8_t H[16]) : ctx_{nullptr, ghash_ctx_free}
{
    ctx_.reset(new alg::GHashCTX());
    this->set_key(H);
}

void GHash::set_key(const std::uint8_t H[16]) noexcept
{
    alg::ghash_init((alg::GHashCTX*)ctx_.get(), H);
}

void GHash::reset() noexcept
{
    this->HashImpl<GHash::BLOCK_SIZE>::reset();
    alg::ghash_reset((alg::GHashCTX*)ctx_.get());
}

GHash& GHash::operator=(const GHash& other) noexcept
{
    std::memcpy(ctx_.get(), other.ctx_.get(), sizeof(alg::GHashCTX));
    return *this;
}

const char* GHash::fetch_impl_algo() const noexcept
{
    return alg::GHASH_ALGO_NAME;
}

void GHash::update_blocks(const std::uint8_t* in,
                          std::size_t         block_num) noexcept
{
    alg::ghash_update_blocks((alg::GHashCTX*)ctx_.get(), in, block_num);
}

void GHash::final_block(std::uint8_t*       digest,
                        const std::uint8_t* in,
                        std::size_t         inl)
{
    int ret =
        alg::ghash_final_block((alg::GHashCTX*)ctx_.get(), digest, in, inl);
    if (ret != 0)
    {
        throw std::runtime_error("ghash final block error");
    }
}

} // namespace ghash
