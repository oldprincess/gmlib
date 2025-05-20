
#include <gmlib/md5/md5.h>

#include "md5_common.h"
namespace md5 {
namespace alg = internal::common;
} // namespace md5

namespace md5 {

const char* MD5::fetch_impl_algo() const noexcept
{
    return alg::MD5_ALGO_NAME;
}

MD5::MD5() noexcept
{
    alg::md5_init(state_, &data_bits_);
}

void MD5::reset() noexcept
{
    this->HashImpl<BLOCK_SIZE>::reset();
    alg::md5_reset(state_, &data_bits_);
}

void MD5::update_blocks(const std::uint8_t* in, std::size_t block_num) noexcept
{
    alg::md5_update_blocks(state_, &data_bits_, in, block_num);
}

void MD5::final_block(std::uint8_t*       digest,
                      const std::uint8_t* in,
                      std::size_t         inl) noexcept
{
    alg::md5_final_block(state_, &data_bits_, digest, in, inl);
}

} // namespace md5
