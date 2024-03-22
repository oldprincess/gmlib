#ifndef SM3_SM3_H
#define SM3_SM3_H

#include <gmlib/hash_lib/hash.h>

#include <stdexcept>

#if defined(SUPPORT_SM3_YANG15)
#include <gmlib/sm3/internal/sm3_yang15.h>
namespace sm3 {
namespace alg = sm3::internal::yang15;
} // namespace sm3
#else
#include <gmlib/sm3/internal/sm3_common.h>
namespace sm3 {
namespace alg = sm3::internal::common;
} // namespace sm3
#endif

namespace sm3 {

/**
 * @brief   SM3 cryptographic hash algorithm
 * @details GB/T 32905-2016
 */
class SM3 : public hash_lib::Hash<alg::SM3_BLOCK_SIZE>
{
public:
    /// @brief SM4 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = alg::SM3_BLOCK_SIZE;

    /// @brief SM4 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = alg::SM3_DIGEST_SIZE;

private:
    /// @brief SM3 private Context
    alg::Sm3CTX ctx_;

public:
    /**
     * @brief SM3 Context Init
     */
    SM3() noexcept
    {
        alg::sm3_init(&ctx_);
    }

public:
    /**
     * @brief SM3 Context Reset (re-init)
     */
    void reset() noexcept
    {
        this->Hash<alg::SM3_BLOCK_SIZE>::reset();
        alg::sm3_reset(&ctx_);
    }

    /**
     * @brief   get the Name of Hash Algorithm
     * @return  Name of Hash Algorithm
     */
    const char* name() const noexcept override
    {
        return "SM3";
    }

private:
    /**
     * @brief                   SM3 message update
     * @param[in]   in          BLOCK_SIZE x block_num -bytes input data
     * @param[in]   block_num   input data block number
     */
    void update_blocks(const std::uint8_t* in, std::size_t block_num) override
    {
        if (alg::sm3_update_blocks(&ctx_, in, block_num))
        {
            throw std::runtime_error("err in sm3 update blocks");
        }
    }

    /**
     * @brief               SM3 update final message block and output digest
     * @param[out]  digest  32-bytes digest data
     * @param[in]   in      input data, not bigger than 64 bytes
     * @param[in]   inl     input length (in bytes)
     */
    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        if (alg::sm3_final_block(&ctx_, digest, in, inl))
        {
            throw std::runtime_error("err in sm3 final block");
        }
    }
};

} // namespace sm3

#endif