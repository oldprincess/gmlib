#ifndef SHA1_SHA1_H
#define SHA1_SHA1_H

#include <gmlib/hash_lib/hash.h>

#include <stdexcept>

#if defined(CPU_FLAG_SHA)
#include <gmlib/sha1/internal/sha1_sha.h>
namespace sha1 {
namespace alg = sha1::internal::sha;
} // namespace sha1
#else
#include <gmlib/sha1/internal/sha1_common.h>
namespace sha1 {
namespace alg = sha1::internal::common;
} // namespace sha1
#endif

namespace sha1 {

class SHA1 : public hash_lib::HashImpl<alg::SHA1_BLOCK_SIZE>
{
public:
    static constexpr const char* NAME = "SHA1";

    static constexpr std::size_t NAME_STR_LEN = 4;

    /// @brief SHA1 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = alg::SHA1_BLOCK_SIZE;

    /// @brief SHA1 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = alg::SHA1_DIGEST_SIZE;

    /// @brief SHA1 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH =
        alg::SHA1_SECURITY_STRENGTH;

private:
    /// @brief SHA1 private Context
    alg::Sha1CTX ctx_;

public:
    /**
     * @brief SHA1 Context Init
     */
    SHA1() noexcept
    {
        alg::sha1_init(&ctx_);
    }

public:
    /**
     * @brief   get the Name of Hash Algorithm
     * @return  Name of Hash Algorithm
     */
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

    std::size_t fetch_security_strength() const noexcept override
    {
        return SECURITY_STRENGTH;
    }

public:
    /**
     * @brief SHA1 Context Reset (re-init)
     */
    void reset() noexcept override
    {
        this->HashImpl<alg::SHA1_BLOCK_SIZE>::reset();
        alg::sha1_reset(&ctx_);
    }

private:
    /**
     * @brief                   SHA1 message update
     * @param[in]   in          BLOCK_SIZE x block_num -bytes input data
     * @param[in]   block_num   input data block number
     */
    void update_blocks(const std::uint8_t* in, std::size_t block_num) override
    {
        if (alg::sha1_update_blocks(&ctx_, in, block_num))
        {
            throw std::runtime_error("err in sha1 update blocks");
        }
    }

    /**
     * @brief               SHA1 update final message block and output digest
     * @param[out]  digest  20-bytes digest data
     * @param[in]   in      input data, not bigger than 64 bytes
     * @param[in]   inl     input length (in bytes)
     */
    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        if (alg::sha1_final_block(&ctx_, digest, in, inl))
        {
            throw std::runtime_error("err in sha1 final block");
        }
    }
};

} // namespace sha1

#endif