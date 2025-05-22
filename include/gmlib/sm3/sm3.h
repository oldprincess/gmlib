#ifndef SM3_SM3_H
#define SM3_SM3_H

#include <gmlib/hash_lib/impl/hash_impl.h>

namespace sm3 {

/**
 * @brief   SM3 cryptographic hash algorithm
 * @details GB/T 32905-2016
 */
class SM3 : public hash_lib::impl::HashImpl<64>
{
public:
    static constexpr const char* NAME = "SM3";

    /// @brief SM3 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 64;

    /// @brief SM3 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = 32;

    /// @brief SM3 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = 16;

private:
    /// @brief SM3 private Context
    std::uint32_t state_[8];
    std::uint64_t data_bits_;

public:
    /**
     * @brief SM3 Context Init
     */
    SM3() noexcept;

public:
    /**
     * @brief   get the Name of Hash Algorithm
     * @return  Name of Hash Algorithm
     */
    const char* fetch_name() const noexcept override
    {
        return NAME;
    }

    const char* fetch_impl_algo() const noexcept override;

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
     * @brief SM3 Context Reset (re-init)
     */
    void reset() noexcept override;

private:
    /**
     * @brief                   SM3 message update
     * @param[in]   in          BLOCK_SIZE x block_num -bytes input data
     * @param[in]   block_num   input data block number
     */
    void update_blocks(const std::uint8_t* in, std::size_t block_num) override;

    /**
     * @brief               SM3 update final message block and output digest
     * @param[out]  digest  32-bytes digest data
     * @param[in]   in      input data, not bigger than 64 bytes
     * @param[in]   inl     input length (in bytes)
     */
    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override;
};

} // namespace sm3

#endif