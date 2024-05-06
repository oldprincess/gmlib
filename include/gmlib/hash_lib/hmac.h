#ifndef HASH_LIB_HMAC_H
#define HASH_LIB_HMAC_H

#include <gmlib/hash_lib/abc.h>

namespace hash_lib {

template <class Hash>
class HMac
{
    static_assert(type_traits::is_valid_hash<Hash>::value,
                  "invalid hash class");

public:
    static constexpr std::size_t DIGEST_SIZE = Hash::DIGEST_SIZE;

private:
    std::uint8_t K_[Hash::BLOCK_SIZE];
    Hash         h_;

public:
    HMac() = default;

    HMac(const std::uint8_t* key, std::size_t key_len)
    {
        this->set_key(key, key_len);
    }

public:
    void set_key(const std::uint8_t* key, std::size_t key_len)
    {
        h_.reset();
        std::memset(K_, 0, Hash::BLOCK_SIZE);
        if (key_len > Hash::BLOCK_SIZE)
        {
            std::uint8_t digest[Hash::DIGEST_SIZE];
            h_.do_final(digest, key, key_len);
            h_.reset();
            std::size_t cpy_size = (Hash::BLOCK_SIZE < Hash::DIGEST_SIZE)
                                       ? Hash::BLOCK_SIZE
                                       : Hash::DIGEST_SIZE;
            std::memcpy(K_, digest, cpy_size);
        }
        else
        {
            std::memcpy(K_, key, key_len);
        }

        std::uint8_t i_pad[Hash::BLOCK_SIZE];
        for (std::size_t i = 0; i < Hash::BLOCK_SIZE; i++)
        {
            i_pad[i] = K_[i] ^ 0x36;
        }
        h_.update(i_pad, Hash::BLOCK_SIZE);
    }

    void update(const std::uint8_t* msg, std::size_t msg_len)
    {
        h_.update(msg, msg_len);
    }

    void do_final(std::uint8_t*       digest,
                  const std::uint8_t* msg     = nullptr,
                  std::size_t         msg_len = 0)
    {
        this->update(msg, msg_len);

        std::uint8_t i_digest[Hash::DIGEST_SIZE];
        std::uint8_t o_pad[Hash::BLOCK_SIZE];

        h_.do_final(i_digest, nullptr, 0);
        h_.reset();
        for (std::size_t i = 0; i < Hash::BLOCK_SIZE; i++)
        {
            o_pad[i] = K_[i] ^ 0x5c;
        }
        h_.update(o_pad, Hash::BLOCK_SIZE);
        h_.update(i_digest, Hash::DIGEST_SIZE);
        h_.do_final(digest, nullptr, 0);
    }
};

} // namespace hash_lib

#endif