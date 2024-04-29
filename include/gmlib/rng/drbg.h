// NIST SP 800 90
#ifndef RNG_DRBG_H
#define RNG_DRBG_H

#include <gmlib/rng/sp800_90/hash_drbg.h>
#include <gmlib/rng/sp800_90/hmac_drbg.h>
namespace rng {

using sp800_90::HashDrbg;
using sp800_90::HMacDrbg;

} // namespace rng

#endif