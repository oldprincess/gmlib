#ifndef MD5_MD5_H
#define MD5_MD5_H

#include <gmlib/hash_lib/hash.h>
#include <gmlib/md5/internal/md5_common.h>

namespace md5 {
namespace alg = md5::internal::common;
} // namespace md5

namespace md5 {

class MD5 : public hash_lib::HashImpl<alg::MD5_BLOCK_SIZE>
{
public:
    static constexpr const char* NAME = "MD5";

    static constexpr std::size_t NAME_STR_LEN = 3;

    /// @brief MD5 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = alg::MD5_BLOCK_SIZE;

    /// @brief MD5 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = alg::MD5_DIGEST_SIZE;

    /// @brief MD5 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = alg::MD5_SECURITY_STRENGTH;

private:
    /// @brief MD5 private Context
    alg::Md5CTX ctx_;

public:
    /**
     * @brief MD5 Context Init
     */
    MD5() noexcept
    {
        alg::md5_init(&ctx_);
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
     * @brief MD5 Context Reset (re-init)
     */
    void reset() noexcept override
    {
        this->HashImpl<alg::MD5_BLOCK_SIZE>::reset();
        alg::md5_reset(&ctx_);
    }

private:
    /**
     * @brief                   MD5 message update
     * @param[in]   in          BLOCK_SIZE x block_num -bytes input data
     * @param[in]   block_num   input data block number
     */
    void update_blocks(const std::uint8_t* in,
                       std::size_t         block_num) noexcept override
    {
        alg::md5_update_blocks(&ctx_, in, block_num);
    }

    /**
     * @brief               MD5 update final message block and output digest
     * @param[out]  digest  16-bytes digest data
     * @param[in]   in      input data, not bigger than 64 bytes
     * @param[in]   inl     input length (in bytes)
     */
    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) noexcept override
    {
        alg::md5_final_block(&ctx_, digest, in, inl);
    }
};

} // namespace md5

#endif