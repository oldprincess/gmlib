#ifndef MD5_MD5_H
#define MD5_MD5_H

#include <gmlib/hash_lib/impl/hash_impl.h>

namespace md5 {

class MD5 : public hash_lib::impl::HashImpl<64>
{
public:
    static constexpr const char* NAME = "MD5";

    /// @brief MD5 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 64;

    /// @brief MD5 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = 16;

    /// @brief MD5 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = 8;

private:
    /// @brief MD5 private Context
    std::uint32_t state_[4];
    std::uint64_t data_bits_;

public:
    /**
     * @brief MD5 Context Init
     */
    MD5() noexcept;

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
     * @brief MD5 Context Reset (re-init)
     */
    void reset() noexcept override;

private:
    /**
     * @brief                   MD5 message update
     * @param[in]   in          BLOCK_SIZE x block_num -bytes input data
     * @param[in]   block_num   input data block number
     */
    void update_blocks(const std::uint8_t* in,
                       std::size_t         block_num) noexcept override;

    /**
     * @brief               MD5 update final message block and output digest
     * @param[out]  digest  16-bytes digest data
     * @param[in]   in      input data, not bigger than 64 bytes
     * @param[in]   inl     input length (in bytes)
     */
    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) noexcept override;
};

} // namespace md5

#endif