#ifndef HASH_LIB_HASH_H
#define HASH_LIB_HASH_H

#include <cstddef>
#include <cstdint>

namespace hash_lib {

class Hash
{
public:
    virtual ~Hash() = default;

public:
    virtual const char* fetch_name() const noexcept = 0;

    virtual std::size_t fetch_block_size() const noexcept = 0;

    virtual std::size_t fetch_digest_size() const noexcept = 0;

    virtual std::size_t fetch_security_strength() const noexcept = 0;

public:
    virtual void reset() = 0;

    virtual void update(const std::uint8_t* in, std::size_t inl) = 0;

    virtual void do_final(std::uint8_t*       digest,
                          const std::uint8_t* in  = nullptr,
                          std::size_t         inl = 0) = 0;
};

} // namespace hash_lib

#endif