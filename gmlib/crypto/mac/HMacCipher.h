/**
 * RFC 2104: "HMAC: Keyed-Hashing for Message Authentication"
 * https://www.rfc-editor.org/rfc/rfc2104
 */
#ifndef _GMLIB_CRYPTO_MAC_HMAC_H
#define _GMLIB_CRYPTO_MAC_HMAC_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>

namespace gmlib {

template <class Hash>
class HMacCipher
{
public:
    static constexpr size_t DIGEST_SIZE = Hash::DIGEST_SIZE;

private:
    uint8_t K[Hash::BLOCK_SIZE];
    Hash    h;

public:
    HMacCipher() = default;
    HMacCipher(const uint8_t* key, size_t key_len)
    {
        this->set_key(key, key_len);
    }

public:
    void set_key(const uint8_t* key, size_t key_len)
    {
        memset(this->K, 0, Hash::BLOCK_SIZE);
        if (key_len > Hash::BLOCK_SIZE)
        {
            uint8_t digest[Hash::DIGEST_SIZE];
            Hash::compute(digest, key, key_len);
            size_t cpy_size = (Hash::BLOCK_SIZE >= Hash::DIGEST_SIZE)
                                  ? Hash::BLOCK_SIZE
                                  : Hash::DIGEST_SIZE;
            memcpy(this->K, digest, cpy_size);
        }
        else
        {
            memcpy(this->K, key, key_len);
        }

        uint8_t i_pad[Hash::BLOCK_SIZE];
        for (size_t i = 0; i < Hash::BLOCK_SIZE; i++)
        {
            i_pad[i] = this->K[i] ^ 0x36;
        }
        this->h.update(i_pad, Hash::BLOCK_SIZE);
    }

    void update(const uint8_t* msg, size_t msg_len)
    {
        this->h.update(msg, msg_len);
    }

    void final(uint8_t* digest)
    {
        uint8_t i_digest[Hash::DIGEST_SIZE];
        uint8_t o_pad[Hash::BLOCK_SIZE];

        this->h.final(i_digest);
        this->h.reset();
        for (size_t i = 0; i < Hash::BLOCK_SIZE; i++)
        {
            o_pad[i] = this->K[i] ^ 0x5c;
        }
        this->h.update(o_pad, Hash::BLOCK_SIZE);
        this->h.update(i_digest, Hash::DIGEST_SIZE);
        this->h.final(digest);
    }

public:
    static void compute(uint8_t*       digest,
                        const uint8_t* key,
                        size_t         key_len,
                        const uint8_t* msg,
                        size_t         msg_len)
    {
        auto hmac = HMacCipher(key, key_len);
        hmac.update(msg, msg_len);
        hmac.final(digest);
    }
};

} // namespace gmlib

#endif