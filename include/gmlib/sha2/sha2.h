#ifndef SHA224_SHA2_H
#define SHA224_SHA2_H

#include <gmlib/hash_lib/hash.h>

namespace sha2 {

class SHA224 : public hash_lib::Hash
{
public:
    static constexpr const char* NAME = "SHA224";

    /// @brief SHA224 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 64;

    /// @brief SHA224 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = 28;

    /// @brief SHA224 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = 14;

public:
    static hash_lib::Hash::HashPtr create_hash(const char* provider = nullptr);

private:
    hash_lib::Hash::HashPtr impl_ = create_hash();

public:
    SHA224() noexcept = default;

    SHA224(const SHA224& other) : impl_(other.impl_->clone())
    {
    }

    SHA224& operator=(const SHA224& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    SHA224(SHA224&& other) noexcept            = default;
    SHA224& operator=(SHA224&& other) noexcept = default;

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

class SHA256 : public hash_lib::Hash
{
public:
    static constexpr const char* NAME = "SHA256";

    /// @brief SHA256 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 64;

    /// @brief SHA256 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = 32;

    /// @brief SHA256 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = 16;

public:
    static hash_lib::Hash::HashPtr create_hash(const char* provider = nullptr);

private:
    hash_lib::Hash::HashPtr impl_ = create_hash();

public:
    SHA256() noexcept = default;

    SHA256(const SHA256& other) : impl_(other.impl_->clone())
    {
    }

    SHA256& operator=(const SHA256& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    SHA256(SHA256&& other) noexcept            = default;
    SHA256& operator=(SHA256&& other) noexcept = default;

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

class SHA384 : public hash_lib::Hash
{
public:
    static constexpr const char* NAME = "SHA384";

    /// @brief SHA384 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 128;

    /// @brief SHA384 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = 48;

    /// @brief SHA384 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = 24;

public:
    static hash_lib::Hash::HashPtr create_hash(const char* provider = nullptr);

private:
    hash_lib::Hash::HashPtr impl_ = create_hash();

public:
    SHA384() noexcept = default;

    SHA384(const SHA384& other) : impl_(other.impl_->clone())
    {
    }

    SHA384& operator=(const SHA384& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    SHA384(SHA384&& other) noexcept            = default;
    SHA384& operator=(SHA384&& other) noexcept = default;

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

class SHA512 : public hash_lib::Hash
{
public:
    static constexpr const char* NAME = "SHA512";

    /// @brief SHA512 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 128;

    /// @brief SHA512 Digest Size (in bytes)
    static constexpr std::size_t DIGEST_SIZE = 64;

    /// @brief SHA512 Security Strength (in bytes)
    static constexpr std::size_t SECURITY_STRENGTH = 32;

public:
    static hash_lib::Hash::HashPtr create_hash(const char* provider = nullptr);

private:
    hash_lib::Hash::HashPtr impl_ = create_hash();

public:
    SHA512() noexcept = default;

    SHA512(const SHA512& other) : impl_(other.impl_->clone())
    {
    }

    SHA512& operator=(const SHA512& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    SHA512(SHA512&& other) noexcept            = default;
    SHA512& operator=(SHA512&& other) noexcept = default;

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

} // namespace sha2

#endif