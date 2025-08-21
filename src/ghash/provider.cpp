#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/ghash/ghash.h>

#include <cstring>
#include <stdexcept>

#include "config.h"
#include "ghash_common.h"
#include "ghash_lut256.h"
#include "ghash_pclmul.h"

namespace ghash {

struct GHashProvider
{
    bool (*available)();

    const char* algo_name;

    std::size_t ctx_size;

    void (*init)(void* ctx, const std::uint8_t H[16]);

    void (*reset)(void* ctx);

    void (*update_blocks)(void*               ctx,
                          const std::uint8_t* in,
                          std::size_t         block_num);

    int (*final_block)(const void*         ctx,
                       std::uint8_t        digest[16],
                       const std::uint8_t* in,
                       std::size_t         inl);
};

static GHashProvider ghash_providers[] = {

#if defined(GHASH_IMPL_PCLMUL)
    {
        []() {
            return cpuinfo::x86_64::cpu_supports_pclmulqdq() &&
                   cpuinfo::x86_64::cpu_supports_sse2();
        },
        ghash::internal::pclmul::GHASH_ALGO_NAME,
        sizeof(ghash::internal::pclmul::GHashCTX),
        [](void* ctx, const std::uint8_t H[16]) {
            namespace alg = ghash::internal::pclmul;
            alg::ghash_init((alg::GHashCTX*)ctx, H);
        },
        [](void* ctx) {
            namespace alg = ghash::internal::pclmul;
            alg::ghash_reset((alg::GHashCTX*)ctx);
        },
        [](void* ctx, const std::uint8_t* in, std::size_t block_num) {
            namespace alg = ghash::internal::pclmul;
            alg::ghash_update_blocks((alg::GHashCTX*)ctx, in, block_num);
        },
        [](const void*         ctx,
           std::uint8_t        digest[16],
           const std::uint8_t* in,
           std::size_t         inl) {
            namespace alg = ghash::internal::pclmul;
            return alg::ghash_final_block((alg::GHashCTX*)ctx, digest, in, inl);
        },
    },
#endif

#if defined(GHASH_IMPL_LUT256)
    {
        []() { return true; },
        ghash::internal::lut256::GHASH_ALGO_NAME,
        sizeof(ghash::internal::lut256::GHashCTX),
        [](void* ctx, const std::uint8_t H[16]) {
            namespace alg = ghash::internal::lut256;
            alg::ghash_init((alg::GHashCTX*)ctx, H);
        },
        [](void* ctx) {
            namespace alg = ghash::internal::lut256;
            alg::ghash_reset((alg::GHashCTX*)ctx);
        },
        [](void* ctx, const std::uint8_t* in, std::size_t block_num) {
            namespace alg = ghash::internal::lut256;
            alg::ghash_update_blocks((alg::GHashCTX*)ctx, in, block_num);
        },
        [](const void*         ctx,
           std::uint8_t        digest[16],
           const std::uint8_t* in,
           std::size_t         inl) {
            namespace alg = ghash::internal::lut256;
            return alg::ghash_final_block((alg::GHashCTX*)ctx, digest, in, inl);
        },
    },
#endif
    // universal
    {
        []() { return true; },
        ghash::internal::common::GHASH_ALGO_NAME,
        sizeof(ghash::internal::common::GHashCTX),
        [](void* ctx, const std::uint8_t H[16]) {
            namespace alg = ghash::internal::common;
            alg::ghash_init((alg::GHashCTX*)ctx, H);
        },
        [](void* ctx) {
            namespace alg = ghash::internal::common;
            alg::ghash_reset((alg::GHashCTX*)ctx);
        },
        [](void* ctx, const std::uint8_t* in, std::size_t block_num) {
            namespace alg = ghash::internal::common;
            alg::ghash_update_blocks((alg::GHashCTX*)ctx, in, block_num);
        },
        [](const void*         ctx,
           std::uint8_t        digest[16],
           const std::uint8_t* in,
           std::size_t         inl) {
            namespace alg = ghash::internal::common;
            return alg::ghash_final_block((alg::GHashCTX*)ctx, digest, in, inl);
        },
    },
    // end
    {nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr},
};

static const GHashProvider* get_provider(const GHashProvider* providers,
                                         const char* name = nullptr) noexcept
{
    std::size_t idx = 0;
    while (providers[idx].algo_name != nullptr)
    {
        if (providers[idx].available())
        {
            if (name == nullptr)
            {
                return &providers[idx];
            }

            if (std::strcmp(providers[idx].algo_name, name) == 0)
            {
                return &providers[idx];
            }
        }
        idx += 1;
    }
    std::printf("[GHASH PROVIDER] Provider %s is not available. %s:%d\n", name,
                __FILE__, __LINE__);
    std::exit(-1);
}

#define GHASH_PROVIDER get_provider(ghash_providers)
static void ghash_ctx_free(void* ctx)
{
    delete[] (std::uint8_t*)ctx;
}

GHash::GHash() : ctx_{nullptr, ghash_ctx_free}
{
    ctx_.reset(new std::uint8_t[GHASH_PROVIDER->ctx_size]);
}

GHash::GHash(const GHash& other) : ctx_{nullptr, ghash_ctx_free}
{
    ctx_.reset(new std::uint8_t[GHASH_PROVIDER->ctx_size]);
    std::memcpy(ctx_.get(), other.ctx_.get(), GHASH_PROVIDER->ctx_size);
}

GHash::GHash(const std::uint8_t H[16]) : ctx_{nullptr, ghash_ctx_free}
{
    ctx_.reset(new std::uint8_t[GHASH_PROVIDER->ctx_size]);
    this->set_key(H);
}

void GHash::set_key(const std::uint8_t H[16]) noexcept
{
    GHASH_PROVIDER->init(ctx_.get(), H);
}

void GHash::reset() noexcept
{
    this->HashImpl<GHash::BLOCK_SIZE>::reset();
    GHASH_PROVIDER->reset(ctx_.get());
}

GHash& GHash::operator=(const GHash& other) noexcept
{
    std::memcpy(ctx_.get(), other.ctx_.get(), GHASH_PROVIDER->ctx_size);
    return *this;
}

const char* GHash::fetch_impl_algo() const noexcept
{
    return GHASH_PROVIDER->algo_name;
}

void GHash::update_blocks(const std::uint8_t* in,
                          std::size_t         block_num) noexcept
{
    GHASH_PROVIDER->update_blocks(ctx_.get(), in, block_num);
}

void GHash::final_block(std::uint8_t*       digest,
                        const std::uint8_t* in,
                        std::size_t         inl)
{
    int ret = GHASH_PROVIDER->final_block(ctx_.get(), digest, in, inl);
    if (ret != 0)
    {
        throw std::runtime_error("ghash final block error");
    }
}

} // namespace ghash
