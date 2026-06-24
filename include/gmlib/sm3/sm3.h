#ifndef SM3_SM3_H
#define SM3_SM3_H

#include <gmlib/hash_lib/hash.h>

namespace sm3 {

/**
 * @brief   SM3 cryptographic hash algorithm
 * @details GB/T 32905-2016
 */
class SM3 : public hash_lib::Hash
{
public:
    static constexpr const char* NAME = "SM3";

    /// @brief SM3 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 64;

    /// @brief SM3 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = 32;

    /// @brief SM3 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = 16;

public:
    static hash_lib::Hash::HashPtr create_hash(const char* provider = nullptr);

private:
    hash_lib::Hash::HashPtr impl_ = create_hash();

public:
    SM3() noexcept = default;

    SM3(const SM3& other) : impl_(other.impl_->clone())
    {
    }

    SM3& operator=(const SM3& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    SM3(SM3&& other) noexcept            = default;
    SM3& operator=(SM3&& other) noexcept = default;

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

} // namespace sm3

#endif