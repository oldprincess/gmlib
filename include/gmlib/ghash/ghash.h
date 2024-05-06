#ifndef GHASH_GHASH_H
#define GHASH_GHASH_H

#include <gmlib/ghash/internal/ghash_common.h>
#include <gmlib/ghash/internal/ghash_lut256.h>
#include <gmlib/ghash/internal/ghash_pclmul.h>
#include <gmlib/hash_lib/hash.h>

#include <stdexcept>

#if defined(CPU_FLAG_PCLMUL) && defined(CPU_FLAG_SSE2)
namespace alg = ghash::internal::pclmul;
#else
namespace alg = ghash::internal::lut256;
#endif

// namespace alg = ghash::internal::common;

namespace ghash {

class GHash : public hash_lib::HashImpl<alg::GHASH_BLOCK_SIZE>
{
public:
    static constexpr const char* NAME         = "GHash";
    static constexpr std::size_t NAME_STR_LEN = 5;
    static constexpr std::size_t BLOCK_SIZE   = alg::GHASH_BLOCK_SIZE;
    static constexpr std::size_t DIGEST_SIZE  = alg::GHASH_DIGEST_SIZE;

private:
    alg::GHashCTX ctx_;

public:
    GHash() = default;

    GHash(const std::uint8_t H[16]) noexcept
    {
        alg::ghash_init(&ctx_, H);
    }

    void reset() noexcept override
    {
        alg::ghash_reset(&ctx_);
    }

    void set_key(const std::uint8_t H[16]) noexcept
    {
        alg::ghash_init(&ctx_, H);
    }

public:
    const char* fetch_name() const noexcept override
    {
        return NAME;
    }

    std::size_t fetch_name_str_len() const noexcept override
    {
        return NAME_STR_LEN;
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t fetch_digest_size() const noexcept override
    {
        return DIGEST_SIZE;
    }

private:
    void update_blocks(const std::uint8_t* in,
                       std::size_t         block_num) noexcept override
    {
        alg::ghash_update_blocks(&ctx_, in, block_num);
    }

    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        int err = alg::ghash_final_block(&ctx_, digest, in, inl);
        if (err != 0)
        {
            throw std::runtime_error("err in ghash final block");
        }
    }
};

} // namespace ghash

#endif