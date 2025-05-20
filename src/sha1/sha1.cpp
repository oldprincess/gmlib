#include <gmlib/sha1/sha1.h>

#include <stdexcept>

#include "config.h"

#if defined(SHA1_IMPL_SHA)
#include "sha1_sha.h"
namespace sha1 {
namespace alg = internal::sha;
} // namespace sha1
#else
#include "sha1_common.h"
namespace sha1 {
namespace alg = internal::common;
} // namespace sha1
#endif

namespace sha1 {

SHA1::SHA1() noexcept
{
    alg::sha1_init(state_, &data_bits_);
}

const char* SHA1::fetch_impl_algo() const noexcept
{
    return alg::SHA1_ALGO_NAME;
}

void SHA1::reset() noexcept
{
    this->HashImpl<64>::reset();
    alg::sha1_reset(state_, &data_bits_);
}

void SHA1::update_blocks(const std::uint8_t* in, std::size_t block_num)
{
    int ret = alg::sha1_update_blocks(state_, &data_bits_, in, block_num);
    if (ret != 0)
    {
        throw std::runtime_error("sha1 update blocks error");
    }
}

void SHA1::final_block(std::uint8_t*       digest,
                       const std::uint8_t* in,
                       std::size_t         inl)
{
    int ret = alg::sha1_final_block(state_, &data_bits_, digest, in, inl);
    if (ret != 0)
    {
        throw std::runtime_error("sha1 final block error");
    }
}

}; // namespace sha1