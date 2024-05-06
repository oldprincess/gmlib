// NIST SP 800 90
#ifndef RNG_SP800_90_HMAC_DRBG_H
#define RNG_SP800_90_HMAC_DRBG_H

#include <gmlib/hash_lib/hmac.h>
#include <gmlib/memory_utils/endian.h>
#include <gmlib/rng/rng.h>
#include <gmlib/rng/sp800_90/internal/bn.h>
#include <gmlib/rng/sp800_90/internal/entropy.h>

#include <cstring>

namespace rng::sp800_90 {

/**
 * @brief   Unlike the standard of NIST SP 800 90A, the length here is in bytes,
 *          which is different from the length in bits in the standard
 * @tparam  Hash
 */
template <class Hash>
class HMacDrbg : public Rng
{
    static_assert(hash_lib::type_traits::is_valid_hash<Hash>::value,
                  "invalid hash class");

public:
    /// @brief Minimum entropy input length (in bytes)
    static constexpr std::size_t MINIMUM_ENTROPY = Hash::SECURITY_STRENGTH;

    /// @brief Maximum entropy input length (in bytes):  2^32 bytes
    static constexpr std::uint64_t MAXIMUM_ENTROPY = (1ULL << 32);

    /// @brief Maximum personalization string length (in bytes): 2^32 bytes
    static constexpr std::uint64_t MAXIMUM_PERSONALIZATION = (1ULL << 32);

    /// @brief Maximum additional_input length (in bytes): 2^32 bytes
    static constexpr std::uint64_t MAXIMUM_ADDITIONAL = (1ULL << 32);

    static constexpr std::uint32_t MAXIMUM_BYTES_PER_REQUEST = (1ULL << 16);

    /// @brief Maximum number of requests: 2^48
    static constexpr std::uint64_t MAXIMUM_REQUESTS_BEFORE_RESEED =
        (1ULL << 48);

    /// @brief Seed length (in bytes)
    static constexpr std::size_t SEED_LEN =
        (Hash::DIGEST_SIZE <= 32) ? 55 : 111;

    /// @brief Output Block Length (in bytes)
    static constexpr std::size_t OUT_BLOCK_LEN = Hash::DIGEST_SIZE;

private:
    std::uint8_t  V_[HMacDrbg::OUT_BLOCK_LEN];
    std::uint8_t  K_[HMacDrbg::OUT_BLOCK_LEN];
    std::uint64_t reseed_counter_;

public:
    inline HMacDrbg();

    inline ~HMacDrbg() noexcept = default;

private:
    /**
     * @brief       HMAC_DRBG_Update (provided_data, K, V)
     * @param[in]   provided_data
     *                  The data to be used, a list
     * @param[in]   provided_data_length
     *                  length in bytes, a list
     * @param[in]   provided_data_num
     *                  number of provided data, that means, provided data is
     *                  provided_data[0] || provided_data[1] || ... ||
     *                  provided_data[provided_data_num -1]
     */
    inline void hmac_drbg_update(const std::uint8_t* provided_data[],
                                 const std::size_t   provided_data_length[],
                                 std::size_t         provided_data_num);

public:
    /**
     * @brief       HMac_DRBG_Instantiate_algorithm
     * @param[in]   entropy_input
     *                  The string of bytes obtained from the randomness source
     * @param[in]   entropy_input_length
     *                  length in bytes
     * @param[in]   nonce
     *                  A string of bytes
     * @param[in]   nonce_length
     *                  length in bytes
     * @param[in]   personalization_string
     *                  The personalization string received from the consuming
     *                  application. Note that the length of the
     *                  personalization_string may be zero
     * @param[in]   personalization_string_length
     *                  length in bytes
     * @param[in]   security_strength
     *                  The security strength for the instantiation. This
     *                  parameter is optional for HMAC_DRBG, since it is not
     *                  used
     */
    inline void instantiate(const std::uint8_t* entropy_input,
                            std::size_t         entropy_input_length,
                            const std::uint8_t* nonce,
                            std::size_t         nonce_length,
                            const std::uint8_t* personalization_string,
                            std::size_t         personalization_string_length,
                            std::size_t         security_strength);

    /**
     * @brief       HMAC_DRBG_Reseed_algorithm
     * @param[in]   entropy_input
     *                  The string of bytes obtained from the randomness source
     * @param[in]   entropy_input_length
     *                  length in bytes
     * @param[in]   additional_input
     *                  The additional input string received from the consuming
     *                  application. Note that the length of the
     *                  additional_input string may be zero
     * @param[in]   additional_input_length
     *                  length in bytes
     */
    inline void reseed(const std::uint8_t* entropy_input,
                       std::size_t         entropy_input_length,
                       const std::uint8_t* additional_input,
                       std::size_t         additional_input_length);

    /**
     * @brief       HMAC_DRBG_Generate_algorithm
     * @param[out]  returned_bytes
     *                  The pseudorandom bytes to be returned to the generate
     *                  function
     * @param[in]   requested_number_of_bytes
     *                  The number of pseudorandom bytes to be returned to the
     *                  generate function
     * @param[in]   additional_input
     *                  The additional input string received from the consuming
     *                  application. Note that the length of the
     *                  additional_input string may be zero
     * @param[in]   additional_input_length
     *                  length in bytes
     * @return          0(Success), -1(error, need to reseed)
     */
    inline int generate(std::uint8_t*       returned_bytes,
                        std::size_t         requested_number_of_bytes,
                        const std::uint8_t* additional_input,
                        std::size_t         additional_input_length);

public:
    const char* name() const noexcept override
    {
        return "HMacDrbg";
    }

    inline void gen(void* out, std::size_t len) override;
};

template <class Hash>
inline HMacDrbg<Hash>::HMacDrbg()
{
    std::uint8_t entropy[HMacDrbg<Hash>::MINIMUM_ENTROPY];
    internal::get_entropy(entropy, sizeof(entropy));
    this->instantiate(entropy, sizeof(entropy), nullptr, 0, nullptr, 0,
                      Hash::SECURITY_STRENGTH);
}

template <class Hash>
inline void HMacDrbg<Hash>::gen(void* out, std::size_t len)
{
    std::uint8_t  entropy[HMacDrbg<Hash>::MINIMUM_ENTROPY];
    std::uint8_t* data_u8ptr = (std::uint8_t*)out;
    int           ret;
    while (len >= HMacDrbg<Hash>::MAXIMUM_BYTES_PER_REQUEST)
    {
        ret = this->generate(                          //
            data_u8ptr,                                //
            HMacDrbg<Hash>::MAXIMUM_BYTES_PER_REQUEST, //
            nullptr,                                   //
            0                                          //
        );
        if (ret == -1) // unlikely
        {
            internal::get_entropy(entropy, sizeof(entropy));
            this->reseed(entropy, sizeof(entropy), nullptr, 0);
        }
        else
        {
            data_u8ptr += HMacDrbg<Hash>::MAXIMUM_BYTES_PER_REQUEST;
            len -= HMacDrbg<Hash>::MAXIMUM_BYTES_PER_REQUEST;
        }
    }
    if (len > 0)
    {
        ret = this->generate(data_u8ptr, len, nullptr, 0);
        if (ret == -1) // unlikely
        {
            internal::get_entropy(entropy, sizeof(entropy));
            this->reseed(entropy, sizeof(entropy), nullptr, 0);
            this->generate(data_u8ptr, len, nullptr, 0); // never fail
        }
    }
}

template <class Hash>
void HMacDrbg<Hash>::hmac_drbg_update( //
    const std::uint8_t* provided_data[],
    const std::size_t   provided_data_length[],
    std::size_t         provided_data_num)
{
    static const std::uint8_t ZERO = 0, ONE = 1;

    hash_lib::HMac<Hash> hmac;
    // 1. K = HMAC (K, V || 0x00 || provided_data)
    hmac.set_key(K_, sizeof(K_));
    hmac.update(V_, sizeof(V_));
    hmac.update(&ZERO, 1);
    for (std::size_t i = 0; i < provided_data_num; i++)
    {
        hmac.update(provided_data[i], provided_data_length[i]);
    }
    hmac.do_final(K_);
    // 2. V = HMAC (K, V)
    hmac.set_key(K_, sizeof(K_));
    hmac.do_final(V_, V_, sizeof(V_));
    // 3. If (provided_data = Null), then return K and V
    if (provided_data_num == 0)
    {
        return;
    }
    // 4. K = HMAC (K, V || 0x01 || provided_data)
    hmac.set_key(K_, sizeof(K_));
    hmac.update(V_, sizeof(V_));
    hmac.update(&ONE, 1);
    for (std::size_t i = 0; i < provided_data_num; i++)
    {
        hmac.update(provided_data[i], provided_data_length[i]);
    }
    hmac.do_final(K_);
    // 5. V = HMAC (K, V)
    hmac.set_key(K_, sizeof(K_));
    hmac.do_final(V_, V_, sizeof(V_));
    // 6. Return (K, V)
}

template <class Hash>
void HMacDrbg<Hash>::instantiate( //
    const std::uint8_t* entropy_input,
    std::size_t         entropy_input_length,
    const std::uint8_t* nonce,
    std::size_t         nonce_length,
    const std::uint8_t* personalization_string,
    std::size_t         personalization_string_length,
    std::size_t         security_strength)
{
    const std::uint8_t* provided_data[3];
    std::size_t         provided_data_length[3];
    // 1. seed_material = entropy_input || nonce || personalization_string
    provided_data[0]        = entropy_input;
    provided_data_length[0] = entropy_input_length;
    provided_data[1]        = nonce;
    provided_data_length[1] = nonce_length;
    provided_data[2]        = personalization_string;
    provided_data_length[2] = personalization_string_length;
    // 2. Key = 0x00 00...00
    // 3. V   = 0x01 01...01
    std::memset(K_, 0, sizeof(K_));
    std::memset(V_, 1, sizeof(V_));
    // 4. (Key, V) = HMAC_DRBG_Update(seed_material, Key, V)
    this->hmac_drbg_update(provided_data, provided_data_length, 3);
    // 5. reseed_counter = 1
    reseed_counter_ = 1;
    // 6. Return (V, Key. reseed_counter)
}

template <class Hash>
void HMacDrbg<Hash>::reseed(const std::uint8_t* entropy_input,
                            std::size_t         entropy_input_length,
                            const std::uint8_t* additional_input,
                            std::size_t         additional_input_length)
{
    const std::uint8_t* provided_data[2];
    std::size_t         provided_data_length[2];
    // 1. seed_material = entropy_input || additional_input
    provided_data[0]        = entropy_input;
    provided_data_length[0] = entropy_input_length;
    provided_data[1]        = additional_input;
    provided_data_length[1] = additional_input_length;
    // 2. (Key, V) = HMAC_DRBG_Update(seed_material, Key, V)
    this->hmac_drbg_update(provided_data, provided_data_length, 2);
    // 3. reseed_counter = 1
    reseed_counter_ = 1;
}

template <class Hash>
inline int HMacDrbg<Hash>::generate( //
    std::uint8_t*       returned_bytes,
    std::size_t         requested_number_of_bytes,
    const std::uint8_t* additional_input,
    std::size_t         additional_input_length)
{
    const std::uint8_t* provided_data[1]        = {additional_input};
    const std::size_t   provided_data_length[1] = {additional_input_length};

    hash_lib::HMac<Hash> hmac;
    // 1. If reseed_counter > reseed_interval, then return an indication that a
    // reseed is required
    if (reseed_counter_ > HMacDrbg<Hash>::MAXIMUM_REQUESTS_BEFORE_RESEED)
    {
        return -1;
    }
    // 2. If additional_input != Null,
    // then (Key, V) = HMAC_DRBG_Update(additional_input, Key, V)
    if (additional_input != nullptr)
    {
        this->hmac_drbg_update(provided_data, provided_data_length, 1);
    }
    // 3. temp = Null
    // 4. While (len (temp) < requested_number_of_bits) do
    //      4.1 V = HMAC (Key, V)
    //      4.2 temp = temp || V
    // 5. returned_bits = leftmost (temp, requested_number_of_bits)
    while (requested_number_of_bytes >= HMacDrbg<Hash>::OUT_BLOCK_LEN)
    {
        hmac.set_key(K_, sizeof(K_));
        hmac.do_final(V_, V_, sizeof(V_));
        std::memcpy(returned_bytes, V_, HMacDrbg<Hash>::OUT_BLOCK_LEN);

        returned_bytes += HMacDrbg<Hash>::OUT_BLOCK_LEN;
        requested_number_of_bytes -= HMacDrbg<Hash>::OUT_BLOCK_LEN;
    }
    if (requested_number_of_bytes)
    {
        hmac.set_key(K_, sizeof(K_));
        hmac.do_final(V_, V_, sizeof(V_));
        std::memcpy(returned_bytes, V_, requested_number_of_bytes);
    }
    // 6. (Key, V) = HMAC_DRBG_Update (additional_input, Key, V)
    this->hmac_drbg_update(provided_data, provided_data_length, 1);
    // 7. reseed_counter = reseed_counter + 1
    reseed_counter_ += 1;
    // 8. Return (SUCCESS, returned_bits, Key, V, reseed_counter)
    return 0;
}

} // namespace rng::sp800_90

#endif