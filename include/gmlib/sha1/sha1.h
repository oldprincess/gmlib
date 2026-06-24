#ifndef SHA1_SHA1_H
#define SHA1_SHA1_H

#include <gmlib/hash_lib/hash.h>

namespace sha1 {

class SHA1 : public hash_lib::Hash
{
public:
    static constexpr const char* NAME = "SHA1";

    /// @brief SHA1 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 64;

    /// @brief SHA1 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = 20;

    /// @brief SHA1 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = 10;

public:
    static hash_lib::Hash::HashPtr create_hash(const char* provider = nullptr);

private:
    hash_lib::Hash::HashPtr impl_ = create_hash();

public:
    SHA1() noexcept = default;

    SHA1(const SHA1& other) : impl_(other.impl_->clone())
    {
    }

    SHA1& operator=(const SHA1& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    SHA1(SHA1&& other) noexcept = default;

    SHA1& operator=(SHA1&& other) noexcept = default;

public:
    const char* fetch_name() const noexcept override
    {
        return impl_->fetch_name();
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return impl_->fetch_impl_algo();
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
    void reset() override
    {
        impl_->reset();
    }

    void update(const std::uint8_t* in, std::size_t inl) override
    {
        impl_->update(in, inl);
    }

    void do_final(std::uint8_t*       digest,
                  const std::uint8_t* in  = nullptr,
                  std::size_t         inl = 0) override
    {
        impl_->do_final(digest, in, inl);
    }

public:
    void ctrl(const char* cmd, std::size_t argc, void* argv[]) override
    {
        impl_->ctrl(cmd, argc, argv);
    }

    hash_lib::Hash::HashPtr clone() const override
    {
        return impl_->clone();
    }
};

} // namespace sha1

#endif