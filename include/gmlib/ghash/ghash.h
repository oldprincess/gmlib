#ifndef GHASH_GHASH_H
#define GHASH_GHASH_H

#include <gmlib/hash_lib/hash.h>

#include <cstring>
#include <memory>

namespace ghash {

class GHash : public hash_lib::Hash
{
public:
    static constexpr const char* NAME        = "GHash";
    static constexpr std::size_t BLOCK_SIZE  = 16;
    static constexpr std::size_t DIGEST_SIZE = 16;

public:
    static hash_lib::Hash::HashPtr create_hash(const char* provider = nullptr);

private:
    hash_lib::Hash::HashPtr impl_ = create_hash();

public:
    GHash() noexcept = default;

    GHash(const GHash& other) : impl_(other.impl_->clone())
    {
    }

    GHash(const std::uint8_t H[16]) : impl_(create_hash())
    {
        const std::uint8_t* h      = H;
        void*               args[] = {&h};
        impl_->ctrl("set_key", 1, args);
    }

    void set_key(const std::uint8_t H[16])
    {
        const std::uint8_t* h      = H;
        void*               args[] = {&h};
        impl_->ctrl("set_key", 1, args);
    }

public:
    GHash& operator=(const GHash& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    GHash(GHash&& other) noexcept            = default;
    GHash& operator=(GHash&& other) noexcept = default;

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
        return 0;
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

} // namespace ghash

#endif