#ifndef MD5_MD5_H
#define MD5_MD5_H

#include <gmlib/hash_lib/hash.h>

namespace md5 {

class MD5 : public hash_lib::Hash
{
public:
    static constexpr const char* NAME = "MD5";

    /// @brief MD5 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 64;

    /// @brief MD5 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = 16;

    /// @brief MD5 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = 8;

public:
    static hash_lib::Hash::HashPtr create_hash(const char* provider = nullptr);

private:
    hash_lib::Hash::HashPtr impl_ = create_hash();

public:
    MD5() noexcept = default;

    MD5(const MD5& other) : impl_(other.impl_->clone())
    {
    }

    MD5& operator=(const MD5& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    MD5(MD5&& other) noexcept            = default;
    MD5& operator=(MD5&& other) noexcept = default;

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

} // namespace md5

#endif