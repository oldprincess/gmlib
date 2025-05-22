#include <gmlib/sm3/sm3.h>

#include <stdexcept>

#include "config.h"
#if defined(SM3_IMPL_YANG15)
#include "sm3_yang15.h"
namespace sm3 {
namespace alg = sm3::internal::yang15;
} // namespace sm3
#else
#include "sm3_common.h"
namespace sm3 {
namespace alg = sm3::internal::common;
} // namespace sm3
#endif

namespace sm3 {

SM3::SM3() noexcept
{
    alg::sm3_init(state_, &data_bits_);
}

const char* SM3::fetch_impl_algo() const noexcept
{
    return alg::SM3_ALGO_NAME;
}

void SM3::reset() noexcept
{
    this->HashImpl<SM3::BLOCK_SIZE>::reset();
    alg::sm3_reset(state_, &data_bits_);
}

void SM3::update_blocks(const std::uint8_t* in, std::size_t block_num)
{
    int ret = alg::sm3_update_blocks(state_, &data_bits_, in, block_num);
    if (ret)
    {
        throw std::runtime_error("sm3 update blocks error");
    }
}

void SM3::final_block(std::uint8_t*       digest,
                      const std::uint8_t* in,
                      std::size_t         inl)
{
    int ret = alg::sm3_final_block(state_, &data_bits_, digest, in, inl);
    if (ret)
    {
        throw std::runtime_error("sm3 final block error");
    }
}

}; // namespace sm3