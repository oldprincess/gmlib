#ifndef _GMLIB_CRYPTO_HASH_BASE_H
#define _GMLIB_CRYPTO_HASH_BASE_H

#include <gmlib/exception.h>
#include <stdint.h>
#include <stddef.h>

namespace gmlib {

class HashBase
{
public:
    static constexpr size_t BLOCK_SIZE  = 0;
    static constexpr size_t DIGEST_SIZE = 0;

public:
    virtual void reset()
    {
        throw gmlib::Exception("NotImplementedError");
    }

    virtual void update(const uint8_t* in, size_t inl)
    {
        throw gmlib::Exception("NotImplementedError");
    }

    virtual void final(uint8_t* digest)
    {
        throw gmlib::Exception("NotImplementedError");
    }

public:
    static void compute(uint8_t* digest, const uint8_t* msg, size_t msg_len)
    {
        throw gmlib::Exception("NotImplementedError");
    }
};

} // namespace gmlib

#endif