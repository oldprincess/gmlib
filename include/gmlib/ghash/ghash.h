#ifndef GHASH_GHASH_H
#define GHASH_GHASH_H

#include <gmlib/hash_lib/impl/hash_impl.h>

#include <memory>

namespace ghash {

class GHash : public hash_lib::impl::HashImpl<16>
{
public:
    static constexpr const char* NAME        = "GHash";
    static constexpr std::size_t BLOCK_SIZE  = 16;
    static constexpr std::size_t DIGEST_SIZE = 16;

private:
    std::unique_ptr<void, void (*)(void*)> ctx_;

public:
    GHash();

    GHash(const GHash& other);

    GHash(const std::uint8_t H[16]);

    void reset() noexcept override;

    void set_key(const std::uint8_t H[16]) noexcept;

public:
    GHash& operator=(const GHash& other) noexcept;

public:
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
        return 0;
    }

private:
    void update_blocks(const std::uint8_t* in,
                       std::size_t         block_num) noexcept override;

    void final_block(std::uint8_t*       digest,
                     const std::uint8_t* in,
                     std::size_t         inl) override;
};

} // namespace ghash

#endif