#ifndef SHA224_SHA2_H
#define SHA224_SHA2_H

#include <gmlib/hash_lib/impl/hash_impl.h>

namespace sha2 {

class SHA224 : public hash_lib::impl::HashImpl<64>
{
public:
    static constexpr const char* NAME = "SHA224";

    /// @brief SHA224 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 64;

    /// @brief SHA224 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = 28;

    /// @brief SHA224 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = 14;

private:
    /// @brief SHA224 private Context
    std::uint8_t state_[32];
    std::uint64_t data_bits_;

public:
    /**
     * @brief SHA224 Context Init
     */
    SHA224() noexcept;

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
     * @brief SHA224 Context Reset (re-init)
     */
    void reset() noexcept override;

private:
    /**
     * @brief                   SHA224 message update
     * @param[in]   in          BLOCK_SIZE x block_num -bytes input data
     * @param[in]   block_num   input data block number
     */
    void update_blocks(const std::uint8_t* in, std::size_t block_num) override;

    /**
     * @brief               SHA224 update final message block and output digest
     * @param[out]  digest  24-bytes digest data
     * @param[in]   in      input data, not bigger than 64 bytes
     * @param[in]   inl     input length (in bytes)
     */
    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override;
};

class SHA256 : public hash_lib::impl::HashImpl<64>
{
public:
    static constexpr const char* NAME = "SHA256";

    /// @brief SHA256 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 64;

    /// @brief SHA256 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = 32;

    /// @brief SHA256 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = 16;

private:
    /// @brief SHA256 private Context
    std::uint8_t state_[32];
    std::uint64_t data_bits_;

public:
    /**
     * @brief SHA256 Context Init
     */
    SHA256() noexcept;

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
     * @brief SHA256 Context Reset (re-init)
     */
    void reset() noexcept override;

private:
    /**
     * @brief                   SHA256 message update
     * @param[in]   in          BLOCK_SIZE x block_num -bytes input data
     * @param[in]   block_num   input data block number
     */
    void update_blocks(const std::uint8_t* in, std::size_t block_num) override;

    /**
     * @brief               SHA256 update final message block and output digest
     * @param[out]  digest  32-bytes digest data
     * @param[in]   in      input data, not bigger than 64 bytes
     * @param[in]   inl     input length (in bytes)
     */
    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override;
};

class SHA384 : public hash_lib::impl::HashImpl<128>
{
public:
    static constexpr const char* NAME = "SHA384";

    /// @brief SHA384 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 128;

    /// @brief SHA384 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = 48;

    /// @brief SHA384 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = 24;

private:
    /// @brief SHA384 private Context
    std::uint8_t state_[64];
    std::uint64_t data_bits_h_;
    std::uint64_t data_bits_l_;

public:
    /**
     * @brief SHA384 Context Init
     */
    SHA384() noexcept;

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
     * @brief SHA384 Context Reset (re-init)
     */
    void reset() noexcept override;

private:
    /**
     * @brief                   SHA384 message update
     * @param[in]   in          BLOCK_SIZE x block_num -bytes input data
     * @param[in]   block_num   input data block number
     */
    void update_blocks(const std::uint8_t* in, std::size_t block_num) override;

    /**
     * @brief               SHA384 update final message block and output digest
     * @param[out]  digest  48-bytes digest data
     * @param[in]   in      input data, not bigger than 64 bytes
     * @param[in]   inl     input length (in bytes)
     */
    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override;
};

class SHA512 : public hash_lib::impl::HashImpl<128>
{
public:
    static constexpr const char* NAME = "SHA512";

    /// @brief SHA512 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 128;

    /// @brief SHA512 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = 64;

    /// @brief SHA512 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = 32;

private:
    /// @brief SHA512 private Context
    std::uint8_t state_[64];
    std::uint64_t data_bits_h_;
    std::uint64_t data_bits_l_;

public:
    /**
     * @brief SHA512 Context Init
     */
    SHA512() noexcept;

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
     * @brief SHA512 Context Reset (re-init)
     */
    void reset() noexcept override;

private:
    /**
     * @brief                   SHA512 message update
     * @param[in]   in          BLOCK_SIZE x block_num -bytes input data
     * @param[in]   block_num   input data block number
     */
    void update_blocks(const std::uint8_t* in, std::size_t block_num) override;

    /**
     * @brief               SHA512 update final message block and output digest
     * @param[out]  digest  32-bytes digest data
     * @param[in]   in      input data, not bigger than 64 bytes
     * @param[in]   inl     input length (in bytes)
     */
    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override;
};

} // namespace sha2

#endif