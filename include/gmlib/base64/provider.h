#ifndef BASE64_PROVIDER_H
#define BASE64_PROVIDER_H

#include <cstddef>
#include <cstdint>

namespace base64 {

struct Base64Provider
{
    /** @brief Implementation name. */
    const char* algo_name;

    /**
     * @brief  Check whether the input is valid Base64 encoding
     * @param  in   Input string
     * @param  inl  Input length
     * @return true if the input is valid Base64, false otherwise
     */
    bool (*base64_is_b64)(const char* in, std::size_t inl) noexcept = nullptr;

    /**
     * @brief  Compute the output buffer size required for Base64 encoding
     * @param  inl  Input data length in bytes
     * @return Required output buffer size after encoding
     */
    std::size_t (*base64_encode_outl)(std::size_t inl) noexcept = nullptr;

    /**
     * @brief  Compute the string length after Base64 encoding (including null
     *         terminator)
     * @param  inl  Input data length in bytes
     * @return Encoded string length (includes null terminator)
     */
    std::size_t (*base64_encode_strl)(std::size_t inl) noexcept = nullptr;

    /**
     * @brief  Compute the output buffer size required for Base64 decoding
     * @param  in   Input Base64 string
     * @param  inl  Input length
     * @return Required output buffer size after decoding
     */
    std::size_t (*base64_decode_outl)(const char* in,
                                      std::size_t inl) noexcept = nullptr;

    /**
     * @brief  Encode data to Base64
     * @param  out  Output buffer (caller-allocated, size determined by
     *              base64_encode_outl)
     * @param  in   Input data
     * @param  inl  Input data length in bytes
     */
    void (*base64_encode)(char*               out,
                          const std::uint8_t* in,
                          std::size_t         inl) noexcept = nullptr;

    /**
     * @brief  Decode a Base64 string
     * @param  out  Output buffer (caller-allocated, size determined by
     *              base64_decode_outl)
     * @param  in   Input Base64 string
     * @param  inl  Input length
     * @return 0 on success, non-zero on failure
     */
    int (*base64_decode)(std::uint8_t* out,
                         const char*   in,
                         std::size_t   inl) noexcept = nullptr;
};

const Base64Provider* get_provider(const char* name) noexcept;

const char* const* get_provider_name_list() noexcept;

} // namespace base64

#endif
