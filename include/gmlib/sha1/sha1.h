#ifndef SHA1_SHA1_H
#define SHA1_SHA1_H

#include <gmlib/hash_lib/impl/hash_impl.h>

namespace sha1 {

class SHA1 : public hash_lib::impl::HashImpl<64>
{
public:
    static constexpr const char* NAME = "SHA1";

    /// @brief SHA1 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 64;

    /// @brief SHA1 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = 20;

    /// @brief SHA1 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = 10;

private:
    /// @brief SHA1 private Context
    std::uint32_t state_[5];
    std::uint64_t data_bits_;

public:
    /**
     * @brief SHA1 Context Init
     */
    SHA1() noexcept;

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
     * @brief SHA1 Context Reset (re-init)
     */
    void reset() noexcept override;

private:
    /**
     * @brief                   SHA1 message update
     * @param[in]   in          BLOCK_SIZE x block_num -bytes input data
     * @param[in]   block_num   input data block number
     */
    void update_blocks(const std::uint8_t* in, std::size_t block_num) override;

    /**
     * @brief               SHA1 update final message block and output digest
     * @param[out]  digest  20-bytes digest data
     * @param[in]   in      input data, not bigger than 64 bytes
     * @param[in]   inl     input length (in bytes)
     */
    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override;
};

} // namespace sha1

#endif